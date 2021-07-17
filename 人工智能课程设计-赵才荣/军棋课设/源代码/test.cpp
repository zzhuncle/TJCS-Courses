#include<cstdio>
#include<iostream>
#include<fstream>
#include<iomanip>
#include <algorithm> //for find(vector)
#include <sstream> //for istringstream

#include"AB_agent.h"
#include"common.h"
#include"ncn.h"
#include"tools.h"
using namespace std;
/**
* @file			test.cpp
* @brief        ����ncn������ת��
* @param[in]    Ncn��
* @param[out]   ��ӡ����״̬��û���ӵ�λ��Ϊ0�����ӵ�λ����ʾ�ڲ������ֵ����Ӫ��*���
* @author       ssc
* @date			2020.04.18
* @version		0.0.1
*/
void test_ncn(const char s[])
{
	array<array<int, 5>, 13> board = {};
	int a = 0, b = 0;
	parse_ncn(board, s, a, b);
	LBChess t(board);
	t.seetheboard();
}

/**
* @file			test.cpp
* @brief        �������ӿ��Դﵽ��λ��
* @param[in]    Ncn��
* @param[out]   ��ӡ����״̬�������������ڵ�λ����*����������ߵ�λ����1�����ܵ���λ����0
* @author       ssc
* @date			2020.04.20
* @version		0.0.1
*/
void test_move(const int row, const int col, const char s[])
{
	vector<int>res;
	array<array<int, 5>, 13> board = {};
	int a = 0, b = 0;
	parse_ncn(board, s, a, b);//����ncn��ת��������
	LBChess t(board);
	t.seetheboard();//��ʾ�����ʽ
	cout << endl << endl;
	t.get(position2int(row, col), res);//�õ����Ե���λ�ã�����res
	char r[13][5];
	int i, j;
	for (i = 0; i < 13; i++)
		for (j = 0; j < 5; j++)
			r[i][j] = '0';
	r[row][col] = '*';//����һ����ά���飬��ʼȫ��0��Ȼ��ǰλ����*

	for (int i = 0; i < res.size(); i++)
		r[res[i] / 5][res[i] % 5] = '1';//���ص�vector�ж�Ӧ��λ�ã��ڶ�ά��������1
	//��ӡ��ά����
	for (i = 0; i < 13; i++) {
		for (j = 0; j < 5; j++)
			cout << r[i][j] << "  ";
		cout << endl;
	}
}

const int NCN_MAXSIZE = 100;	//ncn����󳤶�

static inline void get_option(char optchar[], string& optstr)
{
	cin.getline(optchar, NCN_MAXSIZE);	//�������Խ����ָ��
	cin.clear();						//good��1
	cin.sync();							//��ջ�����
	optstr = string(optchar);			//ת��string��
}

static inline void post_option(const string opt)
{
	cout << opt << endl;			//����淢��ָ�endl�Զ���ջ�����
}

static inline void parse_option(const string opt, string& ncn, int& cnt, int& total_cnt)
{
	istringstream iss(opt);
	iss >> ncn >> cnt >> total_cnt; //��opt�ָ� xxx/.../xxx/ 0 1
}

static inline void print_log(ofstream& fout, string movement, array<array<int, 5>, 13> board)
{
	//�����ǰ���̵���־�ļ�
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 5; j++) {
			fout << board[i][j] << " ";
		}
		fout << endl;
	}
	fout << endl;
	//����ƶ�ָ���־�ļ�
	fout << movement << endl;
}

int time_limitation = (60 - 3) * 1000;

