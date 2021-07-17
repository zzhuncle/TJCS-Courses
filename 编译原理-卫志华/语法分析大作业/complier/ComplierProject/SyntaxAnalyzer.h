#pragma once
#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "LexAnalyzer.h"
#include <unordered_map>
#include <vector>

/* ���Ԫ��ö�� */
enum VN {
	emptypro = -1000,
	A,
	M,
	N,
	P,
	add_expression,
	argument_list,
	assign_sentence,
	declare,
	declare_list,
	expression,
	factor,
	function_declare,
	if_sentence,
	inner_declare,
	inner_var_declare,
	item,
	param,
	parameter,
	parameter_list,
	return_sentence,
	sentence,
	sentence_block,
	sentence_list,
	var_declare,
	while_sentence
};

const int VN_MIN = (int)emptypro;
const int VN_MAX = (int)while_sentence;



string VN_to_string(int i);  //���±��i�ľ������Ƹ�ȡ����
int VNStr_to_int(const char* p);	//���罫return����Ӧ�ı�Ÿ��ҳ���

class SyntaxAnalyzer {
private:
	vector<pair<int,string>> VTs;	//��¼�ս��������������Ԫ��Ϊpair<int,string>,
									//��1��Ԫ��Ϊ���ս���ı�ţ���2��Ԫ��Ϊ���ս����ʵ���ַ������磬pair<52,"break">
	vector<pair<int, string>> VNs;	//��¼�м��Ԫ������������Ԫ��Ϊpair<int,string>,
									//first:�ñ�Ԫ�ı�ţ�second:�ñ�Ԫ��ʵ���ַ������磬pair<-200,"VN_Program">
	vector<vector<int>> PATs;				//��¼���ɹ��������,����Ԫ��Ϊint,
									//first:�ñ�Ԫ�ı�ţ�second:�ñ�Ԫ�Ƴ��ı��ʽ�����磬[ -200,-100,45,12],���� -200 -> -100,45,12
	void InitVTs();
	void InitVNs();
	void InitPATs();
	vector<int> InitPATs_SingleLine(const char * p);	//����ĳһ���ڵ�������Ϣ������Ҫ���Ӷ������ʽ



public:
	SyntaxAnalyzer();
	~SyntaxAnalyzer();
	void VectorClear();
	void PrintVectorVTs();
	void PrintVectorVNs();
	void PrintVectorPATS();
	void LR1_Analyze_file(ofstream& out);

};

#endif

