#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "INode.h"
#include "CacheManager.h"
#include "DiskDriver.h"
/* �����ļ��ṹ��SuperBlock + DiskINode + �ļ������� */

/* �ļ�ϵͳ�洢��Դ�����(SuperBlock�ṹ) 1024�ֽ� */
class SuperBlock 
{
public:
	const static int MAX_NUMBER_FREE = 100;
	const static int MAX_NUMBER_INODE = 100;

public:
	int	s_isize;		        //���INode��ռ�õ��̿��� 1022
	int	s_fsize;		        //�ļ�ϵͳ�������̿�����  16384 - 1024 = 15360

	int	s_nfree;		        //ֱ�ӹ���Ŀ����̿�����
	int	s_free[MAX_NUMBER_FREE];//ֱ�ӹ���Ŀ����̿�������

	int	s_ninode;		          //ֱ�ӹ���Ŀ������INode����
	int	s_inode[MAX_NUMBER_INODE];//ֱ�ӹ���Ŀ������INode������

	int	s_fmod;			        //�ڴ���super block�������޸ı�־����ζ����Ҫ��������Ӧ��Super Block
	int	s_time;			        //���һ�θ���ʱ��
	int	padding[50];	        //���ʹSuperBlock���С����1024�ֽڣ�ռ��2������
};

/* DiskINode�ڵ�������ṹ 32�ֽ� */
class DirectoryEntry 
{
public:
	static const int DIRSIZ = 28;//Ŀ¼����·�����ֵ�����ַ�������
public:
	int m_ino;                   //Ŀ¼����INode��Ų��֣�����Ӧ�ļ��ڿ��豸�ϵ���������ڵ��
	char name[DIRSIZ];           //Ŀ¼����·��������
};

class FileSystem 
{
public:
	static const int BLOCK_SIZE = 512;           //Block���С����λ�ֽ�
	static const int DISK_SECTOR_NUMBER = 16384; //���������������� 8MB / 512B = 16384  
	static const int SUPERBLOCK_START_SECTOR = 0;//����SuperBlockλ�ڴ����ϵ������ţ�ռ����������
	static const int INODE_START_SECTOR = 2;     //���INode��λ�ڴ����ϵ���ʼ������
	static const int INODE_SECTOR_NUMBER = 1022; //���������INode��ռ�ݵ�������
	static const int INODE_SIZE = sizeof(DiskINode);//64�ֽ�
	static const int INODE_NUMBER_PER_SECTOR = BLOCK_SIZE / INODE_SIZE;//���INode���󳤶�Ϊ64�ֽڣ�ÿ�����̿���Դ��512/64 = 8�����INode
	static const int ROOT_INODE_NO = 0;          //�ļ�ϵͳ��Ŀ¼���INode���
	static const int INODE_NUMBER_ALL = INODE_SECTOR_NUMBER * INODE_NUMBER_PER_SECTOR; //���INode���ܸ���
	static const int DATA_START_SECTOR = INODE_START_SECTOR + INODE_SECTOR_NUMBER;     //����������ʼ������    
	static const int DATA_END_SECTOR = DISK_SECTOR_NUMBER - 1;                         //�����������������
	static const int DATA_SECTOR_NUMBER = DISK_SECTOR_NUMBER - DATA_START_SECTOR;      //������ռ�ݵ���������

	DiskDriver* diskDriver;
	SuperBlock* superBlock;
	CacheManager* cacheManager;

	FileSystem();
	~FileSystem();

	void FormatSuperBlock();//��ʽ��SuperBlock
	void FormatDevice();    //��ʽ�������ļ�ϵͳ

	/* �ڲ���ϵͳ��ʼ��ʱ���Ὣ���̵�SuperBlock����һ���ڴ��SuperBlock�������Ա����ں��Ը�����ٶ���ʱ�����ڴ渱����
	һ���ڴ��еĸ��������仯����ͨ������s_fmod��־�����ں˽��ڴ渱��д����� */
	void LoadSuperBlock();  //ϵͳ��ʼ��ʱ����SuperBlock
	void Update();          //��SuperBlock������ڴ渱�����µ��洢�豸��SuperBlock��ȥ

	/* ����Inode�ڵ�ķ���������㷨�����ʵ�� */
	INode* IAlloc();        //�ڴ洢�豸�Ϸ���һ���������INode��һ�����ڴ����µ��ļ�
	void IFree(int number); //�ͷű��Ϊnumber�����INode��һ������ɾ���ļ�

	CacheBlock* Alloc();    //�ڴ洢�豸�Ϸ�����д��̿�   
	void Free(int blkno);   //�ͷŴ洢�豸�ϱ��Ϊblkno�Ĵ��̿�
};
