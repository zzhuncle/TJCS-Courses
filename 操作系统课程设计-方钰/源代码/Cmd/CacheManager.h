#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "DiskDriver.h"
#include "CacheBlock.h"
#include <unordered_map>
using namespace std;

class CacheManager 
{
public:
	static const int NBUF = 100;            //������ƿ顢������������
	static const int BUFFER_SIZE = 512;     //��������С�� ���ֽ�Ϊ��λ

private:
	CacheBlock* bufferList;                 //���ɻ�����п��ƿ�
	CacheBlock nBuffer[NBUF];               //������ƿ�����
	unsigned char buffer[NBUF][BUFFER_SIZE];//����������
	unordered_map<int, CacheBlock*> map;
	DiskDriver* diskDriver;

public:
	CacheManager();
	~CacheManager();
	CacheBlock* GetBlk(int blkno);         //����һ�黺�棬���ڶ�д�豸�ϵĿ�blkno
	void Brelse(CacheBlock* bp);           //�ͷŻ�����ƿ�buf
	CacheBlock* Bread(int blkno);          //��һ�����̿飬blknoΪĿ����̿��߼����
	void Bwrite(CacheBlock* bp);           //дһ�����̿�
	void Bdwrite(CacheBlock* bp);          //�ӳ�д���̿�
	void Bclear(CacheBlock* bp);           //��ջ���������
	void Bflush();                         //���������ӳ�д�Ļ���ȫ�����������
	void FormatBuffer();                   //��ʽ������Buffer

private:
	void InitList();                 //������ƿ���еĳ�ʼ��
	void DetachNode(CacheBlock* pb);
	void InsertTail(CacheBlock* pb);
};