#include"common.h"
/**
* @file			LBChess.cpp
* @brief        �ж��Ƿ����
* @param[in]    ��������
* @param[out]   ����;ַ���0�����򷵻�Ӯ��R����-1��B����1�����û�н�������2
* @author       zzh
* @date			2020.04.13
* @version		0.0.1
*/
const unordered_map<int, int>TYPE = { {DI,39},{GONG,60} ,{PAI,20},{LIAN,40},{ZHA,130},{YING,70},{TUAN,90},{LV,120},{SHI,170},{JUN,260},{SI,350} };
int LBChess::END()
{
	//�жϾ����Ƿ񱻳�
	bool FlagR = false, FlagB = false;
	//�ж��Ƿ���ڿ����ƶ�������
	bool live_R = false, live_B = false;
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 5; j++) {
			if (board[i][j] == FLAG)//B��������R�Ǹ���
				FlagB = true;
			else if (board[i][j] == -FLAG)
				FlagR = true;
			else if (board[i][j] >= 3 && board[i][j] <= 12)
				live_B = true;
			else if (board[i][j] <= -3 && board[i][j] >= -12)
				live_R = true;
		}
	if (!FlagB)  return R;
	if (!FlagR)  return B;
	if (!live_B && !live_R)//�;�
		return 0;
	if (live_B && live_R)//δ����
		return 2;
	return live_B ? B : R;
}

/**
* @file			LBChess.cpp
* @brief        �������ӵȼ��жϹ������
* @param[in]    src : ������ dst : ����Ŀ��
* @param[out]   ͬ���ھ�����0�������ɹ�����1������ʧ�ܷ��� -1���Ƿ���������2
* @author       zzh
* @date			2020.04.13
* @version		0.0.1
*/
int attack(int src, int dst)
{
	if (abs(src) == DI || abs(src) == FLAG || src * dst > 0) // �����߲����ǵ��׻�����հף�˫��������ͬһ��ɫ�����򱨴�
		return 2;
	src = abs(src); dst = abs(dst);
	if (dst == ZHA or src == ZHA)  // ը����Ȼͬ���ھ�
		return 0;
	if (dst == DI)  // �����ŵ��ף�����ͬ���ھ�
		return src == GONG ? 1 : 0;
	if (src == dst)  // ��ͬ��ͬ���ھ�
		return 0;
	if (dst == FLAG)  // ��������
		return 1;
	return src > dst ? 1 : -1;
}

/**
* @file			LBChess.cpp
* @brief        ���ݹ�������ı����
* @param[in]    board : ԭʼ��� arr : ������ʼĩβλ��
* @param[out]   res : ���º�����
* @author       zzh
* @date			2020.04.26
* @version		0.0.1
* @date         2020.05.10
* @version      0.0.2
*/
int  LBChess::change_board(const array<array<int, 2>, 2>& arr, int &start_value, int &end_value)
{
	int start_x = arr[0][0], start_y = arr[0][1];
	int end_x = arr[1][0], end_y = arr[1][1];

	start_value = board[start_x][start_y];
	end_value = board[end_x][end_y];

	//array<array<int, 5>, 13> res = board;
	if (board[end_x][end_y] == BLANK) {//Ҫȥ�ĵط��ǿհף�ֱ�Ӹ��ǿհײ�����
		board[end_x][end_y] = board[start_x][start_y];
		board[start_x][start_y] = BLANK;
		return 1;
	}
	int situation = attack(board[start_x][start_y], board[end_x][end_y]);//���й����ж�
	if (situation == 0)//ͬ���ھ�
		board[start_x][start_y] = board[end_x][end_y] = BLANK;
	else if (situation == 1) {//�����ɹ�
		board[end_x][end_y] = board[start_x][start_y];
		board[start_x][start_y] = BLANK;
	}
	else//����ʧ��
		board[start_x][start_y] = BLANK;
	return situation;
}

//���ָ̻�
void LBChess::recover_board(int start_value,int end_value, const array<array<int, 2>, 2>& arr) {
	
	board[arr[0][0]][arr[0][1]] = start_value;
	board[arr[1][0]][arr[1][1]] = end_value;
}

