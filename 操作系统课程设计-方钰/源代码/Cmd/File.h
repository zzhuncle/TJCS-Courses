#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "INode.h"

/*    ���ļ����ƿ�File�ࡣ
 * �ýṹ��¼�˽��̴��ļ��Ķ���д�������ͣ��ļ���дλ�õȵȡ�
 */
class File
{
public:
	enum FileFlags 
	{
		FREAD = 0x1,	//����������
		FWRITE = 0x2,	//д��������
	};

public:
	File();
	~File();
	void Reset();

	unsigned int flag;	//�Դ��ļ��Ķ���д����Ҫ��
	int	count;		    //��ǰ���ø��ļ����ƿ�Ľ�����������Ϊ0���ʾ��File���У����Է���������
	INode* inode;		//ָ����ļ����ڴ�INodeָ��
	int	offset;		    //�ļ���дλ��ָ��
};

/*     ���̴��ļ���������(OpenFiles)�Ķ���
 * ά���˵�ǰ���̵����д��ļ���
 */
class ProcessOpenFile {
public:
	static const int MAX_FILES = 100;		//��������򿪵�����ļ���

private:
	File* processOpenFileTable[MAX_FILES];	//File�����ָ�����飬ָ��ϵͳ���ļ����е�File����

public:
	ProcessOpenFile();
	~ProcessOpenFile();
	void Reset()
	{
		memset(processOpenFileTable, 0, sizeof(processOpenFileTable));
	};
	int AllocFreeSlot();           //����������ļ�ʱ���ڴ��ļ����������з���һ�����б���
	File* GetF(int fd);            //�����û�ϵͳ�����ṩ���ļ�����������fd���ҵ���Ӧ�Ĵ��ļ����ƿ�File�ṹ	
	void SetF(int fd, File* pFile);//Ϊ�ѷ��䵽�Ŀ���������fd���ѷ���Ĵ��ļ����п���File������������ϵ
};

/*    �ļ�I/O�Ĳ�����
 * ���ļ�����дʱ���õ��Ķ���дƫ�������ֽ����Լ�Ŀ�������׵�ַ������
 */
class IOParameter {
public:
	unsigned char* base;	//��ǰ����д�û�Ŀ��������׵�ַ
	int offset;			    //��ǰ����д�ļ����ֽ�ƫ����
	int count;			    //��ǰ��ʣ��Ķ���д�ֽ�����
};
