#include "Common.h"
#include "INode.h"
#include "FileSystem.h"
#include "UserCall.h"

extern UserCall myUserCall;
extern CacheManager myCacheManager;
extern FileSystem myFileSystem;

DiskINode::DiskINode() 
{
	this->d_mode = 0;
	this->d_nlink = 0;
	this->d_size = 0;
	memset(d_addr, 0, sizeof(d_addr));
	this->d_atime = 0;
	this->d_mtime = 0;
}

DiskINode::~DiskINode() 
{
}

INode::INode() 
{
	this->i_mode = 0;
	this->i_nlink = 0;
	this->i_count = 0;
	this->i_number = -1;
	this->i_size = 0;
	memset(i_addr, 0, sizeof(i_addr));
}

INode::~INode() 
{
}

//����Inode�����е�������̿���������ȡ��Ӧ���ļ�����
void INode::ReadI() 
{
	CacheManager& CacheManager = myCacheManager;
	int lbn, bn;
	int offset, nbytes;
	CacheBlock* pCache;
	//��Ҫ���ֽ���Ϊ�㣬�򷵻�
	if (0 == myUserCall.IOParam.count)
		return;
	this->i_flag |= INode::IACC;

	while (UserCall::U_NOERROR == myUserCall.userErrorCode && myUserCall.IOParam.count) {
		lbn = bn = myUserCall.IOParam.offset / INode::BLOCK_SIZE;
		offset = myUserCall.IOParam.offset % INode::BLOCK_SIZE;

		//���͵��û������ֽ�������ȡ�������ʣ���ֽ����뵱ǰ�ַ�������Ч�ֽ�����Сֵ
		nbytes = Common::min(INode::BLOCK_SIZE - offset, myUserCall.IOParam.count);
		int remain = this->i_size - myUserCall.IOParam.offset;
		if (remain <= 0)
			return;
		//���͵��ֽ�������ȡ����ʣ���ļ��ĳ���
		nbytes = Common::min(nbytes, remain);
		if ((bn = this->Bmap(lbn)) == 0)
			return;

		pCache = CacheManager.Bread(bn);
		//������������ʼ��λ��
		unsigned char* start = pCache->addr + offset;
		memcpy(myUserCall.IOParam.base, start, nbytes);
		myUserCall.IOParam.base += nbytes;
		myUserCall.IOParam.offset += nbytes;
		myUserCall.IOParam.count -= nbytes;

		CacheManager.Brelse(pCache);
	}
}

//����Inode�����е�������̿�������������д���ļ�
void INode::WriteI() {
	int lbn, bn;
	int offset, nbytes;
	CacheBlock* pCache;
	this->i_flag |= (INode::IACC | INode::IUPD);
	//��Ҫд�ֽ���Ϊ�㣬�򷵻�
	if (0 == myUserCall.IOParam.count)
		return;
	while (UserCall::U_NOERROR == myUserCall.userErrorCode && myUserCall.IOParam.count) 
	{
		lbn = myUserCall.IOParam.offset / INode::BLOCK_SIZE;
		offset = myUserCall.IOParam.offset % INode::BLOCK_SIZE;
		nbytes = Common::min(INode::BLOCK_SIZE - offset, myUserCall.IOParam.count);
		if ((bn = this->Bmap(lbn)) == 0)
			return;

		if (INode::BLOCK_SIZE == nbytes) //���д������������һ���ַ��飬��Ϊ����仺��
			pCache = myCacheManager.GetBlk(bn);
		else //д�����ݲ���һ���ַ��飬�ȶ���д���������ַ����Ա�������Ҫ��д�����ݣ�
			pCache = myCacheManager.Bread(bn);
		//���������ݵ���ʼдλ�� д����: ���û�Ŀ�����������ݵ�������
		unsigned char* start = pCache->addr + offset;

		memcpy(start, myUserCall.IOParam.base, nbytes);
		myUserCall.IOParam.base += nbytes;
		myUserCall.IOParam.offset += nbytes;
		myUserCall.IOParam.count -= nbytes;

		if (myUserCall.userErrorCode != UserCall::U_NOERROR)
			myCacheManager.Brelse(pCache);
		//��������Ϊ�ӳ�д�������ڽ���I/O�������ַ��������������
		myCacheManager.Bdwrite(pCache);
		//��ͨ�ļ���������
		if (this->i_size < myUserCall.IOParam.offset)
			this->i_size = myUserCall.IOParam.offset;
		this->i_flag |= INode::IUPD;
	}
}

