#include <iostream>
#include <set>
#include <string>
#include <initializer_list>
#include "tj_multiset.cpp"
#include "tj_student.h"
using namespace std;


//����������
//1.���Ե���������Ϊint��string��student(6�ֹ�ϵ������������)���������������µĲ���������ȫ��ͬ�����ı�����������
//2.���Ը�����multiset��get_allcator��emplace_hint֮���ȫ�������������������ÿ���������������Ҳ�����˾��󲿷�
//3.���Խ�����������ȷ��ʹ�÷�ʽ��û�жԷǷ��Ĵ���ʹ�ý��в���
//4.������������⣬�뼰ʱ����


#define multiset tj_multiset
//���궨��ע�͵�������ϵͳmultiset�Ĳ��ԣ��򿪺궨�壬������Լ��� tj_multiset


/* press key */
void wait_for_next()
{
	cout << endl << "�밴�س�������..." << endl;
	while (getchar() != '\n')
		;
}


int main()
{
	//int
	if (1)
	{
		int test[] = { 1,1,1,1,1,1,1 };

		//��0����ԣ�insert+����������
		if (test[0])
		{
			cout << "��0����ԣ�insert/begin/end/cbegin/cend/rbegin/rend/crbegin/crend" << endl << endl;

			multiset<int> myset1;
			initializer_list<int> L = { 1,2,3 };
			myset1.insert(L);
			myset1.insert(4);
			myset1.insert(3);
			myset1.insert(6);
			myset1.insert(5);
			myset1.insert(6);

			cout << "Ӧ�����1 2 3 3 4 5 6 6" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.begin(); it != myset1.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			cout << "Ӧ�����1 2 3 3 4 5 6 6" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.cbegin(); it != myset1.cend(); it++)
				cout << *it << " ";
			cout << endl << endl;


			cout << "Ӧ�����6 6 5 4 3 3 2 1" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.rbegin(); it != myset1.rend(); it++)
				cout << *it << " ";
			cout << endl << endl;


			cout << "Ӧ�����6 6 5 4 3 3 2 1" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.crbegin(); it != myset1.crend(); it++)
				cout << *it << " ";
			cout << endl << endl;


			auto first = myset1.begin();
			auto last = myset1.end();
			multiset<int> myset2(first, last);
			myset2.insert(7);
			myset2.insert(6);
			cout << "Ӧ�����7 6 6 6 5 4 3 3 2 1" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset2.crbegin(); it != myset2.crend(); it++)
				cout << *it << " ";
			cout << endl;

			wait_for_next();
		}

		//��1����ԣ��������
		if (test[1])
		{
			cout << "��1����ԣ����캯��/=����" << endl << endl;


			initializer_list<int> L = { 1,3 };
			multiset<int> myset1(L);
			myset1.insert(2);
			cout << "Ӧ�����1 2 3" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.begin(); it != myset1.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			multiset<int> myset2(myset1);
			cout << "Ӧ�����1 2 3" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset2.begin(); it != myset2.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			multiset<int> myset3(myset1.begin(), myset1.end());
			cout << "Ӧ�����1 2 3" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset3.begin(); it != myset3.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			multiset<int> myset4 = myset1;
			cout << "Ӧ�����1 2 3" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset4.begin(); it != myset4.end(); it++)
				cout << *it << " ";
			cout << endl;

			wait_for_next();
		}

		//��2����ԣ��������
		if (test[2])
		{
			cout << "��2����ԣ�size/max_size/empty/count" << endl << endl;


			multiset<int> myset;
			cout << "mymapΪ�գ�Ӧ�����1" << endl;
			cout << "mymapΪ�գ�ʵ���ǣ�" << myset.empty();
			cout << endl << endl;


			myset.insert(4);
			myset.insert(3);
			myset.insert(2);
			myset.insert(1);
			myset.insert(3);
			myset.insert(5);
			cout << "mymap��Ϊ�գ���6��Ԫ�أ�Ӧ�����0 6" << endl;
			cout << "mymap��Ϊ�գ���6��Ԫ�أ�ʵ���ǣ�" << myset.empty() << " " << myset.size();
			cout << endl << endl;


			cout << "max_size()��������Բ�ͬ(214748364)" << endl;
			cout << "ʵ��Ϊ��" << myset.max_size();
			cout << endl << endl;


			cout << "Ӧ�����1 2 1 0 0 0" << endl;
			cout << "ʵ���ǣ�" << myset.count(1) << " " << myset.count(3) << " " << myset.count(5) << " ";
			cout << myset.count(33) << " " << myset.count(6) << " " << myset.count(11) << " ";
			cout << endl;

			wait_for_next();
		}

		//��3����ԣ�Ԫ�ز���
		if (test[3])
		{
			cout << "��3����ԣ�insert/erase/emplace/find" << endl << endl;


			multiset<int> myset;
			myset.insert(1);
			myset.insert(2);
			myset.insert(2);
			myset.insert(3);
			myset.insert(4);
			myset.insert(5);
			myset.insert(5);
			cout << "Ӧ�����1 2 2 3 4 5 5" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			myset.erase(myset.begin());
			myset.erase(myset.begin(), ++myset.begin());
			cout << "Ӧ�����2 3 4 5 5" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			myset.erase(5);
			cout << "Ӧ�����2 3 4" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			myset.emplace(1);
			myset.emplace(2);
			myset.emplace(3);
			myset.emplace(6);
			cout << "Ӧ�����1 2 2 3 3 4 6" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << *it << " ";
			cout << endl << endl;



			cout << "Ӧ�����2 6" << endl;
			cout << "ʵ���ǣ�";
			auto it = myset.find(1);
			cout << *++it << " ";
			it = myset.find(10);
			cout << *--it << " ";
			cout << endl;

			wait_for_next();
		}

		//��4����ԣ��������+��Χ����
		if (test[4])
		{
			cout << "��4����ԣ�clear/swap/equal_range/upper_bound/lower_bound" << endl << endl;


			multiset<int> myset1;
			myset1.insert(1);
			myset1.insert(2);
			myset1.insert(3);
			multiset<int> myset2 = myset1;
			myset2.emplace(4);
			myset2.emplace(5);
			myset2.emplace(4);
			myset1.swap(myset2);
			cout << "Ӧ�����6 3" << endl;
			cout << "ʵ���ǣ�";
			cout << myset1.size() << " " << myset2.size();
			cout << endl << endl;


			myset2.clear();
			myset1.swap(myset1);
			swap(myset1, myset2);
			cout << "Ӧ�����0 6" << endl;
			cout << "ʵ���ǣ�";
			cout << myset1.size() << " " << myset2.size();
			cout << endl << endl;


			auto range = myset2.equal_range(4);
			cout << "Ӧ�����4 5" << endl;
			cout << "ʵ���ǣ�";
			cout << *range.first << " " << *range.second;
			cout << endl << endl;


			auto lower = myset2.lower_bound(4);
			auto upper = myset2.upper_bound(4);
			cout << "Ӧ�����4 5" << endl;
			cout << "ʵ���ǣ�";
			cout << *lower << " " << *upper;
			cout << endl;

			wait_for_next();
		}

		//��5����ԣ���������
		if (test[5])
		{
			cout << "��5����ԣ�key_comp/value_comp" << endl << endl;


			multiset<int> mymap;
			auto key_compare = mymap.key_comp();
			cout << "Ӧ�����0 1 1" << endl;
			cout << "ʵ���ǣ�";
			cout << key_compare(1, 1) << " " << key_compare(1, 2) << " " << key_compare(0, 1);
			cout << endl << endl;


			auto value_compare = mymap.value_comp();
			cout << "Ӧ�����0 1 1" << endl;
			cout << "ʵ���ǣ�";
			cout << value_compare(1, 1) << " " << value_compare(1, 2) << " " << value_compare(0, 1);
			cout << endl;

			wait_for_next();
		}

		//��6����ԣ���ϵ�����
		if (test[6])
		{
			cout << "��6����ԣ�6����ϵ�����" << endl << endl;


			multiset<int> myset1;
			myset1.emplace(1);
			myset1.emplace(2);
			myset1.emplace(3);
			myset1.emplace(4);
			myset1.emplace(5);
			multiset<int> myset2 = myset1;
			cout << "Ӧ�����1 0 1 1 0 0" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl << endl;


			myset2.erase(5);
			cout << "Ӧ�����0 1 1 0 0 1" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl << endl;


			myset2.emplace(0);
			cout << "Ӧ�����0 1 1 0 0 1" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl << endl;


			myset2.erase(0);
			myset2.emplace(6);
			cout << "Ӧ�����0 1 0 1 1 0" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl;

			wait_for_next();
		}

	}

	//string
	if (1)
	{
		int test[] = { 1,1,1,1,1,1,1 };

		//��0����ԣ�insert+����������
		if (test[0])
		{
			cout << "��0����ԣ�insert/begin/end/cbegin/cend/rbegin/rend/crbegin/crend" << endl << endl;

			multiset<string> myset1;
			initializer_list<string> L = { "11","22","33" };
			myset1.insert(L);
			myset1.insert("44");
			myset1.insert("33");
			myset1.insert("66");
			myset1.insert("55");
			myset1.insert("66");

			cout << "Ӧ�����11 22 33 33 44 55 66 66" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.begin(); it != myset1.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			cout << "Ӧ�����11 22 33 33 44 55 66 66" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.cbegin(); it != myset1.cend(); it++)
				cout << *it << " ";
			cout << endl << endl;


			cout << "Ӧ�����66 66 55 44 33 33 22 11" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.rbegin(); it != myset1.rend(); it++)
				cout << *it << " ";
			cout << endl << endl;


			cout << "Ӧ�����66 66 55 44 33 33 22 11" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.crbegin(); it != myset1.crend(); it++)
				cout << *it << " ";
			cout << endl << endl;


			auto first = myset1.begin();
			auto last = myset1.end();
			multiset<string> myset2(first, last);
			myset2.insert("77");
			myset2.insert("66");
			cout << "Ӧ�����77 66 66 66 55 44 33 33 22 11" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset2.crbegin(); it != myset2.crend(); it++)
				cout << *it << " ";
			cout << endl;

			wait_for_next();
		}

		//��1����ԣ��������
		if (test[1])
		{
			cout << "��1����ԣ����캯��/=����" << endl << endl;


			initializer_list<string> L = { "11","33" };
			multiset<string> myset1(L);
			myset1.insert("22");
			cout << "Ӧ�����11 22 33" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.begin(); it != myset1.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			multiset<string> myset2(myset1);
			cout << "Ӧ�����11 22 33" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset2.begin(); it != myset2.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			multiset<string> myset3(myset1.begin(), myset1.end());
			cout << "Ӧ�����11 22 33" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset3.begin(); it != myset3.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			multiset<string> myset4 = myset1;
			cout << "Ӧ�����11 22 33" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset4.begin(); it != myset4.end(); it++)
				cout << *it << " ";
			cout << endl;

			wait_for_next();
		}

		//��2����ԣ��������
		if (test[2])
		{
			cout << "��2����ԣ�size/max_size/empty/count" << endl << endl;


			multiset<string> myset;
			cout << "mymapΪ�գ�Ӧ�����1" << endl;
			cout << "mymapΪ�գ�ʵ���ǣ�" << myset.empty();
			cout << endl << endl;


			myset.insert("44");
			myset.insert("33");
			myset.insert("22");
			myset.insert("11");
			myset.insert("33");
			myset.insert("55");
			cout << "mymap��Ϊ�գ���6��Ԫ�أ�Ӧ�����0 6" << endl;
			cout << "mymap��Ϊ�գ���6��Ԫ�أ�ʵ���ǣ�" << myset.empty() << " " << myset.size();
			cout << endl << endl;


			cout << "max_size()��������Բ�ͬ(214748364)" << endl;
			cout << "ʵ��Ϊ��" << myset.max_size();
			cout << endl << endl;


			cout << "Ӧ�����1 2 1 0 0 0" << endl;
			cout << "ʵ���ǣ�" << myset.count("11") << " " << myset.count("33") << " " << myset.count("55") << " ";
			cout << myset.count("23") << " " << myset.count("66") << " " << myset.count("111") << " ";
			cout << endl;

			wait_for_next();
		}

		//��3����ԣ�Ԫ�ز���
		if (test[3])
		{
			cout << "��3����ԣ�insert/erase/emplace/find" << endl << endl;


			multiset<string> myset;
			myset.insert("11");
			myset.insert("22");
			myset.insert("22");
			myset.insert("33");
			myset.insert("44");
			myset.insert("55");
			myset.insert("55");
			cout << "Ӧ�����11 22 22 33 44 55 55" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			myset.erase(myset.begin());
			myset.erase(myset.begin(), ++myset.begin());
			cout << "Ӧ�����22 33 44 55 55" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			myset.erase("55");
			cout << "Ӧ�����22 33 44" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << *it << " ";
			cout << endl << endl;


			myset.emplace("11");
			myset.emplace("22");
			myset.emplace("33");
			myset.emplace("66");
			cout << "Ӧ�����11 22 22 33 33 44 66" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << *it << " ";
			cout << endl << endl;



			cout << "Ӧ�����22 66" << endl;
			cout << "ʵ���ǣ�";
			auto it = myset.find("11");
			cout << *++it << " ";
			it = myset.find("10");
			cout << *--it << " ";
			cout << endl;

			wait_for_next();
		}

		//��4����ԣ��������+��Χ����
		if (test[4])
		{
			cout << "��4����ԣ�clear/swap/equal_range/upper_bound/lower_bound" << endl << endl;


			multiset<string> myset1;
			myset1.insert("11");
			myset1.insert("22");
			myset1.insert("33");
			multiset<string> myset2 = myset1;
			myset2.emplace("44");
			myset2.emplace("55");
			myset2.emplace("44");
			myset1.swap(myset2);
			cout << "Ӧ�����6 3" << endl;
			cout << "ʵ���ǣ�";
			cout << myset1.size() << " " << myset2.size();
			cout << endl << endl;


			myset2.clear();
			myset1.swap(myset1);
			swap(myset1, myset2);
			cout << "Ӧ�����0 6" << endl;
			cout << "ʵ���ǣ�";
			cout << myset1.size() << " " << myset2.size();
			cout << endl << endl;


			auto range = myset2.equal_range("44");
			cout << "Ӧ�����44 55" << endl;
			cout << "ʵ���ǣ�";
			cout << *range.first << " " << *range.second;
			cout << endl << endl;


			auto lower = myset2.lower_bound("44");
			auto upper = myset2.upper_bound("44");
			cout << "Ӧ�����44 55" << endl;
			cout << "ʵ���ǣ�";
			cout << *lower << " " << *upper;
			cout << endl;

			wait_for_next();
		}

		//��5����ԣ���������
		if (test[5])
		{
			cout << "��5����ԣ�key_comp/value_comp" << endl << endl;


			multiset<string> mymap;
			auto key_compare = mymap.key_comp();
			cout << "Ӧ�����0 1 1" << endl;
			cout << "ʵ���ǣ�";
			cout << key_compare("11", "11") << " " << key_compare("1", "2") << " " << key_compare("00", "11");
			cout << endl << endl;


			auto value_compare = mymap.value_comp();
			cout << "Ӧ�����0 1 1" << endl;
			cout << "ʵ���ǣ�";
			cout << value_compare("11", "11") << " " << value_compare("11", "22") << " " << value_compare("0", "1");
			cout << endl;

			wait_for_next();
		}

		//��6����ԣ���ϵ�����
		if (test[6])
		{
			cout << "��6����ԣ�6����ϵ�����" << endl << endl;


			multiset<string> myset1;
			myset1.emplace("11");
			myset1.emplace("22");
			myset1.emplace("33");
			myset1.emplace("44");
			myset1.emplace("55");
			multiset<string> myset2 = myset1;
			cout << "Ӧ�����1 0 1 1 0 0" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl << endl;


			myset2.erase("55");
			cout << "Ӧ�����0 1 1 0 0 1" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl << endl;


			myset2.emplace("00");
			cout << "Ӧ�����0 1 1 0 0 1" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl << endl;


			myset2.erase("00");
			myset2.emplace("66");
			cout << "Ӧ�����0 1 0 1 1 0" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl;

			wait_for_next();
		}

	}

	//student
	if (1)
	{
		const student S[] = {
	   {1851000,"С��",'f',(float)(93.2),"����"},
	   {1852000,"С��",'m',(float)(91.6),"ɽ��"},
	   {1853000,"����",'m',(float)(96.3),"����"},
	   {1854000,"С��",'f',(float)(93.7),"�Ĵ�"},
	   {1855000,"����",'m',(float)(97.2),"����"},
	   {1856000,"����",'f',(float)(98.5),"�㶫"},
	   {1857000,"С��",'f',(float)(89.5),"����"}
		};

		int test[] = { 1,1,1,1,1,1,1 };

		//��0����ԣ�insert+����������
		if (test[0])
		{
			cout << "��0����ԣ�insert/begin/end/cbegin/cend/rbegin/rend/crbegin/crend" << endl << endl;

			multiset<student> myset1;
			initializer_list<student> L = { S[0],S[1],S[2] };
			myset1.insert(L);
			myset1.insert(S[3]);
			myset1.insert(S[2]);
			myset1.insert(S[5]);
			myset1.insert(S[4]);
			myset1.insert(S[5]);

			cout << "Ӧ�����f m m m f m f f" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.begin(); it != myset1.end(); it++)
				cout << it->sex << " ";
			cout << endl << endl;


			cout << "Ӧ�����93.2 91.6 96.3 96.3 93.7 97.2 98.5 98.5" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.cbegin(); it != myset1.cend(); it++)
				cout << it->score << " ";
			cout << endl << endl;


			cout << "Ӧ��������� ���� ���� С�� ���� ���� С�� С��" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.rbegin(); it != myset1.rend(); it++)
				cout << it->name << " ";
			cout << endl << endl;


			cout << "Ӧ������㶫 �㶫 ���� �Ĵ� ���� ���� ɽ�� ����" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.crbegin(); it != myset1.crend(); it++)
				cout << it->addr << " ";
			cout << endl << endl;


			auto first = myset1.begin();
			auto last = myset1.end();
			multiset<student> myset2(first, last);
			myset2.insert(S[6]);
			myset2.insert(S[5]);
			cout << "Ӧ�����f f f f m f m m m f" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset2.crbegin(); it != myset2.crend(); it++)
				cout << it->sex << " ";
			cout << endl;

			wait_for_next();
		}

		//��1����ԣ��������
		if (test[1])
		{
			cout << "��1����ԣ����캯��/=����" << endl << endl;


			initializer_list<student> L = { S[0],S[2] };
			multiset<student> myset1(L);
			myset1.insert(S[1]);
			cout << "Ӧ�����f m m" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.begin(); it != myset1.end(); it++)
				cout << it->sex << " ";
			cout << endl << endl;


			multiset<student> myset2(myset1);
			cout << "Ӧ�����f m m" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.begin(); it != myset1.end(); it++)
				cout << it->sex << " ";
			cout << endl << endl;


			multiset<student> myset3(myset1.begin(), myset1.end());
			cout << "Ӧ�����f m m" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.begin(); it != myset1.end(); it++)
				cout << it->sex << " ";
			cout << endl << endl;


			multiset<student> myset4 = myset1;
			cout << "Ӧ�����f m m" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset1.begin(); it != myset1.end(); it++)
				cout << it->sex << " ";
			cout << endl;

			wait_for_next();
		}

		//��2����ԣ��������
		if (test[2])
		{
			cout << "��2����ԣ�size/max_size/empty/count" << endl << endl;


			multiset<student> myset;
			cout << "mymapΪ�գ�Ӧ�����1" << endl;
			cout << "mymapΪ�գ�ʵ���ǣ�" << myset.empty();
			cout << endl << endl;


			myset.insert(S[3]);
			myset.insert(S[2]);
			myset.insert(S[1]);
			myset.insert(S[0]);
			myset.insert(S[2]);
			myset.insert(S[4]);
			cout << "mymap��Ϊ�գ���6��Ԫ�أ�Ӧ�����0 6" << endl;
			cout << "mymap��Ϊ�գ���6��Ԫ�أ�ʵ���ǣ�" << myset.empty() << " " << myset.size();
			cout << endl << endl;


			cout << "max_size()��������Բ�ͬ(63161283)" << endl;
			cout << "ʵ��Ϊ��" << myset.max_size();
			cout << endl << endl;


			cout << "Ӧ�����1 2 1 0 0 0" << endl;
			cout << "ʵ���ǣ�" << myset.count(S[0]) << " " << myset.count(S[2]) << " " << myset.count(S[4]) << " ";
			cout << myset.count(S[6]) << " " << myset.count(S[5]) << " " << myset.count(S[6]) << " ";
			cout << endl;

			wait_for_next();
		}

		//��3����ԣ�Ԫ�ز���
		if (test[3])
		{
			cout << "��3����ԣ�insert/erase/emplace/find" << endl << endl;


			multiset<student> myset;
			myset.insert(S[0]);
			myset.insert(S[1]);
			myset.insert(S[1]);
			myset.insert(S[2]);
			myset.insert(S[3]);
			myset.insert(S[4]);
			myset.insert(S[4]);
			cout << "Ӧ�����f m m m f m m" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << it->sex << " ";
			cout << endl << endl;


			myset.erase(myset.begin());
			myset.erase(myset.begin(), ++myset.begin());
			cout << "Ӧ�����m m f m m" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << it->sex << " ";
			cout << endl << endl;


			myset.erase(S[4]);
			cout << "Ӧ�����m m f" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << it->sex << " ";
			cout << endl << endl;


			myset.emplace(S[0]);
			myset.emplace(S[1]);
			myset.emplace(S[2]);
			myset.emplace(S[5]);
			cout << "Ӧ�����f m m m m f f" << endl;
			cout << "ʵ���ǣ�";
			for (auto it = myset.begin(); it != myset.end(); it++)
				cout << it->sex << " ";
			cout << endl << endl;



			cout << "Ӧ�����m f" << endl;
			cout << "ʵ���ǣ�";
			auto it = myset.find(S[0]);
			cout << (++it)->sex << " ";
			it = myset.find(S[6]);
			cout << (--it)->sex << " ";
			cout << endl;

			wait_for_next();
		}

		//��4����ԣ��������+��Χ����
		if (test[4])
		{
			cout << "��4����ԣ�clear/swap/equal_range/upper_bound/lower_bound" << endl << endl;


			multiset<student> myset1;
			myset1.insert(S[0]);
			myset1.insert(S[1]);
			myset1.insert(S[2]);
			multiset<student> myset2 = myset1;
			myset2.emplace(S[3]);
			myset2.emplace(S[4]);
			myset2.emplace(S[3]);
			myset1.swap(myset2);
			cout << "Ӧ�����6 3" << endl;
			cout << "ʵ���ǣ�";
			cout << myset1.size() << " " << myset2.size();
			cout << endl << endl;


			myset2.clear();
			myset1.swap(myset1);
			swap(myset1, myset2);
			cout << "Ӧ�����0 6" << endl;
			cout << "ʵ���ǣ�";
			cout << myset1.size() << " " << myset2.size();
			cout << endl << endl;


			auto range = myset2.equal_range(S[3]);
			cout << "Ӧ�����С�� ����" << endl;
			cout << "ʵ���ǣ�";
			cout << range.first->name << " " << range.second->name;
			cout << endl << endl;


			auto lower = myset2.lower_bound(S[3]);
			auto upper = myset2.upper_bound(S[3]);
			cout << "Ӧ�����С�� ����" << endl;
			cout << "ʵ���ǣ�";
			cout << lower->name << " " << upper->name;
			cout << endl;

			wait_for_next();
		}

		//��5����ԣ���������
		if (test[5])
		{
			cout << "��5����ԣ�key_comp/value_comp" << endl << endl;


			multiset<student> mymap;
			auto key_compare = mymap.key_comp();
			cout << "Ӧ�����0 1 1" << endl;
			cout << "ʵ���ǣ�";
			cout << key_compare(S[1], S[1]) << " " << key_compare(S[1], S[2]) << " " << key_compare(S[0], S[1]);
			cout << endl << endl;


			auto value_compare = mymap.value_comp();
			cout << "Ӧ�����0 1 1" << endl;
			cout << "ʵ���ǣ�";
			cout << value_compare(S[1], S[1]) << " " << value_compare(S[1], S[2]) << " " << value_compare(S[0], S[1]);
			cout << endl;

			wait_for_next();
		}

		//��6����ԣ���ϵ�����
		if (test[6])
		{
			cout << "��6����ԣ�6����ϵ�����" << endl << endl;


			multiset<student> myset1;
			myset1.emplace(S[1]);
			myset1.emplace(S[2]);
			myset1.emplace(S[3]);
			myset1.emplace(S[4]);
			myset1.emplace(S[5]);
			multiset<student> myset2 = myset1;
			cout << "Ӧ�����1 0 1 1 0 0" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl << endl;


			myset2.erase(S[5]);
			cout << "Ӧ�����0 1 1 0 0 1" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl << endl;


			myset2.emplace(S[0]);
			cout << "Ӧ�����0 1 1 0 0 1" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl << endl;


			myset2.erase(S[0]);
			myset2.emplace(S[6]);
			cout << "Ӧ�����0 1 0 1 1 0" << endl;
			cout << "ʵ���ǣ�";
			cout << (myset1 == myset2) << " " << (myset1 != myset2) << " " << (myset1 >= myset2) << " ";
			cout << (myset1 <= myset2) << " " << (myset1 < myset2) << " " << (myset1 > myset2) << " ";
			cout << endl;

			wait_for_next();
		}

	}


}
