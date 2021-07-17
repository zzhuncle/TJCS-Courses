#ifndef LEXANALYZER_H
#define LEXANALYZER_H

#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

/* ���Ԫ��ö�� */


/*
int void if while else return + - * / = == > < != >= <= ; , ( ) { } ID NUM
*/

//Ϊ����չ�ԣ����ʷ������ı��д�ĺܶ࣬��ʵ�ʷ�����ʱ��û���õ���ô��
enum VT {
    //0 ~ 9
    VTNull,
    VTInteger,
    VTString,
    VTBoolean,
    VTFloating,
    VTCharacter,
    VTComment,
    VTMacro,
    VTWhiteSpace,
    VTEndLine,
    //��� ���� 10 ~ 15
    VTLeftBrace,
    VTRightBrace,
    VTLeftSquareBracket,
    VTRightSquareBracket,
    VTLeftBracket,
    VTRightBracket,
    //����� 16 ~ 50
    VTPlus,
    VTMinus,
    VTMultiply,
    VTDivide,
    VTModulus,
    VTIncrement,
    VTDecrement,
    VTEqual,
    VTNotEqual,
    VTGreater,
    VTLess,
    VTGE,
    VTLE,
    VTLogicalAnd,
    VTLogicalOr,
    VTLogicalNot,
    VTBinaryAnd,
    VTBinaryOr,
    VTBinaryNot,
    VTXor,
    VTLeftShift,
    VTRightShift,
    VTAssignment,
    VTAddAssignment,
    VTSubtractAssignment,
    VTMultiplyAssignment,
    VTDivideAssignment,
    VTModulusAssignment,
    VTLeftShiftAssignment,
    VTRightShiftAssignment,
    VTBinaryAndAssignment,
    VTBinaryOrAssignment,
    VTBinaryXorAssignment,
    VTComma,
    VTSemicolon,
    //�ؼ��� 51 ~ 82
    VTAuto,
    VTBreak,
    VTCase,
    VTChar,
    VTConst,
    VTContinue,
    VTDefault,
    VTDo,
    VTDouble,
    VTElse,
    VTEnum,
    VTExtern,
    VTFloat,
    VTFor,
    VTGoto,
    VTIf,
    VTInt,
    VTLong,
    VTRegister,
    VTReturn,
    VTShort,
    VTSigned,
    VTSizeof,
    VTStatic,
    VTStruct,
    VTSwitch,
    VTTypedef,
    VTUnion,
    VTUnsigned,
    VTVoid,
    VTVolatile,
    VTWhile,
    //words ��ʶ�� 82
    VTIdentifier,
    VTWord
};
//������ֵ�ֱ��¼�ʻ��Ŀ�ʼ�ͽ�β������Ѱ��ĳһ���ս����λ��
//�˺������map��ʵ�������Ľṹ���Ͳ���Ҫ���ص�����
const int VT_MIN = (int)VTNull;
const int VT_MAX = (int)VTWord;

//�����������ֱ��ǽ�һ������ת��Ϊ�ַ���string�ĺ���������ת����ʱ������
string VT_to_string(VT component);
string VT_to_string(int i);
int VTStr_to_int(const char* p);


//�����﷨������ʱ�������жϷ����ĺ����������ʵ����һ��覴�
//ֱ�ӽ�λ��ȷ������������չ
bool is_keyword(VT component);
bool is_operator(VT component);
bool is_bracket(VT component);
bool is_value(VT component);

/* �ָ������ */
class LexSegment {
public:
    int left_index = -1;
    int right_index = -1;
    //������λ����������ļ���ͷ�Ĳ��֣�����left_index��right_index���Զ�λ�����ԭ�ַ���
    VT component_type = VT::VTNull;

public:
    LexSegment();
    LexSegment(int li, int ri, VT ctype) :
        left_index(li), right_index(ri), component_type(ctype) {};
};

/* �ֵ�������ṹ�� */
struct _Res {
    VT val;
    int begin;
    int end;
};

// �ֵ�����
//������ҹؼ��ֺ������
class Trie {
private:
    bool isLeaf;
    Trie* next[128];
    VT type;
public:
    Trie() {
        isLeaf = false;
        memset(next, NULL, sizeof(next));
    }

    void insert(const string& word, const VT& t) {
        Trie* node = this;
        for (char c : word) {
            if (node->next[c - '\0'] == NULL)
                node->next[c - '\0'] = new Trie();
            node = node->next[c - '\0'];
        }
        node->isLeaf = true;
        node->type = t;
    }

    vector<_Res> match(const string& word) {
        Trie* node = this,* parent = this;
        int len = word.length();
        vector<_Res> res;
        for (int start = 0, i = 0; i < len;) {
            node = this;
            for (i = start; i < len;i++) {
                const char& c = word[i];
                parent = node;
                node = node->next[c - '\0'];
                if (node == NULL) {
                    if (parent->isLeaf) {//��ֹ����ƥ��
                        if ((parent->type == VTPlus || parent->type == VTMinus)
                            && (i >= 2 && (word[i - 2] == 'e' || word[i - 2] == 'E'))) {//��ֹƥ�䵽�������е�-��+
                            start = start + 1;
                            break;
                        }
                        res.emplace_back(_Res{ parent->type, start, i});
                        start = i;
                    }
                    else
                        start = start + 1;
                    break;
                }
            }
        }
        return res;
    }
};


/* �ʷ������� */
class LexAnalyzer {
private:
    char* original_code = NULL;         //ԭʼ�ַ���
    int code_length = -1;               //�ַ�������
    vector<LexSegment> inner_result;    //�ʷ��������
    vector<VT> component_type;//
    Trie trie;                          //�������
private:
    void init();
    void preAnalyze();
    void analyzeSpliters();
    void analyzeKeywordsAndOperators();
    void analyzeWords();
    void setComponent(int start_index, int end_index, VT component);
public:
    LexAnalyzer();
    void Analyze(const char* code);
    void Analyze(const string& code);
    void GetResult(vector<LexSegment>& result);
};

#endif