bool LBChess::tie(int x, int y) {
	return(x >= 0 && y >= 0 && x <= 12 && y <= 4 && _tie[x][y] == 1);
}
void  LBChess::flag_find()
{

	if (-FLAG == board[0][1])//�ж��Ƿ��Ǿ���
		Nflag_location = make_pair(0, 1);
	else
		Nflag_location = make_pair(0, 3);

	if (FLAG == board[12][1])//�ж��Ƿ��Ǿ���
		Sflag_location = make_pair(12, 1);
	else
		Sflag_location = make_pair(12, 3);

}

/**
* @file       LBChess.cpp
* @brief      �������
* @author     zjx
* @date        2020  5.4
* @param[in]   player   ��ǰ������
* @param[out]  value    ����ֵ
* @par history
		zjx��2020.5.4����\n
*/
int LBChess::evalution(int  player) {
	int value = 0;
	int size_board = board.size();
	int size_board_0 = board[0].size();

	//�޸� ը����������ɵ�ǰ���������0.4 ��Ϊ��ʼֵ130�����˾��350��0.4����
	int max_ChessPower_B = -1;
	int max_ChessPower_R = -1;
	int ZHA_ChessPower_B = 0;
	int ZHA_ChessPower_R = 0;
	for (int i = 0; i < size_board; i++)
		for (int j = 0; j < size_board_0; j++)
		{
			if (abs(board[i][j]) != BLANK && abs(board[i][j]) != FLAG)
			{
				if (board[i][j] > 0 && board[i][j] != ZHA && TYPE.find(board[i][j])->second > max_ChessPower_B)
					max_ChessPower_B = TYPE.find(board[i][j])->second;
				if (board[i][j] < 0 && abs(board[i][j]) != ZHA && TYPE.find(abs(board[i][j]))->second > max_ChessPower_R)
					max_ChessPower_R = TYPE.find(abs(board[i][j]))->second;
			}
		}
	ZHA_ChessPower_B = int(max_ChessPower_B * 0.35);
	ZHA_ChessPower_R = int(max_ChessPower_R * 0.35);
	//TYPE.find(ZHA)->second = int(max_ChessPower * 0.4);

	for (int i = 0; i < size_board; i++)
		for (int j = 0; j < size_board_0; j++)
		{
			if (abs(board[i][j]) == BLANK && abs(board[i][j]) == FLAG)
				continue;
			//�����Ӻͷ���
			if (board[i][j] > 0 && !(i == Sflag_location.first && j == Sflag_location.second))
			{
				//��ը������ר�Ŵ���
				if (board[i][j] != ZHA)
					value += TYPE.find(board[i][j])->second;
				else
					value += ZHA_ChessPower_R;//��Ҫ���ӵ��ǶԷ�������ֵ������

				/*if (board[i][j] == DI)
					value += 39;
				else if (board[i][j] == GONG)
					value += 60;
				else if (board[i][j] == PAI)
					value += 20;
				else if (board[i][j] == LIAN)
					value += 40;
				else if (board[i][j] == ZHA)
					value += 130;
				else if (board[i][j] == YING)
					value += 70;
				else if (board[i][j] == TUAN)
					value += 90;
				else if (board[i][j] == LV)
					value += 120;
				else if (board[i][j] == SHI)
					value += 170;
				else  if (board[i][j] == JUN)
					value += 260;
				else
					value += 350;*/
			}
			if (board[i][j] < 0 && !(i == Nflag_location.first && j == Nflag_location.second)) {
				//��ը������ר�Ŵ���
				if (abs(board[i][j]) != ZHA)
					value -= TYPE.find(abs(board[i][j]))->second;
				else
					value -= ZHA_ChessPower_B;//��Ҫ���ӵ��ǶԷ�������ֵ������
				/*if (board[i][j] == -DI)
					value -= 39;
				else if (board[i][j] == -GONG)
					value -= 60;
				else if (board[i][j] == -PAI)
					value -= 20;
				else if (board[i][j] == -LIAN)
					value -= 40;
				else if (board[i][j] == -ZHA)
					value -= 130;
				else if (board[i][j] == -YING)
					value -= 70;
				else if (board[i][j] == -TUAN)
					value -= 90;
				else if (board[i][j] == -LV)
					value -= 120;
				else if (board[i][j] == -SHI)
					value -= 170;
				else  if (board[i][j] == -JUN)
					value -= 260;
				else
					value -= 350;*/
			}

			//��ռ�Է����߼ӷ֣������������ǿ���أ�
			if (i == 11 && board[i][j] < 0)
				value -= 20;
			if (i == 1 && board[i][j] > 0)
				value += 20;
			//ռ����λ��


			//������Ӫ�ӷ�
			if (XINGYING.count(i * 5 + j) != 0 && board[i][j] > 0)
				value += 5;
			if (XINGYING.count(i * 5 + j) != 0 && board[i][j] < 0)
				value -= 5;

		}

	//�츽����λ����killer������Ҫ�ֲ�������Ȳ���
	if (abs(board[Nflag_location.first][Nflag_location.second]) == FLAG)
		value -= FLAG_VALUE;
	if (abs(board[Sflag_location.first][Sflag_location.second]) == FLAG)
		value += FLAG_VALUE;
	if (board[Sflag_location.first][Sflag_location.second + 1] < 0 || board[Sflag_location.first][Sflag_location.second - 1] < 0)
		value -= FLAG_VALUE / 10;
	if ((board[Sflag_location.first - 1][Sflag_location.second]) < 0)
		value -= FLAG_VALUE / 10;
	/*if (board[Sflag_location.first - 1][Sflag_location.second-1]< 0|| board[Sflag_location.first - 1][Sflag_location.second +1]<0)
		value -= FLAG_VALUE / 20;
	if (board[Nflag_location.first + 1][Nflag_location.second - 1] > 0 || board[Nflag_location.first + 1][Nflag_location.second + 1] > 0)
		value += FLAG_VALUE / 20;*/
	if ((board[Nflag_location.first + 1][Nflag_location.second]) > 0)
		value += FLAG_VALUE / 10;
	if (board[Nflag_location.first][Nflag_location.second + 1] > 0 || board[Nflag_location.first][Nflag_location.second - 1] > 0)
		value += FLAG_VALUE / 10;
	//Ҫ��������
	if ((board[Sflag_location.first - 1][Sflag_location.second]) == DI && board[Sflag_location.first][Sflag_location.second + 1] == DI && board[Sflag_location.first][Sflag_location.second - 1] == DI)
		value += 300;
	if ((board[Nflag_location.first + 1][Nflag_location.second]) == -DI && board[Nflag_location.first][Nflag_location.second + 1] == -DI && board[Nflag_location.first][Nflag_location.second - 1] == -DI)
		value -= 300;
	//ռ�Է����ϵ���Ӫ��λ����Ҫ
	if (board[Sflag_location.first - 2][Sflag_location.second] < 0)
		value -= 45;
	if (board[Sflag_location.first - 2][Sflag_location.second] > 0)
		value += 45;
	if (board[Nflag_location.first + 2][Nflag_location.second] > 0)
		value += 45;
	if (board[Nflag_location.first + 2][Nflag_location.second] < 0)
		value -= 45;
	//��ֵ����������Ե�ǰһ�����ԣ����ռ���򷵻����������򷵻ظ���
	if (player < 0)
		value = -value;
	return value;
}