//���������Inode�ַ�������Ϣ�������ڴ�Inode��
void INode::ICopy(CacheBlock* pb, int inumber) 
{
	DiskINode& dINode = *(DiskINode*)(pb->addr + (inumber % FileSystem::INODE_NUMBER_PER_SECTOR) * sizeof(DiskINode));
	i_mode = dINode.d_mode;
	i_size = dINode.d_size;
	i_nlink = dINode.d_nlink;
	memcpy(i_addr, dINode.d_addr, sizeof(i_addr));
}

//���ļ����߼����ת���ɶ�Ӧ�������̿��
int INode::Bmap(int lbn) 
{
	//Unix V6++���ļ������ṹ��(С�͡����ͺ;����ļ�)
	//(1) i_addr[0] - i_addr[5]Ϊֱ���������ļ����ȷ�Χ��0 - 6���̿飻
	//(2) i_addr[6] - i_addr[7]���һ�μ�����������ڴ��̿�ţ�ÿ���̿�
	//�ϴ��128���ļ������̿�ţ������ļ����ȷ�Χ��7 - (128 * 2 + 6)���̿飻
	//(3) i_addr[8] - i_addr[9]��Ŷ��μ�����������ڴ��̿�ţ�ÿ�����μ��
	//�������¼128��һ�μ�����������ڴ��̿�ţ������ļ����ȷ�Χ��
	//(128 * 2 + 6 ) < size <= (128 * 128 * 2 + 128 * 2 + 6)
	CacheManager& CacheManager = myCacheManager;
	FileSystem& fileSystem = myFileSystem;
	CacheBlock* pFirstCache, * pSecondCache;
	int phyBlkno, index;
	int* iTable;

	if (lbn >= INode::HUGE_FILE_BLOCK) {
		myUserCall.userErrorCode = UserCall::U_EFBIG;
		return 0;
	}
	//�����С���ļ����ӻ���������i_addr[0-5]�л�������̿�ż���
	if (lbn < 6) {
		phyBlkno = this->i_addr[lbn];
		//������߼���Ż�û����Ӧ�������̿����֮��Ӧ�������һ�������
		if (phyBlkno == 0 && (pFirstCache = fileSystem.Alloc()) != NULL) {
			phyBlkno = pFirstCache->blkno;
			CacheManager.Bdwrite(pFirstCache);
			this->i_addr[lbn] = phyBlkno;
			this->i_flag |= INode::IUPD;
		}
		return phyBlkno;
	}
	//lbn >= 6 ���͡������ļ�
	if (lbn < INode::LARGE_FILE_BLOCK)
		index = (lbn - INode::SMALL_FILE_BLOCK) / INode::ADDRESS_PER_INDEX_BLOCK + 6;
	else //�����ļ�: ���Ƚ���263 - (128 * 128 * 2 + 128 * 2 + 6)���̿�֮��
		index = (lbn - INode::LARGE_FILE_BLOCK) / (INode::ADDRESS_PER_INDEX_BLOCK * INode::ADDRESS_PER_INDEX_BLOCK) + 8;

	phyBlkno = this->i_addr[index];
	if (phyBlkno)
		pFirstCache = CacheManager.Bread(phyBlkno);
	else { //������Ϊ�㣬���ʾ��������Ӧ�ļ���������
		this->i_flag |= INode::IUPD;
		if ((pFirstCache = fileSystem.Alloc()) == 0)
			return 0;
		this->i_addr[index] = pFirstCache->blkno;
	}

	iTable = (int*)pFirstCache->addr;
	if (index >= 8) {
		//���ھ����ļ��������pFirstBuf���Ƕ��μ��������
		//��������߼���ţ����ɶ��μ���������ҵ�һ�μ��������
		index = ((lbn - INode::LARGE_FILE_BLOCK) / INode::ADDRESS_PER_INDEX_BLOCK) % INode::ADDRESS_PER_INDEX_BLOCK;
		phyBlkno = iTable[index];

		if (phyBlkno) {
			CacheManager.Brelse(pFirstCache);
			pSecondCache = CacheManager.Bread(phyBlkno);
		}
		else {
			if ((pSecondCache = fileSystem.Alloc()) == NULL) {
				CacheManager.Brelse(pFirstCache);
				return 0;
			}
			iTable[index] = pSecondCache->blkno;
			CacheManager.Bdwrite(pFirstCache);
		}

		pFirstCache = pSecondCache;
		iTable = (int*)pSecondCache->addr;
	}

	if (lbn < INode::LARGE_FILE_BLOCK)
		index = (lbn - INode::SMALL_FILE_BLOCK) % INode::ADDRESS_PER_INDEX_BLOCK;
	else
		index = (lbn - INode::LARGE_FILE_BLOCK) % INode::ADDRESS_PER_INDEX_BLOCK;

	if ((phyBlkno = iTable[index]) == 0 && (pSecondCache = fileSystem.Alloc()) != NULL) {
		phyBlkno = pSecondCache->blkno;
		iTable[index] = phyBlkno;
		CacheManager.Bdwrite(pSecondCache);
		CacheManager.Bdwrite(pFirstCache);
	}
	else 
		CacheManager.Brelse(pFirstCache);
	return phyBlkno;
}

