#include"tools.h"
/**
* @file			tools.cpp
* @brief       �ַ���ת��Ϊint
* @author       zzh
* @date			2020.04.13
* @version		0.0.1
*/
int str2int(string str)
{
    int num = 0;
    for (int i = 0; i < str.length(); i++) {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

/**
* @file			tools.cpp
* @brief       �ж��Ƿ�����ĸ����Сд����
* @author       zzh
* @date			2020.04.13
* @version		0.0.1
*/
bool isalpha(char ch)
{
    return (ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a');
}

/**
* @file			tools.cpp
* @brief        �ж��Ƿ�������
* @author       zzh
* @date			2020.04.13
* @version		0.0.1
*/
bool isnumeric(char ch)
{
    return ch <= '9' && ch >= '0';
}

/**
* @file			tools.cpp
* @brief        ����int��int��ת��Ϊint
* @author       zzh
* @date			2020.04.13
* @version		0.0.1
*/
int position2int(int x, int y)
{
    return x * 5 + y;
};
void run(int& depth) {

}