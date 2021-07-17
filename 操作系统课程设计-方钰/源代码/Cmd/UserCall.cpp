#include "SystemCall.h"
#include "UserCall.h"
#include "Common.h"
#include <iostream>
#include <fstream>
using namespace std;

extern SystemCall mySystemCall;
//    extern��һ���ؼ��֣������߱�����������һ����������һ������������ڵ�ǰ��������ǰ��
//��û���ҵ���Ӧ�ı������ߺ�����Ҳ���ڵ�ǰ�ļ��ĺ�����������ļ��ж���

UserCall::UserCall() 
{
	userErrorCode = U_NOERROR;  //��Ŵ�����
	systemCall = &mySystemCall; 

	dirp = "/";                                   //ϵͳ���ò���(һ������Pathname)��ָ��
	curDirPath = "/";                             //��ǰ����Ŀ¼����·��
	nowDirINodePointer = systemCall->rootDirINode;//ָ��ǰĿ¼��Inodeָ��
	paDirINodePointer = NULL;                     //ָ��Ŀ¼��Inodeָ��
	memset(arg, 0, sizeof(arg));                  //ָ�����ջ�ֳ���������EAX�Ĵ���
}

UserCall::~UserCall() {}

//�˺����ı�Usercall�����dirp(ϵͳ���ò��� һ������Pathname)���ݳ�Ա
//ֻ����ļ����Ƿ����
bool UserCall::checkPathName(string path) 
{
	if (path.empty()) {
		cout << "����·��Ϊ��" << endl;
		return false;
	}

	if (path[0] == '/' || path.substr(0, 2) != "..")
		dirp = path;            //ϵͳ���ò���(һ������Pathname)��ָ��
	else {
		if (curDirPath.back() != '/')
			curDirPath += '/';
		string pre = curDirPath;//��ǰ����Ŀ¼����·�� cd����Ż�ı�curDirPath��ֵ
		unsigned int p = 0;
		//���Զ������·�� .. ../../
		for (; pre.length() > 3 && p < path.length() && path.substr(p, 2) == ".."; ) {
			pre.pop_back();
			pre.erase(pre.find_last_of('/') + 1);
			p += 2;
			p += p < path.length() && path[p] == '/';
		}
		dirp = pre + path.substr(p);
	}

	if (dirp.length() > 1 && dirp.back() == '/')
		dirp.pop_back();

	for (unsigned int p = 0, q = 0; p < dirp.length(); p = q + 1) {
		q = dirp.find('/', p);
		q = Common::min(q, (unsigned int)dirp.length());
		if (q - p > DirectoryEntry::DIRSIZ) {
			cout << "�ļ������ļ���������" << endl;
			return false;
		}
	}
	return true;
}

void UserCall::userMkDir(string dirName) 
{
	if (!checkPathName(dirName))
		return;
	arg[1] = INode::IFDIR;//��ŵ�ǰϵͳ���ò��� �ļ����ͣ�Ŀ¼�ļ�
	systemCall->Creat();
	checkError();
}

void UserCall::userLs() 
{
	ls.clear();
	systemCall->Ls();
	if (checkError())
		return;
	cout << ls << endl;
}

void UserCall::userRename(string ori, string cur)
{
	string curDir = curDirPath;
	if (!checkPathName(ori))
		return;
	if (!checkPathName(cur))
		return;
	if (ori.find('/') != string::npos) {
		string nextDir = ori.substr(0, ori.find_last_of('/'));
		userCd(nextDir);
		ori = ori.substr(ori.find_last_of('/') + 1);
		if (cur.find('/') != string::npos)
			cur = cur.substr(cur.find_last_of('/') + 1);
	}
	systemCall->Rename(ori, cur);
	userCd(curDir);
	if (checkError())
		return;
}

void UserCall::__userTree__(string path, int depth)
{
	vector<string> dirs;
	string nextDir;
	ls.clear();
	systemCall->Ls();
	for (int i = 0, p = 0; i < ls.length(); ) {
		p = ls.find('\n', i);
		dirs.emplace_back(ls.substr(i, p - i));
		i = p + 1;
	}
	for (int i = 0; i < dirs.size(); i++) {
		nextDir = (path == "/" ? "" : path) + '/' + dirs[i];
		for (int i = 0; i < depth + 1; i++)
			cout << "|   ";
		cout << "|---" << dirs[i] << endl;
		__userCd__(nextDir);
		if (userErrorCode != UserCall::U_NOERROR) {//���ʵ��ļ�
			userErrorCode = UserCall::U_NOERROR;
			continue;
		}
		__userTree__(nextDir, depth + 1);
	}
	__userCd__(path);
	return;
}

