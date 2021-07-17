#define _CRT_SECURE_NO_WARNINGS
#include "DiskDriver.h"
#include "CacheManager.h"
#include "OpenFileManager.h"
#include "SystemCall.h"
#include "UserCall.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;

DiskDriver myDiskDriver;
CacheManager myCacheManager;
OpenFileTable myOpenFileTable;
SuperBlock mySuperBlock;
FileSystem myFileSystem;
INodeTable myINodeTable;
SystemCall mySystemCall;
UserCall myUserCall;

bool AutoTest()
{
	UserCall& User = myUserCall;
	cout << "ע�⣺�Զ����Բ�������ʽ������" << endl;
	cout << "���ڲ��Գ����е��ļ����д�����������֮ǰ�򿪹��ļ����ܻ�ִ�г��������һ�����Զ�����" << endl;
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "mkdir /bin" << endl;
	User.userMkDir("/bin");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "mkdir /etc" << endl;
	User.userMkDir("/etc");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "mkdir /home" << endl;
	User.userMkDir("/home");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "mkdir /dev" << endl;
	User.userMkDir("/dev");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "ls" << endl;
	User.userLs();

	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "mkdir /home/texts" << endl;
	User.userMkDir("/home/texts");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "mkdir /home/reports" << endl;
	User.userMkDir("/home/reports");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "mkdir /home/photos" << endl;
	User.userMkDir("/home/photos");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "ftree /" << endl;
	User.userTree("/");

	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "cd /home/texts" << endl;
	User.userCd("/home/texts");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fcreate Readme.txt" << endl;
	User.userCreate("Readme.txt");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fopen Readme.txt" << endl;
	User.userOpen("Readme.txt");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fwrite 8 Readme.txt 2609" << endl;
	User.userWrite("8", "Readme.txt", "2609");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fseek 8 0 begin" << endl;
	User.userSeek("8", "0", "0");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fread 8 ReadmeOut.txt 2609" << endl;
	User.userRead("8", "ReadmeOut.txt", "2609");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fclose 8" << endl;
	User.userClose("8");

	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "cd /home/reports" << endl;
	User.userCd("/home/reports");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fcreate Report.pdf" << endl;
	User.userCreate("Report.pdf");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fopen Report.pdf" << endl;
	User.userOpen("Report.pdf");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fwrite 9 Report.pdf 1604288" << endl; 
	User.userWrite("9", "Report.pdf", "1604288");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fseek 9 0 begin" << endl; 
	User.userSeek("9", "0", "0");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fread 9 ReportOut.pdf 1604288" << endl;
	User.userRead("9", "ReportOut.pdf", "1604288");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fclose 9" << endl;
	User.userClose("9");

	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "cd /home/photos" << endl;
	User.userCd("/home/photos");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fcreate DennisRitchie.jpg" << endl;
	User.userCreate("DennisRitchie.jpg");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fopen DennisRitchie.jpg" << endl;
	User.userOpen("DennisRitchie.jpg");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fwrite 10 DennisRitchie.jpg 7402" << endl;
	User.userWrite("10", "DennisRitchie.jpg", "7402");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fread 10 DennisRitchieOut.jpg 7402" << endl;
	User.userSeek("10", "0", "0");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fclose 10" << endl;
	User.userRead("10", "DennisRitchieOut.jpg", "7402");

	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "mkdir /test" << endl; 
	User.userMkDir("/test");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "cd /test" << endl; 
	User.userCd("/test");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fcreate Jerry" << endl;
	User.userCreate("Jerry");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fopen Jerry" << endl; 
	User.userOpen("Jerry");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fwrite 13 input.txt 800" << endl;
	User.userWrite("13", "input.txt", "800");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fseek 13 500 begin" << endl;
	User.userSeek("13", "500", "0");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fread 13 std 500" << endl; 
	User.userRead("13", "std", "500");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fseek 13 500 begin" << endl;
	User.userSeek("13", "500", "0");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fread 13 abc.txt 500" << endl; 
	User.userRead("13", "abc.txt", "500");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fwrite 13 abc.txt 300" << endl;
	User.userWrite("13", "abc.txt", "300");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "fclose 13" << endl;
	User.userClose("13");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "ftree /" << endl;
	User.userTree("/");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "cd /test" << endl;
	User.userCd("/test");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "frename Jerry Larry" << endl;
	User.userRename("Jerry", "Larry");
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "ls" << endl;
	User.userLs();
	cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ " << "ftree /" << endl;
	User.userTree("/");

	cout << "�Զ����Խ���" << endl << endl;
	return true;
}

