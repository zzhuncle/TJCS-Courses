#include "LexAnalyzer.h"

//�����̬������Ϊ�˷���Ѱ�ҳ�ԭ��ŵ�����
const char* VT_names[] = {
    "Null",
    "Integer",
    "String",
    "Boolean",
    "Floating",
    "Character",
    "Comment",
    "Macro",
    "WhiteSpace",
    "EndLine",
    //�����
    "{",
    "}",
    "[",
    "]",
    "(",
    ")",
    "+",
    "-",
    "*",
    "/",
    "%",
    "++",
    "--",
    "==",
    "!=",
    ">",
    "<",
    ">=",
    "<=",
    "&&",
    "||",
    "!",
    "&",
    "|",
    "~",
    "^",
    "<<",
    ">>",
    "=",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "<<=",
    ">>=",
    "&=",
    "|=",
    "^=",
    ",",
    ";",
    //�ؼ���
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while",
    "Identifier",
    "Word"
};

string VT_to_string(VT component) {
    return VT_names[(int)component - (int)VTNull];
}
string VT_to_string(int i) {
    if (i < 0 || (i > VT_MAX - VT_MIN))
        return "";
    else
        return VT_names[i];
}
int VTStr_to_int(const char* p) {
    for (int i = 0;i <= VT_MAX - VT_MIN;i++) {
        if (_strcmpi(p, VT_names[i]) == 0) {
            return i + VT_MIN;
        }
    }
    cerr << "�޷���" << p << "ת��Ϊ�ȴ��ս��" << endl;
    return -1;
    //����Ĭ�ϱ�Ԫ�ķ�Χ��>=0�����Է���-1�Ļ�ʵ������û�ҳ�����
}
string to_string(VT component) { return VT_names[(int)component]; }
bool is_keyword(VT component) { return component >= 51 && component < 83; }
bool is_operator(VT component) { return component >= 16 && component < 51; }
bool is_bracket(VT component) { return component >= 10 && component < 16; }
bool is_value(VT component) { return component >= 1 && component < 6; }

/* ���캯������ʼ���ֵ��� */
LexAnalyzer::LexAnalyzer() {
    for (int i = 10; i < 83; ++i) {
        VT component = (VT)i;
        string sign = to_string(component);
        trie.insert(sign, component);
    }
}

/* ���캯������ʼ���ֵ��� */
void LexAnalyzer::Analyze(const string& code) {
    Analyze(code.c_str());
}

/* �ʷ������������ */
void LexAnalyzer::Analyze(const char* code) {
    init();
    original_code = new char[code_length = strlen(code) + 1];
    memcpy(original_code, code, code_length);
    component_type.clear();
    component_type.resize(strlen(code) + 1, VT::VTNull);
    preAnalyze();
    analyzeSpliters();
    analyzeKeywordsAndOperators();
    analyzeWords();
}

/* ������� */
void LexAnalyzer::GetResult(vector<LexSegment>& result) {
    result = inner_result;
}

/* ��ʼ��������ڴ� */
void LexAnalyzer::init() {
    if (original_code) {
        delete original_code;
        original_code = NULL;
    }
    inner_result.clear();
}