void UserCall::userTree(string path)
{
	if (curDirPath.length() > 1 && curDirPath.back() == '/')
		curDirPath.pop_back();
	string curDir = curDirPath;

	if (path == "") 
		path = curDir;

	if (!checkPathName(path))
		return;

	path = dirp;
	__userCd__(path);
	if (userErrorCode != UserCall::U_NOERROR) {//���ʵ��ļ�
		cout << "Ŀ¼·�������ڣ�" << endl;
		userErrorCode = UserCall::U_NOERROR;
		__userCd__(curDir);
		return;
	}
	cout << "|---" << (path == "/" ? "/" : path.substr(path.find_last_of('/') + 1)) << endl;
	__userTree__(path, 0);
	__userCd__(curDir);
}

void UserCall::__userCd__(string dirName)
{
	if (!checkPathName(dirName))
		return;
	systemCall->ChDir();
}

void UserCall::userCd(string dirName) 
{
	if (!checkPathName(dirName))
		return;
	systemCall->ChDir();
	checkError();
}

void UserCall::userCreate(string fileName) 
{
	if (!checkPathName(fileName))
		return;
	arg[1] = (INode::IREAD | INode::IWRITE);//��ŵ�ǰϵͳ���ò���
	systemCall->Creat();
	checkError();
}

void UserCall::userDelete(string fileName) 
{
	if (!checkPathName(fileName))
		return;
	systemCall->UnLink();
	checkError();
}

void UserCall::userOpen(string fileName) 
{
	if (!checkPathName(fileName))
		return;
	arg[1] = (File::FREAD | File::FWRITE);//��ŵ�ǰϵͳ���ò���
	systemCall->Open();
	if (checkError())
		return;
	cout << "���ļ��ɹ������ص��ļ����fdΪ " << ar0[UserCall::EAX] << endl;
}

//����sfd���
void UserCall::userClose(string sfd) 
{
	arg[0] = stoi(sfd);//��ŵ�ǰϵͳ���ò���
	systemCall->Close();
	checkError();
}

void UserCall::userSeek(string sfd, string offset, string origin) 
{
	arg[0] = stoi(sfd);
	arg[1] = stoi(offset);
	arg[2] = stoi(origin);
	systemCall->Seek();
	checkError();
}

void UserCall::userWrite(string sfd, string inFile, string size) 
{
	int fd = stoi(sfd), usize = 0;
	if (size.empty() || (usize = stoi(size)) < 0) {
		cout << "����������ڵ����� ! \n";
		return;
	}
	char* buffer = new char[usize];
	fstream fin(inFile, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "���ļ�" << inFile << "ʧ��" << endl;
		return;
	}
	fin.read(buffer, usize);
	fin.close();
	arg[0] = fd;
	arg[1] = (int)buffer;
	arg[2] = usize;
	systemCall->Write();

	if (checkError())
		return;
	cout << "�ɹ�д��" << ar0[UserCall::EAX] << "�ֽ�" << endl;
	delete[] buffer;
}

void UserCall::userRead(string sfd, string outFile, string size) 
{
	int fd = stoi(sfd);
	int usize = stoi(size);
	char* buffer = new char[usize];
	arg[0] = fd;
	arg[1] = (int)buffer;
	arg[2] = usize;
	systemCall->Read();
	if (checkError())
		return;

	cout << "�ɹ�����" << ar0[UserCall::EAX] << "�ֽ�" << endl;
	if (outFile == "std") {
		for (uint32 i = 0; i < ar0[UserCall::EAX]; ++i)
			cout << (char)buffer[i];
		cout << endl;
		delete[] buffer;
		return;
	}
	else {
		fstream fout(outFile, ios::out | ios::binary);
		if (!fout) {
			cout << "���ļ�" << outFile << "ʧ��" << endl;
			return;
		}
		fout.write(buffer, ar0[UserCall::EAX]);
		fout.close();
		delete[] buffer;
		return;
	}
}

bool UserCall::checkError() 
{
	if (userErrorCode != U_NOERROR) {
		switch (userErrorCode) {
		case UserCall::U_ENOENT:
			cout << "�Ҳ����ļ������ļ���" << endl;
			break;
		case UserCall::U_EBADF:
			cout << "�Ҳ����ļ����" << endl;
			break;
		case UserCall::U_EACCES:
			cout << "Ȩ�޲���" << endl;
			break;
		case UserCall::U_ENOTDIR:
			cout << "�ļ��в�����" << endl;
			break;
		case UserCall::U_ENFILE:
			cout << "�ļ������" << endl;
			break;
		case UserCall::U_EMFILE:
			cout << "���ļ�����" << endl;
			break;
		case UserCall::U_EFBIG:
			cout << "�ļ�����" << endl;
			break;
		case UserCall::U_ENOSPC:
			cout << "���̿ռ䲻��" << endl;
			break;
		default:
			break;
		}

		userErrorCode = U_NOERROR;
		return true;
	}
	return false;
}