int main() 
{
	UserCall& User = myUserCall;
	cout << "***************************************************************************************" << endl
		<< "*                                                                                     *" << endl
		<< "*                                   ��Unix�ļ�ϵͳ                                    *" << endl
		<< "*                                                                                     *" << endl
		<< "* [����˵��]:                                                                         *" << endl
		<< "* [����]:help <op_name>\t[����]:������ʾ                                               *" << endl
		<< "* [����]:test\t[����]:�Զ�����                                                       *" << endl
		<< "* [����]:fformat\t[����]:��ʽ���ļ�ϵͳ                                         *" << endl
		<< "* [����]:ls\t[����]:�鿴��ǰĿ¼����                                               *" << endl
		<< "* [����]:mkdir <dirname>\t[����]:�����ļ���                                     *" << endl
		<< "* [����]:cd <dirname>\t[����]:����Ŀ¼                                               *" << endl
		<< "* [����]:fcreate <filename>\t[����]:�����ļ���Ϊfilename���ļ�                     *" << endl
		<< "* [����]:fopen <filename>\t[����]:���ļ���Ϊfilename���ļ�                     *" << endl
		<< "* [����]:fwrite <fd> <infile> <size>\t[����]:��infile���룬д��fd�ļ�size�ֽ�       *" << endl
		<< "* [����]:fread <fd> <outfile> <size>\t[����]:��fd�ļ���ȡsize�ֽڣ������outfile    *" << endl
		<< "* [����]:fread <fd> std <size>\t[����]:��fd�ļ���ȡsize�ֽڣ��������Ļ               *" << endl
		<< "* [����]:fseek <fd> <step> begin\t[����]:��beginģʽ��fd�ļ�ָ��ƫ��step        *" << endl
		<< "* [����]:fseek <fd> <step> cur\t[����]:��curģʽ��fd�ļ�ָ��ƫ��step                  *" << endl
		<< "* [����]:fseek <fd> <step> end\t[����]:��endģʽ��fd�ļ�ָ��ƫ��step                  *" << endl
		<< "* [����]:fclose <fd>\t[����]:�ر��ļ����Ϊfd���ļ�                                 *" << endl
		<< "* [����]:fdelete <filename>\t[����]:ɾ���ļ��ļ���Ϊfilename���ļ������ļ���       *" << endl
		<< "* [����]:frename <filename> <filename1>\t[����]:���ļ�fliename������Ϊfilename1        *" << endl
		<< "* [����]:ftree <dirname>\t[����]:�г�dirname���ļ�Ŀ¼��                        *" << endl
		<< "* [����]:exit \t[����]:�˳�ϵͳ�������������ݴ�������                                 *" << endl
		<< "***************************************************************************************" << endl;

	string line, opt, val[3];
	while (true) 
	{
		cout << "[1853790-ZZH-OS " << User.curDirPath << " ]$ ";
		getline(cin, line);
		if (line.size() == 0) 
			continue;

		stringstream in(line);
		in >> opt;
		val[0] = val[1] = val[2] = "";
		
		//��ʽ���ļ�ϵͳ
		if (opt == "fformat") {
			//Us.userCd("/");
			myOpenFileTable.Reset();
			myINodeTable.Reset();
			myCacheManager.FormatBuffer();
			myFileSystem.FormatDevice();
			//myUserCall.ofiles.Reset();
			cout << "��ʽ����ϣ��ļ�ϵͳ���˳���������������" << endl;
			return 0;
		}
		//�鿴��ǰĿ¼����
		else if (opt == "ls")
			User.userLs();
		//�����ļ���
		else if (opt == "mkdir") {
			in >> val[0];
			if (val[0][0] != '/')
				val[0] = User.curDirPath + val[0];
			User.userMkDir(val[0]);
		}
		//����Ŀ¼
		else if (opt == "cd") {
			in >> val[0];
			User.userCd(val[0]);
		}
		//�����ļ���Ϊfilename���ļ�
		else if (opt == "fcreate") {
			in >> val[0];
			if (val[0][0] != '/')
				val[0] = User.curDirPath + val[0];
			User.userCreate(val[0]);
		}
		//���ļ���Ϊfilename���ļ�
		else if (opt == "fopen") {
			in >> val[0];
			if (myUserCall.ar0[UserCall::EAX] == 0) {
				User.userMkDir("demo");
				User.userDelete("demo");
			}
			if (val[0][0] != '/')
				val[0] = User.curDirPath + val[0];
			
			User.userOpen(val[0]);
		}
		//�˳�ϵͳ�������������ݴ�������
		else if (opt == "exit")
			return 0;
		//�ر��ļ����Ϊfd���ļ�
		else if (opt == "fclose") {
			in >> val[0];
			User.userClose(val[0]);
		}
		else if (opt == "fseek") {
			in >> val[0] >> val[1] >> val[2];
			//��beginģʽ��fd�ļ�ָ��ƫ��step
			if (val[2] == "begin")
				User.userSeek(val[0], val[1], string("0"));
			//��curģʽ��fd�ļ�ָ��ƫ��step
			else if (val[2] == "cur")
				User.userSeek(val[0], val[1], string("1"));
			//��endģʽ��fd�ļ�ָ��ƫ��step
			else if (val[2] == "end")
				User.userSeek(val[0], val[1], string("2"));
		}
		//��fd�ļ���ȡsize�ֽڣ������outfile
		//��fd�ļ���ȡsize�ֽڣ��������Ļ
		else if (opt == "fread") {
			in >> val[0] >> val[1] >> val[2];
			User.userRead(val[0], val[1], val[2]);
		}
		//��infile���룬д��fd�ļ�size�ֽ�
		else if (opt == "fwrite") {
			in >> val[0] >> val[1] >> val[2];
			User.userWrite(val[0], val[1], val[2]);
		}
		//ɾ���ļ��ļ���Ϊfilename���ļ������ļ���
		else if (opt == "fdelete") {
			in >> val[0];
			if (val[0][0] != '/')
				val[0] = User.curDirPath + val[0];
			User.userDelete(val[0]);
		}
		else if (opt == "test")
			AutoTest();
		//�������ļ����ļ���
		else if (opt == "frename") {
			in >> val[0] >> val[1];
			User.userRename(val[0], val[1]);
		}
		else if (opt == "ftree") {
			in >> val[0];
			User.userTree(val[0]);
		}
		else if (opt == "help") {
			in >> val[0];
			if (val[0] == "" || val[0] == "?") {
				cout << "[����]:test\t[����]:�Զ�����" << endl
					<< "[����]:fformat\t[����]:��ʽ���ļ�ϵͳ" << endl
					<< "[����]:ls\t[����]:�鿴��ǰĿ¼����" << endl
					<< "[����]:mkdir <dirname>\t[����]:�����ļ���" << endl
					<< "[����]:cd <dirname>\t[����]:����Ŀ¼" << endl
					<< "[����]:fcreate <filename>\t[����]:�����ļ���Ϊfilename���ļ�" << endl
					<< "[����]:fopen <filename>\t[����]:���ļ���Ϊfilename���ļ�" << endl
					<< "[����]:fwrite <fd> <infile> <size>\t[����]:��infile���룬д��fd�ļ�size�ֽ�" << endl
					<< "[����]:fread <fd> <outfile> <size>\t[����]:��fd�ļ���ȡsize�ֽڣ������outfile" << endl
					<< "[����]:fread <fd> std <size>\t[����]:��fd�ļ���ȡsize�ֽڣ��������Ļ" << endl
					<< "[����]:fseek <fd> <step> begin\t[����]:��beginģʽ��fd�ļ�ָ��ƫ��step" << endl
					<< "[����]:fseek <fd> <step> cur\t[����]:��curģʽ��fd�ļ�ָ��ƫ��step" << endl
					<< "[����]:fseek <fd> <step> end\t[����]:��endģʽ��fd�ļ�ָ��ƫ��step" << endl
					<< "[����]:fclose <fd>\t[����]:�ر��ļ����Ϊfd���ļ�" << endl
					<< "[����]:fdelete <filename>\t[����]:ɾ���ļ��ļ���Ϊfilename���ļ������ļ���" << endl
					<< "[����]:frename <filename> <filename1>\t[����]:���ļ�fliename������Ϊfilename1" << endl
					<< "[����]:ftree <dirname>\t[����]:�г�dirname���ļ�Ŀ¼��" << endl
					<< "[����]:exit\t[����]:�˳�ϵͳ�������������ݴ�������" << endl;
			}
			else if (val[0] == "test")
				cout << "[����]:test\t[����]:�Զ�����" << endl;
			else if (val[0] == "fformat")
				cout << "[����]:fformat\t[����]:��ʽ���ļ�ϵͳ" << endl;
			else if (val[0] == "ls")
				cout << "[����]:ls\t[����]:�鿴��ǰĿ¼����" << endl;
			else if (val[0] == "mkdir")
				cout << "[����]:mkdir <dirname>\t[����]:�����ļ���" << endl;
			else if (val[0] == "cd")
				cout << "[����]:cd <dirname>\t[����]:����Ŀ¼" << endl;
			else if (val[0] == "fcreate")
				cout << "[����]:fcreate <filename>\t[����]:�����ļ���Ϊfilename���ļ�" << endl;
			else if (val[0] == "fopen")
				cout << "[����]:fopen <filename>\t[����]:���ļ���Ϊfilename���ļ�" << endl;
			else if (val[0] == "fwrite")
				cout << "[����]:fwrite <fd> <infile> <size>\t[����]:��infile���룬д��fd�ļ�size�ֽ�" << endl;
			else if (val[0] == "fread")
				cout << "[����]:fread <fd> <outfile> <size>\t[����]:��fd�ļ���ȡsize�ֽڣ������outfile" << endl
				<< "[����]:fread <fd> std <size>\t[����]:��fd�ļ���ȡsize�ֽڣ��������Ļ" << endl;
			else if (val[0] == "fseek")
				cout << "[����]:fseek <fd> <step> begin\t[����]:��beginģʽ��fd�ļ�ָ��ƫ��step" << endl
				<< "[����]:fseek <fd> <step> cur\t[����]:��curģʽ��fd�ļ�ָ��ƫ��step" << endl
				<< "[����]:fseek <fd> <step> end\t[����]:��endģʽ��fd�ļ�ָ��ƫ��step" << endl;
			else if (val[0] == "fclose")
				cout << "[����]:fclose <fd>\t[����]:�ر��ļ����Ϊfd���ļ�" << endl;
			else if (val[0] == "fdelete")
				cout << "[����]:fdelete <filename>\t[����]:ɾ���ļ��ļ���Ϊfilename���ļ������ļ���" << endl;
			else if (val[0] == "frename")
				cout << "[����]:frename <filename> <filename1>\t[����]:���ļ�fliename������Ϊfilename1" << endl;
			else if (val[0] == "ftree")
				cout << "[����]:ftree <dirname>\t[����]:�г�dirname���ļ�Ŀ¼��" << endl;
			else if (val[0] == "exit")
				cout << "[����]:exit\t[����]:�˳�ϵͳ�������������ݴ�������" << endl;
		}
	}
	return 0;
}