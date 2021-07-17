#include "CacheManager.h"
#include "Common.h"

extern DiskDriver myDiskDriver;

//CacheBlockֻ�õ���������־��B_DONE��B_DELWRI���ֱ��ʾ�Ѿ����IO���ӳ�д�ı�־��
//����Buffer���κα�־
CacheManager::CacheManager() 
{
	bufferList = new CacheBlock;
	InitList();
	diskDriver = &myDiskDriver;
}

CacheManager::~CacheManager() 
{
	Bflush();
	delete bufferList;
}

void CacheManager::FormatBuffer() 
{
	for (int i = 0; i < NBUF; ++i)
		nBuffer[i].Reset();
	InitList();
}

void CacheManager::InitList() 
{
	for (int i = 0; i < NBUF; ++i) {
		if (i) 
			nBuffer[i].forw = nBuffer + i - 1;
		else {
			nBuffer[i].forw = bufferList;
			bufferList->back = nBuffer + i;
		}

		if (i + 1 < NBUF)
			nBuffer[i].back = nBuffer + i + 1;
		else {
			nBuffer[i].back = bufferList;
			bufferList->forw = nBuffer + i;
		}
		nBuffer[i].addr = buffer[i];
		nBuffer[i].no = i;
	}
}

//����LRU Cache �㷨��ÿ�δ�ͷ��ȡ����ʹ�ú�ŵ�β��
void CacheManager::DetachNode(CacheBlock* pb) 
{
	if (pb->back == NULL)
		return;
	pb->forw->back = pb->back;
	pb->back->forw = pb->forw;
	pb->back = NULL;
	pb->forw = NULL;
}

void CacheManager::InsertTail(CacheBlock* pb) 
{
	if (pb->back != NULL)
		return;
	pb->forw = bufferList->forw;
	pb->back = bufferList;
	bufferList->forw->back = pb;
	bufferList->forw = pb;
}

//����һ�黺�棬�ӻ��������ȡ�������ڶ�д�豸�ϵĿ�blkno
CacheBlock* CacheManager::GetBlk(int blkno) 
{
	CacheBlock* pb;
	if (map.find(blkno) != map.end()) {
		pb = map[blkno];
		DetachNode(pb);
		return pb;
	}
	pb = bufferList->back;
	if (pb == bufferList) {
		cout << "�޻����ɹ�ʹ��" << endl;
		return NULL;
	}
	DetachNode(pb);
	map.erase(pb->blkno);
	if (pb->flags & CacheBlock::CB_DELWRI)
		diskDriver->write(pb->addr, BUFFER_SIZE, pb->blkno * BUFFER_SIZE);
	pb->flags &= ~(CacheBlock::CB_DELWRI | CacheBlock::CB_DONE);
	pb->blkno = blkno;
	map[blkno] = pb;
	return pb;
}

//�ͷŻ�����ƿ�buf
void CacheManager::Brelse(CacheBlock* pb) 
{
	InsertTail(pb);
}

//��һ�����̿飬blknoΪĿ����̿��߼����
CacheBlock* CacheManager::Bread(int blkno) 
{
	CacheBlock* pb = GetBlk(blkno);
	if (pb->flags & (CacheBlock::CB_DONE | CacheBlock::CB_DELWRI)) 
		return pb;
	diskDriver->read(pb->addr, BUFFER_SIZE, pb->blkno * BUFFER_SIZE);
	pb->flags |= CacheBlock::CB_DONE;
	return pb;
}

//дһ�����̿�
void CacheManager::Bwrite(CacheBlock* pb) 
{
	pb->flags &= ~(CacheBlock::CB_DELWRI);
	diskDriver->write(pb->addr, BUFFER_SIZE, pb->blkno * BUFFER_SIZE);
	pb->flags |= (CacheBlock::CB_DONE);
	this->Brelse(pb);
}

//�ӳ�д���̿�
void CacheManager::Bdwrite(CacheBlock* bp) 
{
	bp->flags |= (CacheBlock::CB_DELWRI | CacheBlock::CB_DONE);
	this->Brelse(bp);
	return;
}

//��ջ���������
void CacheManager::Bclear(CacheBlock* bp) 
{
	memset(bp->addr, 0, CacheManager::BUFFER_SIZE);
	return;
}

//���������ӳ�д�Ļ���ȫ�����������
void CacheManager::Bflush() 
{
	CacheBlock* pb = NULL;
	for (int i = 0; i < NBUF; ++i) {
		pb = nBuffer + i;
		if ((pb->flags & CacheBlock::CB_DELWRI)) {
			pb->flags &= ~(CacheBlock::CB_DELWRI);
			diskDriver->write(pb->addr, BUFFER_SIZE, pb->blkno * BUFFER_SIZE);
			pb->flags |= (CacheBlock::CB_DONE);
		}
	}
}