/* ������ָ��ַ����ַ���������ע�͡�����ע�� */
void LexAnalyzer::preAnalyze() {
    bool is_single_line_comment = false;//����ע��
    bool is_multiline_comment = false;  //����ע��
    bool is_string = false;             //�ַ���
    bool is_char = false;               //�ַ�
    bool is_macro = false;              //��ָ��
    int start_index = 0;
    for (int i = 0; ; ++i) {
        const char cch = original_code[i];
        if (is_macro) {                   //��ָ��
            if (!cch || cch == '\n') {
                setComponent(start_index, i, VT::VTMacro);
                is_macro = false;
            }
        }
        else if (is_single_line_comment) {//����ע��
            if (!cch || cch == '\n') {
                setComponent(start_index, i, VT::VTComment);
                is_single_line_comment = false;
            }
        }
        else if (is_multiline_comment) {  //����ע��
            if (cch == '/' && original_code[i - 1] == '*') {
                setComponent(start_index, i + 1, VT::VTComment);
                is_multiline_comment = false;
            }
        }
        else if (is_string) {             //�ַ�������
            if (cch == '\"' && original_code[i - 1] != '\\') {
                setComponent(start_index, i + 1, VT::VTString);
                is_string = false;
            }
        }
        else if (is_char) {               //�ַ�����
            if (cch == '\'' && original_code[i - 1] != '\\') {
                setComponent(start_index, i + 1, VT::VTCharacter);
                is_char = false;
            }
        }
        else if (cch == '*' && i != 0 && original_code[i - 1] == '/') {
            is_multiline_comment = true;
            start_index = i - 1;
        }
        else if (cch == '\"') {
            is_string = true;
            start_index = i;
        }
        else if (cch == '\'') {
            is_char = true;
            start_index = i;
        }
        else if (cch == '/' && i != 0 && original_code[i - 1] == '/') {
            is_single_line_comment = true;
            start_index = i - 1;
        }
        else if (cch == '#') {
            is_macro = true;
            start_index = i;
        }
        if (!cch) return;
    }
}

/* �����ָ�����ո�ͻس��� */
void LexAnalyzer::analyzeSpliters() {   //�ָ��
    int start_index = 0;
    bool is_spliter = false;
    for (int i = 0;; ++i) {
        if (component_type[i] && !is_spliter)
            continue;
        char cch = original_code[i];
        if (cch == ' ' || cch == '\t') {
            if (!is_spliter) {
                is_spliter = true;
                start_index = i;
            }
        }
        else {
            if (is_spliter) {
                setComponent(start_index, i, VT::VTWhiteSpace);
                is_spliter = false;
            }
        }

        if (cch == '\n')
            setComponent(i, i + 1, VT::VTEndLine);
        else if (!cch)
            break;
    }
}

/* �����ؼ���������� */
void LexAnalyzer::analyzeKeywordsAndOperators() {
    string tmp_code = original_code;
    for (int i = 0; i < code_length; ++i)
        if (component_type[i])
            tmp_code[i] = ' ';
    auto res = trie.match(tmp_code);
    for (auto& seg : res)
        if (is_operator(seg.val))
            setComponent(seg.begin, seg.end, seg.val);
    for (auto& seg : res)
        if (is_bracket(seg.val)) {
            setComponent(seg.begin, seg.end, seg.val);
        }
    for (auto& seg : res)
        if (is_keyword(seg.val))
            if ((seg.begin == 0 || component_type[seg.begin - 1]) && (seg.end == code_length || component_type[seg.end]))
                setComponent(seg.begin, seg.end, seg.val);
}

/* �޷��������жϹ��� */
bool ParseInteger(string& str)
{
    char state = '0';//��ʼ״̬
    int i = 0, n = str.length();
    char ch = str[i];
    while (state != '3' && state != '4' && i < n) {
        ch = str[i++];
        switch (state) {
        case '0':
            if ((ch >= '1') && (ch <= '9'))
                state = '1';//1-9��ת״̬ 1
            else if (ch == '0')
                state = '2';//0��ת״̬ 2
            else
                state = '3';//������ת״̬ 3
            break;
        case '1':
            if ((ch >= '0') && (ch <= '9'))
                state = '1';//0-9��ת״̬ 1
            else if (ch == ' ')
                state = '4';//������ת 4
            else
                state = '3';//������ת״̬ 3
            break;
        case '2':
            if (ch == ' ')
                state = '4';//������ת 4
            else
                state = '3';//������ת״̬ 3
            break;
        }
    }
    return state == '4';
}

