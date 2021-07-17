#include "Common.h"
#include "OpenFileManager.h"
#include "UserCall.h"
#include <ctime>

extern UserCall myUserCall;
extern INodeTable myINodeTable;
extern FileSystem myFileSystem;
extern CacheManager myCacheManager;

OpenFileTable::OpenFileTable() 
{
}

OpenFileTable::~OpenFileTable() 
{
}


void OpenFileTable::Reset() 
{
	for (int i = 0; i < OpenFileTable::MAX_FILES; ++i)
		sysFileTable[i].Reset();
}

//���ã����̴��ļ������������ҵĿ�����֮�±�д�� ar0[EAX]
File* OpenFileTable::FAlloc() 
{
	int fd = myUserCall.ofiles.AllocFreeSlot();
	if (fd < 0) 
		return NULL;
	for (int i = 0; i < OpenFileTable::MAX_FILES; ++i) {
		//count == 0��ʾ�������
		if (this->sysFileTable[i].count == 0) {
			myUserCall.ofiles.SetF(fd, &this->sysFileTable[i]);
			this->sysFileTable[i].count++;
			this->sysFileTable[i].offset = 0;
			return (&this->sysFileTable[i]);
		}
	}
	myUserCall.userErrorCode = UserCall::U_ENFILE;
	return NULL;
}

//�Դ��ļ����ƿ�File�ṹ�����ü���count��1�������ü���countΪ0�����ͷ�File�ṹ
void OpenFileTable::CloseF(File* pFile) 
{
	pFile->count--;
	if (pFile->count <= 0)
		myINodeTable.IPut(pFile->inode);
}

INodeTable::INodeTable() 
{
	fileSystem = &myFileSystem;
}

INodeTable::~INodeTable() 
{

}

void INodeTable::Reset() 
{
	INode emptyINode;
	for (int i = 0; i < INodeTable::NINODE; ++i)
		m_INodeTable[i].Reset();
}

//�����Ϊinumber�����INode�Ƿ����ڴ濽����������򷵻ظ��ڴ�INode���ڴ�INode���е�����
int INodeTable::IsLoaded(int inumber) 
{
	for (int i = 0; i < NINODE; ++i) 
		if (m_INodeTable[i].i_number == inumber && m_INodeTable[i].i_count)
			return i;
	return -1;
}

//���ڴ�INode����Ѱ��һ�����е��ڴ�INode
INode* INodeTable::GetFreeINode() 
{
	for (int i = 0; i < INodeTable::NINODE; i++) 
		if (this->m_INodeTable[i].i_count == 0)
			return m_INodeTable + i;
	return NULL;
}

//�������INode��Ż�ȡ��ӦINode�������INode�Ѿ����ڴ��У����ظ��ڴ�INode��
//��������ڴ��У���������ڴ�����������ظ��ڴ�INode������NULL:INode Table OverFlow
INode* INodeTable::IGet(int inumber) 
{
	INode* pINode;
	int index = IsLoaded(inumber);
	if (index >= 0) {
		pINode = m_INodeTable + index;
		++pINode->i_count;
		return pINode;
	}

	pINode = GetFreeINode();
	if (NULL == pINode) {
		cout << "�ڴ� INode �����!" << endl;
		myUserCall.userErrorCode = UserCall::U_ENFILE;
		return NULL;
	}

	pINode->i_number = inumber;
	pINode->i_count++;
	CacheBlock* pCache = myCacheManager.Bread(FileSystem::INODE_START_SECTOR + inumber / FileSystem::INODE_NUMBER_PER_SECTOR);
	pINode->ICopy(pCache, inumber);
	myCacheManager.Brelse(pCache);
	return pINode;
}

//���ٸ��ڴ�INode�����ü����������INode�Ѿ�û��Ŀ¼��ָ������
//���޽������ø�INode�����ͷŴ��ļ�ռ�õĴ��̿顣
void INodeTable::IPut(INode* pINode) 
{
	//��ǰ����Ϊ���ø��ڴ�INode��Ψһ���̣���׼���ͷŸ��ڴ�INode
	if (pINode->i_count == 1) {
		//���ļ��Ѿ�û��Ŀ¼·��ָ����
		if (pINode->i_nlink <= 0) {
			//�ͷŸ��ļ�ռ�ݵ������̿�
			pINode->ITrunc();
			pINode->i_mode = 0;
			//�ͷŶ�Ӧ�����INode
			this->fileSystem->IFree(pINode->i_number);
		}
		//�������INode��Ϣ
		pINode->IUpdate((int)time(NULL));
		//����ڴ�INode�����б�־λ
		pINode->i_flag = 0;
		//�����ڴ�inode���еı�־֮һ����һ����i_count == 0
		pINode->i_number = -1;
	}

	pINode->i_count--;
}

//�����б��޸Ĺ����ڴ�INode���µ���Ӧ���INode��
void INodeTable::UpdateINodeTable() 
{
	for (int i = 0; i < INodeTable::NINODE; ++i) 
		if (this->m_INodeTable[i].i_count) 
			this->m_INodeTable[i].IUpdate((int)time(NULL));
}