//���Inode�����е�����
void INode::Clean() 
{
	//Inode::Clean()�ض�����IAlloc()������·���DiskInode��ԭ�����ݣ�
	//�����ļ���Ϣ��Clean()�����в�Ӧ�����i_dev, i_number, i_flag, i_count,
	//���������ڴ�Inode����DiskInode�����ľ��ļ���Ϣ����Inode�๹�캯����Ҫ
	//�����ʼ��Ϊ��Чֵ��
	this->i_mode = 0;
	this->i_nlink = 0;
	this->i_size = 0;
	memset(i_addr, 0, sizeof(i_addr));
}

//�������Inode�����ķ���ʱ�䡢�޸�ʱ��
void INode::IUpdate(int time) 
{
	CacheBlock* pCache;
	DiskINode dINode;
	FileSystem& fileSystem = myFileSystem;
	CacheManager& CacheManager = myCacheManager;
	//��IUPD��IACC��־֮һ�����ã�����Ҫ������ӦDiskInode
	//Ŀ¼����������������;����Ŀ¼�ļ���IACC��IUPD��־
	if (this->i_flag & (INode::IUPD | INode::IACC)) {
		pCache = CacheManager.Bread(FileSystem::INODE_START_SECTOR + this->i_number / FileSystem::INODE_NUMBER_PER_SECTOR);
		dINode.d_mode = this->i_mode;
		dINode.d_nlink = this->i_nlink;
		dINode.d_size = this->i_size;
		memcpy(dINode.d_addr, i_addr, sizeof(dINode.d_addr));
		if (this->i_flag & INode::IACC)
			dINode.d_atime = time;
		if (this->i_flag & INode::IUPD)
			dINode.d_mtime = time;

		unsigned char* p = pCache->addr + (this->i_number % FileSystem::INODE_NUMBER_PER_SECTOR) * sizeof(DiskINode);
		DiskINode* pNode = &dINode;
		memcpy(p, pNode, sizeof(DiskINode));
		CacheManager.Bwrite(pCache);
	}
}

void INode::ITrunc() 
{
	CacheManager& CacheManager = myCacheManager;
	FileSystem& fileSystem = myFileSystem;
	CacheBlock* pFirstCache, * pSecondCache;

	for (int i = 9; i >= 0; --i) {
		if (this->i_addr[i]) {
			if (i >= 6) {
				pFirstCache = CacheManager.Bread(this->i_addr[i]);
				int* pFirst = (int*)pFirstCache->addr;
				for (int j = BLOCK_SIZE / sizeof(int) - 1; j >= 0; --j) {
					if (pFirst[j]) {
						if (i >= 8) {
							pSecondCache = CacheManager.Bread(pFirst[j]);
							int* pSecond = (int*)pSecondCache->addr;
							for (int k = BLOCK_SIZE / sizeof(int) - 1; k >= 0; --k) {
								if (pSecond[k]) {
									fileSystem.Free(pSecond[k]);
								}
							}
							CacheManager.Brelse(pSecondCache);
						}
						fileSystem.Free(pFirst[j]);
					}
				}
				CacheManager.Brelse(pFirstCache);
			}
			fileSystem.Free(this->i_addr[i]);
			this->i_addr[i] = 0;
		}
	}
	this->i_size = 0;
	this->i_flag |= INode::IUPD;
	this->i_mode &= ~(INode::ILARG);
	this->i_nlink = 1;
}