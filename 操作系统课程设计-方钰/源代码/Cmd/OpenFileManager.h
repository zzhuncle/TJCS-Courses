#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "File.h"
#include "FileSystem.h"

/*    ���ļ�������(OpenFileManager)�����ں��жԴ��ļ������Ĺ���Ϊ���̴��ļ�������
 * �����ݽṹ֮��Ĺ�����ϵ��
 * ������ϵָ����u���д��ļ�������ָ����ļ����е�File���ļ����ƽṹ���Լ���File
 * �ṹָ���ļ���Ӧ���ڴ�INode��
 */
class OpenFileTable {
public:
	static const int MAX_FILES = 100;        // ���ļ����ƿ�File�ṹ������

public:
	File sysFileTable[MAX_FILES];            //ϵͳ���ļ���Ϊ���н��̹������̴�
	                                         //�ļ����������а���ָ����ļ����ж�ӦFile�ṹ��ָ��
public:
	OpenFileTable();
	~OpenFileTable();
	void Reset();
	File* FAlloc();                          //��ϵͳ���ļ����з���һ�����е�File�ṹ
	void CloseF(File* pFile);                //�Դ��ļ����ƿ�File�ṹ�����ü���count��1�������ü���countΪ0�����ͷ�File�ṹ
};

/*    �ڴ�INode��(class INodeTable)
 * �����ڴ�INode�ķ�����ͷš�
 */
class INodeTable {
public:
	static const int NINODE = 100;           //�ڴ�INode������
private:
	INode m_INodeTable[NINODE];              //�ڴ�INode���飬ÿ�����ļ�����ռ��һ���ڴ�INode
	FileSystem* fileSystem;                  //��ȫ�ֶ���g_FileSystem������

public:
	INodeTable();
	~INodeTable();
	INode* IGet(int inumber);                //�������INode��Ż�ȡ��ӦINode�������INode�Ѿ����ڴ��У����ظ��ڴ�INode��
		                                       //��������ڴ��У���������ڴ�����������ظ��ڴ�INode
	void IPut(INode* pNode);                 //���ٸ��ڴ�INode�����ü����������INode�Ѿ�û��Ŀ¼��ָ������
		                                       //���޽������ø�INode�����ͷŴ��ļ�ռ�õĴ��̿�
	void UpdateINodeTable();                 //�����б��޸Ĺ����ڴ�INode���µ���Ӧ���INode��
	int IsLoaded(int inumber);               //�����Ϊinumber�����INode�Ƿ����ڴ濽����
		                                       //������򷵻ظ��ڴ�INode���ڴ�INode���е�����
	INode* GetFreeINode();                   //���ڴ�INode����Ѱ��һ�����е��ڴ�INode
	void Reset();
};