void test_agent(int role, int time)
{
	ofstream fout("time_per_step.txt", ios::app);
	time_limitation = (time - 3) * 1000;

	array<array<int, 5>, 13> board = { 0 }; //���̣���ʼֵ=ȫ0
	char buf[NCN_MAXSIZE]; //��ָ����ַ�����
	string opt, ncn; //����ָ�ncn�� 
	int cnt = 0, total_cnt = 0; //������һ�γ��Ӳ������ܲ���

	post_option("ready"); //����淢��ready��Ϣ

	if (role == 1) { //�ڷ����⴦������ǰ���ܵ���ʼ���̵�ָ��
		get_option(buf, opt); //��ȡ��ʼ���
		//opt.replace(0, 5, ""); //ȥ����ͷ��"init"
		//parse_option(opt, ncn, cnt, total_cnt); //�����������ncn���Ͳ���
	}

	get_option(buf, opt); //��ȡ��ʼ���
	array<array<int, 5>, 13> last_board2 = { 0 };
	array<array<int, 5>, 13> last_board1 = { 0 };
	bool flag;
	while (opt != "end") { //�����ܵ���ֽ�����������˳�
	 //parse_option(opt, ncn, cnt, total_cnt); //�����������ncn���Ͳ���
	 //board = zero_board; //��ʼ��board=ȫ0����Ӱ��Ч�ʣ����Ľ�
		parse_ncn(board, opt, cnt, total_cnt); //��������
		// Node* node = t.UCTSearch(role, board, (total_cnt / 2 == 0 ? true : false)); //UCT����������ӷ���
		//post_option(node->get_move()); //����淢���ƶ�ָ��
		flag = (last_board2 == board);
		last_board2 = last_board1;
		last_board1 = board;
		AB_agent ab_agent(role, board);
		int startTime = clock();
		string sss = ab_agent.runable(flag);
		fout << clock() - startTime << endl;
		post_option(sss);
		get_option(buf, opt); //�������Խ����ָ��

#if 0 //���˴���Ϊ1�������־�ļ�
  //��һ�غϵ�����״̬��δ�ƶ�ǰ�����ƶ�
		print_log(fout, sss, board);
#endif
	}

	fout.close();
}

#if 1
int main(int args, char* argv[])
{
	vector<string> argpaser; //����������
	int role = 1; //����role��-1��ʾ�췽��1��ʾ�ڷ���Ĭ��Ϊ�ڷ�1
	int time = 60; //����time����ʾ��������ʱ�䣬��λs

	// �����в���װ�������
	for (int i = 0; i < args; i++) {
		string arg(argv[i]);
		argpaser.push_back(arg);
	}

	auto it = find(argpaser.begin(), argpaser.end(), "--role");
	if (it != argpaser.end())
		role = stoi(*(it + 1));

	it = find(argpaser.begin(), argpaser.end(), "--time");
	if (it != argpaser.end())
		time = stoi(*(it + 1));

	string inti_ncn = "ppdfd/plldz/z1g1y/yt1ty/s1g1s/jvgva/5/jvgva/s1g1s/yt1ty/z1g1y/plldz/ppdfd";

	//test_move(2, 1, "5/1pg2/1gg11/212/s1g11/jvg11/5/jvgva/s1g1s/yt1ty/z1g1y/plldz/ppdfd");
	test_agent(role, time);
	return 0;
}
#else
int main()
{
	string init_ncn = "init 2dfd/3d1/p4/5/5/2a2/5/5/A4/2Y2/2L1Z/3D1/PLDFD 0 0";
	init_ncn.replace(0, 5, "");
	cout << init_ncn << endl;
	return 0;
	ofstream fout("log.txt", ios::out); //��־�ļ�
	UCT t;

	string ncn = "2dfd/3d1/p4/5/5/2a2/5/5/A4/2Y2/2L1Z/3D1/PLDFD";
	int cnt = 0, total_cnt = 0;
	array<array<int, 5>, 13> board = { 0 };
	parse_ncn(board, ncn, cnt, total_cnt);
	Node* node = t.UCTSearch(-1, board, (total_cnt / 2 == 0 ? true : false));
	cout << node->get_move() << endl;

	//�����ǰ���̵���־�ļ�
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 5; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	fout.close();
	return 0;
}
#endif