/**
* @file       LBChess.cpp
* @brief      �õ�����λ�����ӿ����ߵ�����λ��
* @author     zzh
* @date       2020.4.14
* @param[in]
* @param[out] result   ���пɵ���λ��
* @par history
		zzh��2020.4.25����\n
*/

void LBChess::get_all(int chessman, vector<int>& pre_positions, vector<vector<int>>& res)
{
	int index = 0;
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 5; j++)
			if (chessman * board[i][j] > 0) {//ֻ���ƶ���������
				pre_positions.push_back(i * 5 + j);
				vector<int>move = {};
				res.push_back(move);
				get(i * 5 + j, res[index]);
				if (!res[index].size())
				{
					res.pop_back();
					pre_positions.pop_back();
					//continue;
				}
				else
					index++;
			}
	return;
}

/**
* @file       LBChess.cpp
* @brief      �õ�ĳһλ�����ӿ����ߵ�����λ��
* @author     zjx
* @date        2020.4.14
* @param[in]   pos    λ������
* @param[out]  result   ���пɵ���λ��
* @par history
		zjx��2020.4.14����\n
*/
//������ǰ��
int r_tomove[8][2] = { {1,0},{1,1},{1,-1},{0,1},{0,-1},{-1,1}, {-1,-1},{-1,0} };
int b_tomove[8][2] = { {-1,0},{-1,1},{-1,-1},{0,1},{0,-1},{1,1}, {1,-1},{1,0} };
int r_tomove_tie[4][2] = { {1,0},{0,1},{0,-1},{-1,0} };
int b_tomove_tie[4][2] = { {-1,0},{0,1},{0,-1}, {1,0} };
void LBChess::get(int pos, vector<int>& result) {
	int pos_first = pos / 5, pos_second = pos % 5;
	if (abs(board[pos_first][pos_second]) == BLANK || abs(board[pos_first][pos_second]) == FLAG || abs(board[pos_first][pos_second]) == DI ||
		SHANJIE.count(pos_first * 5 + pos_second)) //[��Ӫ�޷��ƶ����������]
		return;
	//��·�ߣ�������Χ�˸�λ��
	int which_ = board[pos_first][pos_second];//ȡ��Ҫ�жϵ��ӵ���ֵ
	int(*p)[2];
	if (which_*R > 0)//˵���Ǻ췽
		p = r_tomove;
	else
		p = b_tomove;
	for (int k = 0; k < 8; k++) {

		int i = p[k][0];
		int j = p[k][1];
		int new_row = pos_first + i;
		int new_col = pos_second + j;
		if (new_row < 0 || new_row>12 || new_col < 0 || new_col>4)    //�����ƶ�������
			continue;
		if (SHANJIE.count(new_row * 5 + new_col))   //�����ƶ���ɽ��
			continue;
		if (i != 0 && j != 0 && !XINGYING.count(pos_first * 5 + pos_second) &&
			!XINGYING.count(new_row * 5 + new_col))//б�������ƶ�������һ������Ӫ
			continue;
		if (XINGYING.count(new_row * 5 + new_col) && board[new_row][new_col] != BLANK)//����ƶ�����Ӫ����Ӫ������������
			continue;
		if (board[new_row][new_col] != 0 && board[pos_first][pos_second] != 0 && board[new_row][new_col] * board[pos_first][pos_second] > 0)
			continue;
		result.push_back(new_row * 5 + new_col);
	}

	//��·�ߣ�����ֱ��·��������ǹ�����ʹ�ù�����Ѱ·�㷨
	if (!tie(pos_first, pos_second))
		return;
	if (abs(board[pos_first][pos_second]) == GONG)
		_get_gong(pos, result);
	else
	{
		int(*direct)[2];
		if (which_*R > 0)//˵���Ǻ췽
			direct = r_tomove_tie;
		else
			direct = b_tomove_tie;
		for (int i = 0; i < 4; i++) {
			int  new_pos_first = pos_first + direct[i][0], new_pos_second = pos_second + direct[i][1];
			if (tie(new_pos_first, new_pos_second) && board[new_pos_first][new_pos_second] == BLANK)
				while (true) {
					new_pos_first = new_pos_first + direct[i][0];
					new_pos_second = new_pos_second + direct[i][1];
					if (!tie(new_pos_first, new_pos_second))  //����·����
						break;
					if (board[new_pos_first][new_pos_second] * board[pos_first][pos_second] > 0)  //ͬɫ�ڵ�
						break;
					result.push_back(new_pos_first * 5 + new_pos_second);
					if (board[new_pos_first][new_pos_second] * board[pos_first][pos_second] < 0)
						break;
				}
		}
	}
	return;

}

