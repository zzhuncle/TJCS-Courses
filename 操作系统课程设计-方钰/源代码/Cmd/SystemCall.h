#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"
#include "FileSystem.h"
#include "INode.h"
#include "OpenFileManager.h"

/*
*     SystemCall
*    ��װ���ļ�ϵͳ�ĸ���ϵͳ�����ں���̬�´�����̣�
* ����ļ���Open()��Close()��Read()��Write()�ȵ�
* ��װ�˶��ļ�ϵͳ���ʵľ���ϸ�ڡ�
*/
class SystemCall
{
public:
	//Ŀ¼����ģʽ������NameI()����
	enum DirectorySearchMode
	{
		OPEN = 0,   //�Դ��ļ���ʽ����Ŀ¼
		CREATE = 1, //���½��ļ���ʽ����Ŀ¼
		DELETE = 2  //��ɾ���ļ���ʽ����Ŀ¼
	};

public:

	INode* rootDirINode;         //��Ŀ¼�ڴ�INode
	FileSystem* fileSystem;      //��ȫ�ֶ���g_FileSystem�����ã��ö���������ļ�ϵͳ�洢��Դ
	INodeTable* inodeTable;      //��ȫ�ֶ���g_INodeTable�����ã��ö������ڴ�INode��Ĺ���
	OpenFileTable* openFileTable;//��ȫ�ֶ���g_OpenFileTable�����ã��ö�������ļ�����Ĺ���

public:
	SystemCall();
	~SystemCall();
	void Open();                          //Open()ϵͳ���ô������
	void Creat();                         //Creat()ϵͳ���ô������
	void Open1(INode* pINode, int trf);   //Open()��Creat()ϵͳ���õĹ�������
	void Close();                         //Close()ϵͳ���ô������                  
	void Seek();                          //Seek()ϵͳ���ô������
	void Read();                          //Read()ϵͳ���ô������
	void Write();                         //Write()ϵͳ���ô������
	void Rdwr(enum File::FileFlags mode); //��дϵͳ���ù������ִ���
	INode* NameI(enum DirectorySearchMode mode);//Ŀ¼��������·��ת��Ϊ��Ӧ��INode�����������INode
	INode* MakNode(int mode);             //��Creat()ϵͳ����ʹ�ã�����Ϊ�������ļ������ں���Դ
	void UnLink();                        //ȡ���ļ�
	void WriteDir(INode* pINode);         //��Ŀ¼��Ŀ¼�ļ�д��һ��Ŀ¼��
	void ChDir();                         //�ı䵱ǰ����Ŀ¼
	void Ls();                            //�г���ǰINode�ڵ���ļ���
	void Rename(string ori, string cur);  //�������ļ����ļ���
};
