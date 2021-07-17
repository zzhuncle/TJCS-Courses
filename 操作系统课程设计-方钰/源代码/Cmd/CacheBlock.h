#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
using namespace std;

/* �����
*     �����Ӧ�������̺ţ�����ı�־���Ƿ��Ѿ���Ӳ��ͬ�����������ӳ�д����
* �������Լ������ǰ��ָ�����Ϣ��
*/
//���ڱ��ογ�����в�����ڶ���豸������ȡ�������е��豸���У������ֻ������� NODEV �����С�
//������ͷŵĲ���Ҳ�ǳ��򵥣������ǴӶ���ͷȡ��һ������飬�ͷ�ʱ���û�����־λ�û�����ڶ���β����
class CacheBlock
{
public:
	//flags�еı�־λ
	enum CacheBlockFlag
	{
		CB_DONE = 0x1,    //I/O��������
		CB_DELWRI = 0x2   //�ӳ�д����Ӧ�Ļ�����������;ʱ����������д����Ӧ�Ŀ��豸��
	};
	unsigned int flags;   //������ƿ��־λ

	CacheBlock* forw;    
	CacheBlock* back;

	int wcount;		      //�贫�͵��ֽ���
	unsigned char* addr;  //ָ��û�����ƿ�������Ļ��������׵�ַ
	int	blkno;		      //�����߼����
	int no;

	CacheBlock() 
	{
		flags = 0;
		forw = NULL;
		back = NULL;
		wcount = 0;
		addr = NULL;
		blkno = -1;
		no = 0;
	}

	void Reset() 
	{
		flags = 0;
		forw = NULL;
		back = NULL;
		wcount = 0;
		addr = NULL;
		blkno = -1;
		no = 0;
	}
};