/**
* @file			LBChess.cpp
* @brief        ������·���ϣ��������Ե��������λ��
* @param[in]    ����λ��pair<int, int>, ���Ե���λ�õ�vector�����ô���
* @param[out]   ��(���Ե���λ�õķ��������õ�vector����
* @author       ssc
* @date			2020.04.14
* @version		0.0.3
* @history      zzh��2020.5.1�������
*/
void LBChess::_get_gong(int pos, vector<int>& res)
{
	/*����˼·��ʹ��BFS����Ѱ·�������һ��λ���Ǽ��������Ѿ�̽�������ǹ�·�ߣ���ֹͣ̽��
	 �������·�ߣ��������У��ȴ�����
	 �Ӷ����г����У�����������������
	*/
	//cout <<"testget_gong   "<< pos.first << "  " << pos.second << endl;
	int group;//�������ķ���Ӫ
	int pos_first = pos / 5, pos_second = pos % 5;
	//if (RAILWAY.count(position2int(pos.first, pos.second)) == 0 || abs(board[pos.first][pos.second]) != GONG) //����·�߻���û�й����򷵻�
		//return;
	if (board[pos_first][pos_second] > 0)
		group = 1;
	else
		group = -1;//��֤��������*group>0,�Է���*group<0
	int temp[13][5] = {
		{0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1},
		{1, 0, 1, 0, 1},
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0} };//������·�ߵ�ͼ��Ϊ�˼ӿ������ٶ�
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 5; j++)
		{
			if (temp[i][j] == 0)
				continue;
			if (board[i][j] * group > 0)
				temp[i][j] = -1;//�Լ�����-1
			if (board[i][j] * group < 0)
				temp[i][j] = 2;//������2
		}//���õ�ͼ����·��λ����0����·�߿հ׵ط�Ϊ0���Լ�λ��Ϊ1������λ��Ϊ2

	vector<int>result;
	/*cout << "testget_gong   " << endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 5; j++)
			cout << temp[i][j]<<"  ";
		cout << endl;
	}*/
	queue<int> Q;
	Q.push(pos);
	int current_first, current_second, a;//��ʱ��������¼���ڵ�λ��
	while (Q.size() > 0)
	{
		current_first = Q.front() / 5;
		current_second = Q.front() % 5;
		Q.pop();//�����У�Ȼ���¼
		//cout << "testget_gong   " << current.first << "  " << current.second << endl;
		if (temp[current_first][current_second] != -1)
			result.push_back(current_first * 5 + current_second);//����result�У���������ߵ�
		temp[current_first][current_second] = -1;//�����ѷ��ʹ�
		if (current_first + 1 < 13) {
			if (temp[current_first + 1][current_second] == 1)
				Q.push((current_first + 1) * 5 + current_second);//�������·��������У������´η���
			else if (temp[current_first + 1][current_second] == 2)
				result.push_back((current_first + 1) * 5 + current_second);//����ǵ��ˣ��Ϳ����ߵ����λ�ã����ܼ���
			//����ǹ�·�������������Ѿ�̽���������
		}
		if (current_second + 1 < 5) {
			if (temp[current_first][current_second + 1] == 1)
				Q.push(current_first * 5 + current_second + 1);
			else if (temp[current_first][current_second + 1] == 2)
				result.push_back(current_first * 5 + current_second + 1);
		}
		if (current_first - 1 >= 0) {
			if (temp[current_first - 1][current_second] == 1)
				Q.push((current_first - 1) * 5 + current_second);
			else if (temp[current_first - 1][current_second] == 2)
				result.push_back((current_first - 1) * 5 + current_second);
		}
		if (current_second - 1 >= 0) {
			if (temp[current_first][current_second - 1] == 1)
				Q.push(current_first * 5 + current_second - 1);
			else if (temp[current_first][current_second - 1] == 2)
				result.push_back(current_first * 5 + current_second - 1);
		}
	}
	//result.erase(result.begin());//��һ��Ԫ���Ǵ����pos,�Ƴ�
	vector<int> res_tmp = res;
	res.clear();//res��������µ�vector�������
	for (int i = 0; i < res_tmp.size(); i++)
		if (_tie[res_tmp[i] / 5][res_tmp[i] % 5] == 0)
			res.push_back(res_tmp[i]);
	res.insert(res.end(), result.begin(), result.end());//������·�߿ɵ���λ�ý��룬
	//cout << "testget_gong   " << result.size() << endl;
}

/**
* @file			LBChess.cpp
* @brief        �鿴���̵�ǰ״̬
* @param[in]    /
* @param[out]   ��ӡ����״̬��û���ӵ�λ��Ϊ0�����ӵ�λ����ʾ�ڲ������ֵ����Ӫ��*���
* @author       ssc
* @date			2020.04.18
* @version		0.0.1
*/
void LBChess::seetheboard()
{
	int i, j;
	for (i = 0; i < 13; i++) {
		for (j = 0; j < 5; j++)
		{
			if (XINGYING.count(position2int(i, j)) > 0)
				cout << setw(4) << "*" << board[i][j] << "*";
			else
				cout << setw(5) << board[i][j];
		}
		cout << endl;
	}
}