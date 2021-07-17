#include"tools.h"
#include"common.h"
//ncn����ת����
unordered_map<char, int> n2b_mapper = {
    {'F', 1}, {'P', 5}, {'V' , 9}, {'D' , 2}, {'L' , 6} ,{'S' , 10},
    {'Z' , 3},{'Y' , 7}, {'J' , 11}, {'G' , 4}, {'T' , 8}, {'A' , 12},
    {'f' , -1}, {'p' , -5}, {'v' , -9}, {'d' , -2}, {'l' , -6}, {'s' , -10},
    {'z' , -3}, {'y' , -7}, {'j' , -11}, {'g' , -4}, {'t' , -8},{'a' , -12}
};

unordered_map<int, char> b2n_mapper = {
    {1, 'F'}, {5 , 'P'}, {9 , 'V'}, {2 , 'D'}, {6 , 'L'}, {10 , 'S'},
    {3 , 'Z'}, {7 , 'Y'}, {11 , 'J'}, {4 , 'G'}, {8 , 'T'}, {12 , 'A'},
    {-1 , 'f'}, {-5 , 'p'}, {-9 , 'v'},{ -2 , 'd'}, {-6 , 'l'}, {-10 , 's'},
    {-3 , 'z'}, {-7 , 'y'}, {-11 , 'j'}, {-4 , 'g'}, {-8 , 't'}, {-12 , 'a'}
};
/**
* @file			ncn.cpp
* @brief        ncn������Ϊ�������顢˫��û�г��ӵ����岽������ǰ�Ĳ�����
* @param[in]    ncn->ncn��
* @param[out]   board->�������� cnt->˫��û�г��ӵ����岽��  total_cnt->��ǰ�Ĳ�����
* @author       zzh
* @date			2020.04.13
* @version		0.0.1
*/
void parse_ncn(array<array<int, 5>, 13>& board, string ncn, int& cnt, int& total_cnt)
{
    string temp = "";
    vector<string> ncn_element;
    ncn += " ";
    int n = ncn.length();
    //�ָ�ncn�ַ���
    for (int i = 0; i < n; i++) {
        if (ncn[i] == ' ' && temp != "") {
            ncn_element.push_back(temp);
            temp.clear();
        }
        if (ncn[i] == ' ')
            continue;
        temp += ncn[i];
    }
    //ncn����������ʽ
    if (ncn_element.size() == 3) {
        temp = ncn_element[0];
        cnt = str2int(ncn_element[1]);
        total_cnt = str2int(ncn_element[2]);
    }
    else {
        temp = ncn_element[0];
        cnt = -1;//����Ƿ�ֵ
        total_cnt = -1;
    }
    //��ncn��ת��Ϊchessboard�Ķ�ά����
    temp += "/";
    for (int i = 0, index = 0; i < 13; i++) {//i��
        for (int j = 0; index < temp.length();) {//j��
            if (isalpha(temp[index])) {//index�ַ������
                board[i][j] = n2b_mapper[temp[index]];
                j += 1;
            }
            else if (isnumeric(temp[index])) {
                for (int k = 0; k < temp[index] - '0'; k++)
                    board[i][j + k] = 0;
                j += temp[index] - '0';
            }
            else if (temp[index] == '/') {
                index++;
                break;
            }
            index++;
        }
    }
}

/**
* @file			ncn.cpp
* @brief        �����������Ϊncn��
* @param[in]    board->��������
* @param[out]   ncn->ncn��
* @author       zzh
* @date			2020.04.13
* @version		0.0.1
*/
string board_to_ncn(const array<array<int, 5>, 13>& board)
{
    string ncn = "";
    for (int i = 0; i < 13; i++) {
        if (i)
            ncn += '/';
        int zero_cnt = 0;
        for (int j = 0; j < 5; j++) {
            int element = board[i][j];
            if (element) {
                if (zero_cnt) {
                    ncn += char('0' + zero_cnt);
                    zero_cnt = 0;
                }
                ncn += b2n_mapper[element];
            }
            else
                zero_cnt += 1;
        }
        if (zero_cnt)
            ncn += char('0' + zero_cnt);
    }
    return ncn;
}

/**
* @file			ncn.cpp
* @brief        �ƶ��������Ϊ�ƶ�����ĩ����
* @param[in]    move->�ƶ������ַ���
* @param[out]   arr->2x2�����飬{{��ʼx���꣬��ʼy����}��{��ֹx���꣬��ֹy����}}
* @author       zzh
* @date			2020.04.13
* @version		0.0.1
*/
array<array<int, 2>, 2> parse_ncn_move(string move)
{
    array<array<int, 2>, 2> arr;
    arr[0][0] = 'm' - move[0];
    arr[0][1] = move[1] - '0';
    arr[1][0] = 'm' - move[2];
    arr[1][1] = move[3] - '0';
    return arr;
}

/**
* @file			ncn.cpp
* @brief        �ƶ�����ĩ�������Ϊ�ƶ�����
* @param[in]    arr->2x2�����飬{{��ʼx���꣬��ʼy����}��{��ֹx���꣬��ֹy����}}
* @param[out]   ncn->�ƶ������ַ���
* @author       zzh
* @date			2020.04.13
* @version		0.0.1
*/
string move_to_ncn(const array<array<int, 2>, 2>& arr)
{
    string ncn = "";
    return ncn + char('m' - arr[0][0]) + char(arr[0][1] + '0') + char('m' - arr[1][0]) + char(arr[1][1] + '0');
}

