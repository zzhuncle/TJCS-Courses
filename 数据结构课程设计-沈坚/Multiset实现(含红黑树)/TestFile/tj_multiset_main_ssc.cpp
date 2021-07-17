
#include <iostream>
#include <string>
#include<set>
#include "tj_student.h"
#include "tj_multiset.cpp"
using namespace std;

/* ���궨��ע�͵�������ϵͳset�Ĳ��ԣ�
   �򿪺궨�壬������Լ��� tj_set */
#define	multiset	tj_multiset


void press_key(int num, const char *prompt)
{
	int i;
	cout << endl << prompt << "�������������...";
	for (i = 0; i < num; i++)
		getchar();
	cout << endl;
}

string tmp = "test";
int main()
{
	//int
	if (1)
	{
		press_key(1, "\n key=int,value=int���ԣ�\n");
		int test_int[] = { 1,1,1,1,1,1,1,1 }; //ÿ��1��Ӧ1��if����
		// ��1����� 
		if (test_int[0]) {
			press_key(1, "��1����ԣ�\n size()��empty()����");
			cout << "������map" << endl;
			multiset<int>m1;
			cout << "empty()����: " << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << m1.empty() << endl;
			cout << "size()����: " << endl;
			cout << "Ӧ�����0" << endl;
			cout << "ʵ���ǣ�" << m1.size() << endl;
		}
		if (test_int[1]) {
			press_key(1, "��2����ԣ�\n �������뷽ʽ");
			multiset<int>m1;
			cout << "map�и�ֵ" << endl;
			m1.insert(1);
			cout << "insert(   int   )��ʽ����ɹ�" << endl;
			cout << "empty()����: " << endl;
			cout << "Ӧ�����0" << endl;
			cout << "ʵ���ǣ�" << m1.empty() << endl;
			cout << "size()����: " << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << m1.size() << endl;

			m1.emplace(2);
			cout << "emplace��ʽ����ɹ�" << endl;
			cout << "empty()����: " << endl;
			cout << "Ӧ�����0" << endl;
			cout << "ʵ���ǣ�" << m1.empty() << endl;
			cout << "size()����: " << endl;
			cout << "Ӧ�����2" << endl;
			cout << "ʵ���ǣ�" << m1.size() << endl;

			for (auto p = m1.begin(); p != m1.end(); p++) {
				cout << (*p) << endl;
			}

			cout << endl << "����" << endl;
			cout << "Ӧ�����1 2" << endl;
			cout << "ʵ���ǣ�";
			multiset<int>m2 = m1;
			for (auto p = m1.begin(); p != m1.end(); p++) {
				cout << (*p) << " ";
			}

			cout << endl << "��ֵ" << endl;
			multiset<int>m3;
			m3 = m1;
			cout << "Ӧ�����1 2" << endl;
			cout << "ʵ���ǣ�";
			for (auto p = m1.begin(); p != m1.end(); p++) {
				cout << (*p) << " ";
			}
			cout << endl;
		}
		// ��2����� 
		if (test_int[2]) {
			press_key(1, "��3����ԣ�\n begin/end/��rbegin/rend/����");

			multiset<int>m1;
			for (int i = 1; i <= 5; i++)
				m1.insert(i);
			cout << "����(����): " << endl;
			cout << "Ӧ�����1 2 3 4 5" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = m1.begin(); it != m1.end(); it++) {
				cout << (*it) << " ";
			}
			cout << endl;

			cout << endl;

			cout << "����(����): " << endl;
			cout << "Ӧ�����5 4 3 2 1 " << endl;
			cout << "ʵ���ǣ�";
			for (auto it = m1.rbegin(); it != m1.rend(); ++it) {
				cout << (*it) << " ";
			}
			cout << endl;

			cout << endl;

			multiset<int>m2;
			cout << "���Ե�map��СΪ0ʱbegin��end�Ƿ����" << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << (m2.begin() == m2.end()) << endl;

			cout << endl;

			cout << "���Ե�map��СΪ0ʱrbegin��rend�Ƿ����" << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << (m2.rbegin() == m2.rend());

			cout << endl << endl;
		}

		// ��4����� 
		if (test_int[3]) {
			press_key(1, "��4����ԣ�\n erase��insert");
			cout << "insert�Ĳ���";
			multiset<int>m1;
			for (int i = 1; i <= 5; i++)
				m1.emplace(i);
			multiset<int>m2;
			for (int i = 5; i <= 10; i++)
				m2.insert(i);
			auto q = m2.begin();
			q++; q++;
			m1.insert(m2.begin(), q);
			cout << "���Ӧ����:\n1 2 3 4 5 5 6 " << endl << "ʵ����: \n";
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << " ";
			cout << endl;
			cout << endl;

			cout << "erase�Ĳ���";
			q = m1.end();
			q = m1.erase(--q);
			cout << "����erase�ķ���ֵ �����Ӧ���� 1,  " << "ʵ����: ";
			cout << (q == m1.end()) << endl;
			cout << "ɾ��һ��Ԫ��" << endl;
			cout << "���Ӧ����:\n1 2 3 4 5 5 " << endl << "ʵ����: \n";
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << " ";
			cout << endl;
			cout << endl;
			q = m1.begin();
			q++;
			auto q_e = m1.end();
			m1.erase(q, q_e);
			cout << "ɾ�����Ԫ��" << endl;
			cout << "���Ӧ����: 1" << endl << "ʵ����: ";
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << "  ";
			cout << endl;
		}

		// ��5����� 
		if (test_int[4]) {
			press_key(1, "��5����ԣ�\n find()/lower_bound()/upper_bound()/count()");
			multiset<int>m1;
			for (int i = 1; i <= 5; i++)
				m1.emplace(i);
			for (int i = 1; i <= 3; i++)
				m1.emplace(2);
			auto n1 = m1.find(2);
			cout << "find()�Ĳ���,Ӧ���� 2 ��ʵ����";
			cout << (*n1) << endl;
			auto n2 = m1.lower_bound(2);
			cout << "lower_bound()�Ĳ���,Ӧ���� 2 ��ʵ���� ";
			cout << (*n2) << endl;
			n2 = m1.upper_bound(2);
			cout << "upper_bound()�Ĳ���,Ӧ����3 ��ʵ����";
			cout << (*n2) << endl;

			cout << "count()�Ĳ���,Ӧ����4��ʵ����";
			cout << m1.count(2) << endl;
			cout << "count()�Ĳ���,Ӧ����0��ʵ����";
			cout << m1.count(16) << endl;
			cout << endl << "findʧ�ܵ����" << endl;

			auto p1 = m1.find(100);
			cout << "find()�Ҳ����ڵ�ֵ�Ĳ���,Ӧ��1��ʵ����  ";
			cout << (p1 == m1.end()) << endl;
			auto p2 = m1.lower_bound(100);
			cout << "lower_bound()�Ҳ����ڵ�ֵ�Ĳ���,Ӧ��1��ʵ����  ";
			cout << (p2 == m1.end()) << endl;
			auto p3 = m1.upper_bound(100);
			cout << "upper_bound()�Ҳ����ڵ�ֵ�Ĳ���,Ӧ��1��ʵ����  ";
			cout << (p3 == m1.end()) << endl;
		}

		// ��6����� 
		if (test_int[5]) {
			press_key(1, "��6����ԣ�\n key_comp");
			multiset<int>m1;
			bool r;
			r = m1.key_comp()(3, 5);
			cout << "key_comp()�Ĳ��ԣ����Ӧ���ǣ�1��ʵ����";
			cout << r << endl;
			r = m1.key_comp()(3, 3);
			cout << "key_comp()�Ĳ��ԣ����Ӧ���ǣ�0��ʵ����";
			cout << r << endl;
			r = m1.key_comp()(5, 3);
			cout << "key_comp()�Ĳ��ԣ����Ӧ���ǣ�0��ʵ����";
			cout << r << endl;
		}

		// ��7����� 
		if (test_int[6]) {

			press_key(1, "��7����ԣ�\n swap()  ");
			multiset<int>m1;
			multiset<int>m2;
			for (int i = 1; i <= 3; i++)
				m1.emplace(i);
			for (int i = 8; i <= 9; i++)
				m2.emplace(i);

			cout << "swap()�Ĳ���" << endl;
			m1.swap(m2);
			cout << "m1 Ӧ���� 8 9��ʵ����";
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << "  ";
			cout << endl;
			cout << "m2 Ӧ����1 2 3��ʵ����";
			for (auto p = m2.begin(); p != m2.end(); p++)
				cout << (*p) << "  ";
			cout << endl;
			cout << "�ٴν����Ĳ���" << endl;
			m1.swap(m2);
			cout << "m1 Ӧ����1 2 3��ʵ����";
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << "  ";
			cout << endl;
			cout << "m2 Ӧ����8 9��ʵ����";
			for (auto p = m2.begin(); p != m2.end(); p++)
				cout << (*p) << "  ";
			cout << endl;
		}
		// ��8����� 
		if (test_int[7]) {

			press_key(1, "��8����ԣ����ز���,clear���� ");
			multiset<int>m1;
			multiset<int>m2;
			for (int i = 1; i <= 5; i++)
				m1.emplace(i);
			for (int i = 1; i <= 3; i++)
				m2.emplace(i);
			for (int i = 8; i <= 12; i++)
				m2.emplace(i);
			cout << "<�Ų���" << "Ӧ���  1��ʵ�����" << (m1 < m2) << endl;
			cout << ">�Ų���" << "Ӧ���  0��ʵ�����" << (m1 > m2) << endl;
			cout << "=�Ų���" << "Ӧ���  0��ʵ�����" << (m1 == m2) << endl;

			m1.clear();
			m2.clear();
			cout << "clear m1,Ӧ��� 1��ʵ�����" << m1.empty() << endl;
			cout << "clear m2,Ӧ��� 1��ʵ�����" << m2.empty() << endl;
			cout << "<�Ų���" << "Ӧ���  0��ʵ�����" << (m1 < m2) << endl;
			cout << ">�Ų���" << "Ӧ���  0��ʵ�����" << (m1 > m2) << endl;
			cout << "=�Ų���" << "Ӧ���  1��ʵ�����" << (m1 == m2) << endl;
		}
	}
	//string
	if (1) {
		press_key(1, "\n string��\n");
		int test_int[] = { 1,1,1,1,1,1,1,1,1 }; //ÿ��1��Ӧ1��if����
		// ��1����� 
		if (test_int[0]) {
			press_key(1, "��1����ԣ�\n size()��empty()����");
			cout << "������map" << endl;
			multiset<string>m1;
			cout << "empty()����: " << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << m1.empty() << endl;
			cout << "size()����: " << endl;
			cout << "Ӧ�����0" << endl;
			cout << "ʵ���ǣ�" << m1.size() << endl;
		}
		if (test_int[1]) {
			press_key(1, "��2����ԣ�\n �������뷽ʽ");
			multiset<string>m1;
			cout << "map�и�ֵ" << endl;
			m1.insert("test1");
			cout << "insert(   string   )��ʽ����ɹ�" << endl;
			cout << "empty()����: " << endl;
			cout << "Ӧ�����0" << endl;
			cout << "ʵ���ǣ�" << m1.empty() << endl;
			cout << "size()����: " << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << m1.size() << endl;

			m1.emplace("test2");
			cout << "emplace��ʽ����ɹ�" << endl;
			cout << "empty()����: " << endl;
			cout << "Ӧ�����0" << endl;
			cout << "ʵ���ǣ�" << m1.empty() << endl;
			cout << "size()����: " << endl;
			cout << "Ӧ�����2" << endl;
			cout << "ʵ���ǣ�" << m1.size() << endl;

			for (auto p = m1.begin(); p != m1.end(); p++) {
				cout << (*p) << endl;
			}

			cout << endl << "����" << endl;
			cout << "Ӧ�����test1 test2" << endl;
			cout << "ʵ���ǣ�";
			multiset<string>m2 = m1;
			for (auto p = m1.begin(); p != m1.end(); p++) {
				cout << (*p) << " ";
			}

			cout << endl << "��ֵ" << endl;
			multiset<string>m3;
			m3 = m1;
			cout << "Ӧ�����test1 test2" << endl;
			cout << "ʵ���ǣ�";
			for (auto p = m1.begin(); p != m1.end(); p++) {
				cout << (*p) << " ";
			}
			cout << endl;
		}
		// ��2����� 
		if (test_int[2]) {
			press_key(1, "��3����ԣ�\n begin/end/��rbegin/rend/����");
			multiset<string>m1;
			for (int i = 1; i <= 5; i++)
				m1.emplace(tmp + char('0' + i));
			cout << "����(����): " << endl;
			cout << "Ӧ�����test1 test2 test3 test4 test5" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = m1.begin(); it != m1.end(); it++) {
				cout << (*it) << " ";
			}
			cout << endl;

			cout << endl;




			cout << "����(����): " << endl;
			cout << "Ӧ�����test5 test4 test3 test2 test1" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = m1.rbegin(); it != m1.rend(); ++it) {
				cout << (*it) << " ";
			}
			cout << endl;

			cout << endl;

			multiset<int>m2;
			cout << "���Ե�map��СΪ0ʱbegin��end�Ƿ����" << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << (m2.begin() == m2.end()) << endl;

			cout << endl;

			cout << "���Ե�map��СΪ0ʱrbegin��rend�Ƿ����" << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << (m2.rbegin() == m2.rend());

			cout << endl << endl;
		}

		// ��4����� 
		if (test_int[3]) {
			press_key(1, "��4����ԣ�\n erase��insert");
			cout << "insert�Ĳ���";
			multiset<string>m1;
			for (int i = 1; i <= 5; i++)
				m1.emplace(tmp + char('0' + i));
			multiset<string>m2;
			for (int i = 5; i <= 9; i++)
				m2.insert(tmp + char('0' + i));
			auto q = m2.begin();
			q++; q++;
			m1.insert(m2.begin(), q);
			cout << "���Ӧ����:\ntest1 test2 test3 test4 test5 test5 test6 " << endl << "ʵ����: \n";
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << " ";
			cout << endl;
			cout << endl;

			cout << "erase�Ĳ���";
			q = m1.end();
			q = m1.erase(--q);
			cout << "����erase�ķ���ֵ �����Ӧ���� 1,  " << "ʵ����: ";
			cout << (q == m1.end()) << endl;
			cout << "ɾ��һ��Ԫ��" << endl;
			cout << "���Ӧ����:\n test1 test2 test3 test4 test5 test5 " << endl << "ʵ����: \n";
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << " ";
			cout << endl;
			cout << endl;
			q = m1.begin();
			q++;
			auto q_e = m1.end();
			m1.erase(q, q_e);
			cout << "ɾ�����Ԫ��" << endl;
			cout << "���Ӧ����: test1" << endl << "ʵ����: ";
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << "  ";
			cout << endl;
		}

		// ��5����� 
		if (test_int[4]) {
			press_key(1, "��5����ԣ�\n find()/lower_bound()/upper_bound()/count()");
			multiset<string>m1;
			for (int i = 1; i <= 5; i++)
				m1.emplace(tmp + char('0' + i));
			for (int i = 1; i <= 3; i++)
				m1.emplace("test2");
			auto n1 = m1.find("test2");
			cout << "find()�Ĳ���,Ӧ����test2��ʵ����";
			cout << (*n1) << endl;
			auto n2 = m1.lower_bound("test2");
			cout << "lower_bound()�Ĳ���,Ӧ����test2��ʵ����";
			cout << (*n2) << endl;
			n2 = m1.upper_bound("test2");
			cout << "upper_bound()�Ĳ���,Ӧ����test3��ʵ����";
			cout << (*n2) << endl;

			cout << "count()�Ĳ���,Ӧ����4��ʵ����";
			cout << m1.count("test2") << endl;

			cout << endl << "findʧ�ܵ����" << endl;

			auto p1 = m1.find("test200");
			cout << "find()�Ҳ����ڵ�ֵ�Ĳ���,Ӧ��1��ʵ����  ";
			cout << (p1 == m1.end()) << endl;
			auto p2 = m1.lower_bound("test200");
			cout << "lower_bound()�Ҳ����ڵ�ֵ�Ĳ���,Ӧ��0��ʵ����  ";
			cout << (p2 == m1.end()) << endl;
			auto p3 = m1.upper_bound("test200");
			cout << "upper_bound()�Ҳ����ڵ�ֵ�Ĳ���,Ӧ��0��ʵ����  ";
			cout << (p3 == m1.end()) << endl;
		}

		// ��6����� 
		if (test_int[5]) {
			press_key(1, "��6����ԣ�\n key_comp");
			multiset<string>m1;
			bool r;
			r = m1.key_comp()("test200", "test300");
			cout << "key_comp()�Ĳ��ԣ����Ӧ���ǣ�1��ʵ����";
			cout << r << endl;
			r = m1.key_comp()("test300", "test300");
			cout << "key_comp()�Ĳ��ԣ����Ӧ���ǣ�0��ʵ����";
			cout << r << endl;
			r = m1.key_comp()("test300", "test200");
			cout << "key_comp()�Ĳ��ԣ����Ӧ���ǣ�0��ʵ����";
			cout << r << endl;
		}

		// ��7����� 
		if (test_int[6]) {

			press_key(1, "��7����ԣ�\n swap()  ");
			multiset<string>m1;
			multiset<string>m2;
			for (int i = 1; i <= 3; i++)
				m1.emplace(tmp + char('0' + i));
			for (int i = 8; i <= 9; i++)
				m2.emplace(tmp + char('0' + i));

			cout << "swap()�Ĳ���" << endl;
			m1.swap(m2);
			cout << "m1 Ӧ���� test8 test9��ʵ����";
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << "  ";
			cout << endl;
			cout << "m2 Ӧ����test1 test2 test3��ʵ����";
			for (auto p = m2.begin(); p != m2.end(); p++)
				cout << (*p) << "  ";
			cout << endl;
			cout << "�ٴν����Ĳ���" << endl;
			m1.swap(m2);
			cout << "m1 Ӧ����test1 test2 test3��ʵ����";
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << "  ";
			cout << endl;
			cout << "m2 Ӧ����test8 test9��ʵ����";
			for (auto p = m2.begin(); p != m2.end(); p++)
				cout << (*p) << "  ";
			cout << endl;
		}
		// ��8����� 
		if (test_int[7]) {

			press_key(1, "��8����ԣ����ز���,clear���� ");
			multiset<string>m1;
			multiset<string>m2;
			for (int i = 1; i <= 5; i++)
				m1.emplace(tmp + char('0' + i));
			for (int i = 1; i <= 3; i++)
				m2.emplace(tmp + char('0' + i));
			for (int i = 8; i <= 9; i++)
				m2.emplace(tmp + char('0' + i));
			cout << "<�Ų���" << "Ӧ���  1��ʵ�����" << (m1 < m2) << endl;
			cout << ">�Ų���" << "Ӧ���  0��ʵ�����" << (m1 > m2) << endl;
			cout << "=�Ų���" << "Ӧ���  0��ʵ�����" << (m1 == m2) << endl;

			m1.clear();
			m2.clear();
			cout << "clear m1,Ӧ��� 1��ʵ�����" << m1.empty() << endl;
			cout << "clear m2,Ӧ��� 1��ʵ�����" << m2.empty() << endl;
			cout << "<�Ų���" << "Ӧ���  0��ʵ�����" << (m1 < m2) << endl;
			cout << ">�Ų���" << "Ӧ���  0��ʵ�����" << (m1 > m2) << endl;
			cout << "=�Ų���" << "Ӧ���  1��ʵ�����" << (m1 == m2) << endl;
		}

		// ��9����� 
		if (test_int[9])
		{
			press_key(1, "��5����ԣ���ͬ���Ĳ��� ");
			multiset<string>m1;
			for (int i = 1; i <= 5; i++)
				m1.emplace(tmp + char('1'));
			cout << "Ӧ�����" << endl;
			cout << "test1" << endl;
			cout << "test1" << endl;
			cout << "test1" << endl;
			cout << "test1" << endl;
			cout << "test1" << endl;
			cout << "ʵ���ǣ�" << endl;
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << endl;
			cout << endl;
			cout << endl;
		}
	}

	if (1) {
		press_key(1, "\n student���ԣ�\n");
		int test_int[] = { 1,1,1,1,1 }; //ÿ��1��Ӧ1��if����
		student t[4] = { {1001,"t1",'M',81,"test1" },{1002,"t2",'F',82,"test2" },
								{1003,"t3",'M',83,"test3" } ,{1004,"t4",'F',84,"test4" } };

		// ��1����� 
		if (test_int[0]) {
			press_key(1, "��1����ԣ�\n size()��empty()����");
			cout << "������map" << endl;
			multiset<student>m1;
			cout << "empty()����: " << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << m1.empty() << endl;
			cout << "size()����: " << endl;
			cout << "Ӧ�����0" << endl;
			cout << "ʵ���ǣ�" << m1.size() << endl;
		}
		if (test_int[1]) {
			press_key(1, "��2����ԣ�\n �������뷽ʽ");
			multiset<student>m1;
			cout << "map�и�ֵ" << endl;
			m1.insert(t[0]);
			cout << "insert(   student   )��ʽ����ɹ�" << endl;
			cout << "empty()����: " << endl;
			cout << "Ӧ�����0" << endl;
			cout << "ʵ���ǣ�" << m1.empty() << endl;
			cout << "size()����: " << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << m1.size() << endl;

			m1.emplace(t[1]);
			cout << "emplace��ʽ����ɹ�" << endl;
			cout << "empty()����: " << endl;
			cout << "Ӧ�����0" << endl;
			cout << "ʵ���ǣ�" << m1.empty() << endl;
			cout << "size()����: " << endl;
			cout << "Ӧ�����2" << endl;
			cout << "ʵ���ǣ�" << m1.size() << endl;

			for (auto p = m1.begin(); p != m1.end(); p++) {
				cout << (*p) << endl;
			}

			cout << endl << "����" << endl;
			cout << "Ӧ�����1001 t1 M 81 test1        1002 t2 F 82 test2" << endl;
			cout << "ʵ���ǣ�";
			multiset<student>m2 = m1;
			for (auto p = m1.begin(); p != m1.end(); p++) {
				cout << (*p) << "        ";
			}

			cout << endl << "��ֵ" << endl;
			multiset<student>m3;
			m3 = m1;
			cout << "Ӧ�����1001 t1 M 81 test1        1002 t2 F 82 test2" << endl;
			cout << "ʵ���ǣ�";
			for (auto p = m1.begin(); p != m1.end(); p++) {
				cout << (*p) << "        ";
			}
			cout << endl;
		}
		// ��2����� 
		if (test_int[2]) {
			press_key(1, "��3����ԣ�\n begin/end/��rbegin/rend/����");
			multiset<student>m1;
			for (int i = 2; i >= 0; i--)
				m1.emplace(t[i]);
			cout << "����(����): " << endl;
			cout << "Ӧ�����\n" << endl;
			cout << "1001 t1 M 81 test1" << endl;
			cout << "1002 t2 F 82 test2" << endl;
			cout << "1003 t3 M 83 test3" << endl;
			cout << "ʵ���ǣ�\n";
			for (auto it = m1.begin(); it != m1.end(); it++) {
				cout << (*it) << endl;
			}
			cout << endl;

			cout << endl;

			cout << "����(����): " << endl;
			cout << "Ӧ�����\n" << endl;
			cout << "1003 t3 M 83 test3" << endl;
			cout << "1002 t2 F 82 test2" << endl;
			cout << "1001 t1 M 81 test1" << endl;

			cout << "ʵ���ǣ�\n";
			for (auto it = m1.rbegin(); it != m1.rend(); ++it) {
				cout << (*it) << endl;
			}
			cout << endl;

			cout << endl;

			multiset<student> m2;
			cout << "���Ե�map��СΪ0ʱbegin��end�Ƿ����" << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << (m2.begin() == m2.end()) << endl;

			cout << endl;

			cout << "���Ե�map��СΪ0ʱrbegin��rend�Ƿ����" << endl;
			cout << "Ӧ�����1" << endl;
			cout << "ʵ���ǣ�" << (m2.rbegin() == m2.rend());

			cout << endl << endl;
		}

		// ��4����� 
		if (test_int[3]) {
			press_key(1, "��4����ԣ�\n erase��insert");
			cout << "insert�Ĳ���";
			multiset<student>m1;
			for (int i = 0; i <= 1; i++)
				m1.emplace(t[i]);
			multiset<student>m2;
			for (int i = 0; i <= 3; i++)
				m2.insert(t[i]);
			auto q = m2.begin();
			q++; q++;
			m1.insert(m2.begin(), q);
			cout << "Ӧ�����" << endl;
			cout << "1001 t1 M 81 test1" << endl;
			cout << "1001 t1 M 81 test1" << endl;
			cout << "1002 t2 F 82 test2" << endl;
			cout << "1002 t2 F 82 test2" << endl;
			cout << "ʵ���ǣ�" << endl;
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << endl;
			cout << endl;
			cout << endl;

			cout << "erase�Ĳ���";
			q = m1.end();
			q = m1.erase(--q);
			cout << "����erase�ķ���ֵ �����Ӧ���� 1,  " << "ʵ����: ";
			cout << (q == m1.end()) << endl;
			cout << "ɾ��һ��Ԫ��" << endl;
			cout << "Ӧ�����" << endl;
			cout << "1001 t1 M 81 test1" << endl;
			cout << "1001 t1 M 81 test1" << endl;
			cout << "1002 t2 F 82 test2" << endl;
			cout << "ʵ���ǣ�" << endl;
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << endl;
			cout << endl;
			cout << endl;
		}

		// ��5����� 
		if (test_int[4]) {

			press_key(1, "��5����ԣ���ͬ���Ĳ��� ");
			multiset<student>m1;
			for (int i = 0; i <= 3; i++)
				m1.emplace(t[0]);
			cout << "Ӧ�����" << endl;
			cout << "1001 t1 M 81 test1" << endl;
			cout << "1001 t1 M 81 test1" << endl;
			cout << "1001 t1 M 81 test1" << endl;
			cout << "1001 t1 M 81 test1" << endl;
			cout << "ʵ���ǣ�" << endl;
			for (auto p = m1.begin(); p != m1.end(); p++)
				cout << (*p) << endl;
			cout << endl;
			cout << endl;

		}
	}
	return 0;
}