/* �޷��Ÿ������жϹ��� */
bool ParseFloating(string& str)
{
    char state = '0';//��ʼ״̬
    int i = 0, n = str.length();
    char ch = str[i];
    while (state != '8' && state != '9' && i < n) {
        ch = str[i++];
        switch (state) {
        case '0':
            if ((ch >= '1') && (ch <= '9'))
                state = '1';//1-9��ת״̬ 1
            else if (ch == '0')
                state = '2';//0��ת״̬ 2
            else
                state = '8';//������ת״̬ 8
            break;
        case '1':
            if ((ch >= '0') && (ch <= '9'))
                state = '1';//0-9��ת״̬ 1
            else if (ch == 'e' || ch == 'E')
                state = '5';//e ��ת״̬ 5
            else if (ch == '.')
                state = '3';//. ��ת״̬ 3
            else if (ch == ' ')
                state = '9';//������ת 9
            else
                state = '8';//������ת״̬ 8
            break;
        case '2':
            if (ch == '.')
                state = '3';//. ��ת״̬ 3
            else
                state = '8';//������ת״̬ 8
            break;
        case '3':
            if ((ch >= '0') && (ch <= '9'))
                state = '4';//0-9��ת״̬ 4
            else
                state = '8';//������ת״̬ 8
            break;
        case '4':
            if ((ch >= '0') && (ch <= '9'))
                state = '4';//0-9��ת״̬ 4
            else if (ch == 'e' || ch == 'E')
                state = '5';//e ��ת״̬ 5
            else if (ch == ' ')
                state = '9';//�հף�ת 9
            else
                state = '8';//������ת״̬ 8
            break;
        case '5':
            if ((ch >= '0') && (ch <= '9'))
                state = '7';//0-9��ת״̬ 7
            else if (ch == '+' || ch == '-')
                state = '6';//+/-��ת״̬ 6
            else
                state = '8';//������ת״̬ 8
            break;
        case '6':
            if ((ch >= '0') && (ch <= '9'))
                state = '7';//0-9��ת״̬ 7
            else
                state = '8';//������ת״̬ 8
            break;
        case '7':
            if ((ch >= '0') && (ch <= '9'))
                state = '7';//0-9��ת״̬ 7
            else if (ch == ' ')
                state = '9';//�հף�ת 9
            else
                state = '8';//������ת״̬ 8
            break;
        }
    }
    return state == '9';
}

/* ��ʶ���жϹ��� */
bool ParseIdentifier(string& str)
{
    char state = '0';//��ʼ״̬
    int i = 0, n = str.length();
    char ch = str[i];
    while (state != '2' && state != '3' && i < n) {
        ch = str[i++];
        switch (state) {
        case '0':
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
                state = '1';//ת״̬ 1
            else if (ch == ' ')
                state = '3';//ת״̬ 3
            else
                state = '2';
            break;
        case '1':
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_')
                state = '1';//ת״̬ 1
            else if (ch == ' ')
                state = '3';//ת״̬ 3
            else
                state = '2';
            break;
        }
    }
    return state == '3';
}

/* ��������������������ʶ������������ */
void LexAnalyzer::analyzeWords() {
    int start_index = -1;
    string ori = original_code;
    for (int i = 0; ; ++i) {
        if (start_index < 0 && (original_code[i] && !component_type[i]))
            start_index = i;
        else if (start_index >= 0 && (!original_code[i] || component_type[i])) {
            string code = ori.substr(start_index, i - start_index) + ' ';
            if (code == "true " || code == "false ")
                setComponent(start_index, i, VT::VTBoolean);
            else if (ParseInteger(code))
                setComponent(start_index, i, VT::VTInteger);
            else if (ParseFloating(code))
                setComponent(start_index, i, VT::VTFloating);
            else if (ParseIdentifier(code))
                setComponent(start_index, i, VT::VTIdentifier);
            else
                setComponent(start_index, i, VT::VTWord);
            start_index = -1;
        }
        if (!original_code[i])
            break;
    }
}

/* �洢��� */
void LexAnalyzer::setComponent(int start_index, int end_index, VT component) {
    inner_result.emplace_back(start_index, end_index, component);
    for (int i = start_index; i < end_index; ++i)
        component_type[i] = component;
}
