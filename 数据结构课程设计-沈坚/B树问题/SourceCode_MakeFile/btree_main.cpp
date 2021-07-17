#define _CRT_SECURE_NO_WARNINGS
#define MAXM 10                     //����B�������Ľ���
#include <fstream>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

const int M = 3;                      //�趨B���Ľ��� 
const int MAX = M - 1;                //�������ؼ������� 
const int MIN = (M - 1) / 2;          //������С�ؼ������� 

typedef struct node {               //B����B��������� 
    int keynum;                     //���ؼ��ָ���
    int key[MAXM];                  //�ؼ������飬key[0]��ʹ�� 
    struct node* parent;            //˫�׽��ָ��
    struct node* ptr[MAXM];         //���ӽ��ָ������ 
} BTNode, * BTree;

typedef struct {                    //B�����ҽ������ 
    BTNode* pt;                     //ָ���ҵ��Ľ��
    int i;                          //�ڽ���еĹؼ���λ��; 
    bool tag;                       //���ҳɹ�����־
} Result;

typedef enum status {               //ö�����ͣ����ε����� 
    TRUE,
    FALSE,
    OK,
    ERROR,
    LOVERFLOW,
    EMPTY
} Status;

//�����÷�
void Usage()
{
    cout << "Usage : ./btree --input in.dat --output out.dat �� ./btree --output out.dat --input in.dat" << endl;
}

bool isnumber(char* ch_m, int& m)
{
    m = 0;
    for (int i = 0; ch_m[i]; i++) {
        if (!(ch_m[i] >= '0' && ch_m[i] <= '9'))
            return false;
        m *= 10;
        m += ch_m[i] - '0';
    }
    return true;
}

//��ʼ��B�� 
Status InitBTree(BTree& t) {
    t = NULL;
    return OK;
}

//�ڽ��p�в��ҹؼ���k�Ĳ���λ��i 
int SearchBTNode(BTNode* p, int k) {
    int i = 0;
    for (i = 0; i < p->keynum && p->key[i + 1] <= k; i++);
    return i;
}

//����t�ϲ��ҹؼ���k, ���ؽ��(pt, i, tag)
//�����ҳɹ�, ������ֵtag = 1, �ؼ���k��ָ��pt��ָ����е�i���ؼ���
//��������ֵtag = 0, �ؼ���k�Ĳ���λ��Ϊpt���ĵ�i��
Result SearchBTree(BTree t, int k) {
    BTNode* p = t, * q = NULL;                      //��ʼ�����p�ͽ��q, pָ�������,qָ��p��˫��
    bool found_tag = false;                        //�趨���ҳɹ�����־ 
    int i = 0;
    Result r;                                      //�趨���صĲ��ҽ�� 

    while (p && found_tag == false) {
        i = SearchBTNode(p, k);                        //�ڽ��p�в��ҹؼ���k, ʹ��p->key[i] <= k < p->key[i+1]
        if (i > 0 && p->key[i] == k)                   //�ҵ�����ؼ��� 
            found_tag = true;                          //���ҳɹ� 
        else {                                         //����ʧ�� 
            q = p;
            p = p->ptr[i];
        }
    }

    if (found_tag == true) {                         //���ҳɹ�
        r.pt = p;
        r.i = i;
        r.tag = true;
    }
    else {                                           //����ʧ��
        r.pt = q;
        r.i = i;
        r.tag = false;
    }

    return r;                                       //���عؼ���k��λ��(�����λ��)
}

//���ؼ���k�ͽ��q�ֱ���뵽p->key[i + 1]��p->ptr[i + 1]��
void InsertBTNode(BTNode*& p, int i, int k, BTNode* q) {
    int j;
    for (j = p->keynum; j > i; j--) {                       //������ƿճ�һ��λ��
        p->key[j + 1] = p->key[j];
        p->ptr[j + 1] = p->ptr[j];
    }
    p->key[i + 1] = k;
    p->ptr[i + 1] = q;
    if (q)
        q->parent = p;
    p->keynum++;
}

//�����p���ѳ��������,ǰһ�뱣��,��һ��������q
void SplitBTNode(BTNode*& p, BTNode*& q) {
    int i;
    int s = (M + 1) / 2;
    q = (BTNode*)malloc(sizeof(BTNode));             //�����q����ռ�

    q->ptr[0] = p->ptr[s];                            //��һ��������q
    for (i = s + 1; i <= M; i++) {
        q->key[i - s] = p->key[i];
        q->ptr[i - s] = p->ptr[i];
    }
    q->keynum = p->keynum - s;
    q->parent = p->parent;
    for (i = 0; i <= p->keynum - s; i++)                     //�޸�˫��ָ�� 
        if (q->ptr[i])
            q->ptr[i]->parent = q;
    p->keynum = s - 1;                                  //���p��ǰһ�뱣��,�޸Ľ��p��keynum
}

//�����µĸ����t,ԭp��qΪ����ָ��
void NewRoot(BTNode*& t, int k, BTNode* p, BTNode* q) {
    t = (BTNode*)malloc(sizeof(BTNode));            //����ռ� 
    t->keynum = 1;
    t->ptr[0] = p;
    t->ptr[1] = q;
    t->key[1] = k;
    if (p)                                          //�������p�ͽ��q��˫��ָ�� 
        p->parent = t;
    if (q)
        q->parent = t;
    t->parent = NULL;
}

//����t�Ͻ��p��key[i]��key[i + 1]֮�����ؼ���k�������������,����˫�������б�Ҫ�Ľ����ѵ���,ʹt����B��
void InsertBTree(BTree& t, int i, int k, BTNode* p) {
    BTNode* q;
    bool finish_tag, newroot_tag;
    int s;                   //�趨��Ҫ�½���־�Ͳ�����ɱ�־ 
    int x;
    if (p == NULL)                                     //t�ǿ���
        NewRoot(t, k, NULL, NULL);                     //���ɽ����ؼ���k�ĸ����t
    else {
        x = k;
        q = NULL;
        finish_tag = false;
        newroot_tag = false;
        while (finish_tag == false && newroot_tag == false) {
            InsertBTNode(p, i, x, q);                  //���ؼ���x�ͽ��q�ֱ���뵽p->key[i+1]��p->ptr[i+1]
            if (p->keynum <= MAX)
                finish_tag = true;                     //�������
            else {
                s = (M + 1) / 2;
                SplitBTNode(p, q);                    //���ѽ�� 
                x = p->key[s];
                if (p->parent) {                      //����x�Ĳ���λ��
                    p = p->parent;
                    i = SearchBTNode(p, x);
                }
                else                                //û�ҵ�x����Ҫ�½�� 
                    newroot_tag = true;
            }
        }
        if (newroot_tag == true)                          //������ѷ���Ϊ���p��q 
            NewRoot(t, x, p, q);                       //�����¸����t,p��qΪ����ָ��
    }
}

//��Ҷ�ӽ��pɾ��key[i]�����ĺ���ָ��ptr[i]
void DeleteBTLeaf(BTNode* p, int i) {
    int j;
    for (j = i + 1; j <= p->keynum; j++) {                    //ǰ��ɾ��key[i]��ptr[i]
        p->key[j - 1] = p->key[j];
        p->ptr[j - 1] = p->ptr[j];
    }
    p->keynum--;
}

//���ұ�ɾ�ؼ���p->key[i](�ڷ�Ҷ�ӽ����)�����Ҷ�ӽ��(��������ֵ��С�Ĺؼ���) 
void Substitution(BTNode* p, int i) {
    BTNode* q;
    for (q = p->ptr[i]; q->ptr[0] != NULL; q = q->ptr[0]);
    p->key[i] = q->key[1];                            //���ƹؼ���ֵ
}

//��˫�׽��p�е����һ���ؼ��������ҽ��q�У�������aq�е����һ���ؼ�������˫�׽��p��
void BorrowLeft(BTNode* p, int i) {
    int j;
    BTNode* q = p->ptr[i];
    BTNode* aq = p->ptr[i - 1];

    for (j = q->keynum; j > 0; j--) {                       //�����ֵ�q�����йؼ�������ƶ�һλ
        q->key[j + 1] = q->key[j];
        q->ptr[j + 1] = q->ptr[j];
    }

    q->ptr[1] = q->ptr[0];                            //��˫�׽��p�ƶ��ؼ��ֵ����ֵ�q��
    q->key[1] = p->key[i];
    q->keynum++;

    p->key[i] = aq->key[aq->keynum];                  //�����ֵ�aq�����һ���ؼ����ƶ���˫�׽��p��
    p->ptr[i]->ptr[0] = aq->ptr[aq->keynum];
    aq->keynum--;
}

//��˫�׽��p�еĵ�һ���ؼ�����������aq�У����ҽ��q�еĵ�һ���ؼ�������˫�׽��p��
void BorrowRight(BTNode* p, int i) {
    int j;
    BTNode* aq = p->ptr[i - 1];
    BTNode* q = p->ptr[i];

    aq->keynum++;                                   //��˫�׽��p�еĹؼ����ƶ������ֵ�aq��
    aq->key[aq->keynum] = p->key[i];
    aq->ptr[aq->keynum] = p->ptr[i]->ptr[0];

    p->key[i] = q->key[1];                            //�����ֵ�q�еĹؼ����ƶ���˫�׽ڵ�p��
    q->ptr[0] = q->ptr[1];
    q->keynum--;

    for (j = 1; j <= q->keynum; j++) {                     //�����ֵ�q�����йؼ�����ǰ�ƶ�һλ
        q->key[j] = q->key[j + 1];
        q->ptr[j] = q->ptr[j + 1];
    }
}

//��˫�׽��p���ҽ��q�ϲ�������aq��������˫�׽��p�е�ʣ��ؼ��ֵ�λ��
void MergeBTNode(BTNode* p, int i) {
    int j;
    BTNode* q = p->ptr[i];
    BTNode* aq = p->ptr[i - 1];

    aq->keynum++;                                  //��˫�׽��Ĺؼ���p->key[i]���뵽����aq     
    aq->key[aq->keynum] = p->key[i];
    aq->ptr[aq->keynum] = q->ptr[0];

    for (j = 1; j <= q->keynum; j++) {                      //���ҽ��q�е����йؼ��ֲ��뵽����aq 
        aq->keynum++;
        aq->key[aq->keynum] = q->key[j];
        aq->ptr[aq->keynum] = q->ptr[j];
    }

    for (j = i; j < p->keynum; j++) {                       //��˫�׽��p�е�p->key[i]������йؼ�����ǰ�ƶ�һλ 
        p->key[j] = p->key[j + 1];
        p->ptr[j] = p->ptr[j + 1];
    }
    p->keynum--;                                    //�޸�˫�׽��p��keynumֵ 
    free(q);                                        //�ͷſ��ҽ��q�Ŀռ�
}

//ɾ�����p�еĵ�i���ؼ��ֺ�,����B��
void AdjustBTree(BTNode* p, int i) {
    if (i == 0)                                        //ɾ����������߹ؼ���
        if (p->ptr[1]->keynum > MIN)                   //�ҽ����Խ�
            BorrowRight(p, 1);
        else                                        //���ֵܲ����� 
            MergeBTNode(p, 1);
    else if (i == p->keynum)                           //ɾ���������ұ߹ؼ���
        if (p->ptr[i - 1]->keynum > MIN)                 //������Խ� 
            BorrowLeft(p, i);
        else                                        //���㲻���� 
            MergeBTNode(p, i);
    else if (p->ptr[i - 1]->keynum > MIN)                //ɾ���ؼ������в������㹻�� 
        BorrowLeft(p, i);
    else if (p->ptr[i + 1]->keynum > MIN)                //ɾ���ؼ������в����ҽ�㹻�� 
        BorrowRight(p, i + 1);
    else                                            //ɾ���ؼ������в������ҽ�㶼������
        MergeBTNode(p, i);
}

//��ӳ�Ƿ��ڽ��p���Ƿ���ҵ��ؼ���k 
bool FindBTNode(BTNode* p, int k, int& i) {
    if (k < p->key[1]) {                               //���p�в��ҹؼ���kʧ�� 
        i = 0;
        return false;
    }
    else {                                             //��p����в���
        i = p->keynum;
        while (k < p->key[i] && i > 1)
            i--;
        if (k == p->key[i])                            //���p�в��ҹؼ���k�ɹ� 
            return true;
    }
    return false;
}

//�ڽ��p�в��Ҳ�ɾ���ؼ���k
bool BTNodeDelete(BTNode* p, int k) {
    int i;
    bool found_tag;                                  //���ұ�־ 
    if (p == NULL)
        return false;
    else {
        found_tag = FindBTNode(p, k, i);                //���ز��ҽ�� 
        if (found_tag == true) {                           //���ҳɹ� 
            if (p->ptr[i - 1] != NULL) {                  //ɾ�����Ƿ�Ҷ�ӽ��
                Substitution(p, i);                  //Ѱ�����ڹؼ���(����������С�Ĺؼ���) 
                BTNodeDelete(p->ptr[i], p->key[i]);  //ִ��ɾ������ 
            }
            else
                DeleteBTLeaf(p, i);                        //�ӽ��p��λ��i��ɾ���ؼ���
        }
        else
            found_tag = BTNodeDelete(p->ptr[i], k);    //�غ��ӽ��ݹ���Ҳ�ɾ���ؼ���k
        if (p->ptr[i] != NULL)                         //p����Ҷ�ӽڵ�
            if (p->ptr[i]->keynum < MIN)               //ɾ����ؼ��ָ���С��MIN
                AdjustBTree(p, i);                     //����B�� 
        return found_tag;
    }
}

//ִ��ɾ������  
bool BTreeDelete(BTree& t, int k) {
    BTNode* p;
    bool flag = BTNodeDelete(t, k);                   //ɾ���ؼ���k 
    if (!flag)                                        //����ʧ�� 
        return false;
    else if (t->keynum == 0) {                        //���� 
        p = t;
        t = t->ptr[0];
        free(p);
    }
    return true;
}

//�ݹ��ͷ�B�� 
void DestroyBTree(BTree& t) {
    int i;
    BTNode* p = t;
    if (p) {                                    //B����Ϊ��  
        for (i = 0; i <= p->keynum; i++)        //�ݹ��ͷ�ÿһ����� 
            DestroyBTree(*&p->ptr[i]);
        free(p);
    }
    t = NULL;
}

//��ӡB��
void PrintBTree(BTree t, int count, ofstream& out)
{
    if (t) {
        int i, j;
        for (i = 1; i <= t->keynum; i++) {
            for (j = count; j > 0; j--)
                out << " ";
            out << t->key[i] << endl;
        }
        for (i = 0; i <= t->keynum; i++)
            if (t->ptr[i])
                PrintBTree(t->ptr[i], count + 2, out);
    }
}

//��ӡ����·��
void PrintSearchBTree(BTNode* t, int value, ofstream& out)
{
    if (t == NULL)
        return;
    else {
        int i;
        for (i = 1; i < t->keynum; i++)
            out << t->key[i] << " ";
        out << t->key[t->keynum];
        //�ڱ���С�ͱ�������м��ӽڵ���Ѱ����ȵ�
        for (i = 1; i <= t->keynum; i++)
            if (value <= t->key[i])
                break;
        //У�鵱ǰ�Ĺؼ����Ƿ���ڲ��ҵĹؼ���t
        if (i <= t->keynum && value == t->key[i])
            out << endl;
        else {
            out << "->";
            PrintSearchBTree(t->ptr[i - 1], value, out);//�����return������
        }
    }
}

int main(int argc, char** argv)
{
    if (argc != 5) {
        Usage();
        return 0;
    }
    if (!((!strcmp(argv[1], "--input") && !strcmp(argv[3], "--output")) || (!strcmp(argv[3], "--input") && !strcmp(argv[1], "--output")))) {
        Usage();
        return 0;
    }
    char* indata, * outdata;
    indata = (!strcmp(argv[1], "--input") ? argv[2] : argv[4]);
    outdata = (!strcmp(argv[1], "--output") ? argv[2] : argv[4]);

    //�ж��ļ��Ƿ���Դ�
    ifstream in(indata, ios::in);
    ofstream out(outdata, ios::out);
    if (!in.is_open()) {
        cout << "���ļ�" << indata << "ʧ��" << endl;
        return 0;
    }
    in.close();

    freopen(indata, "r", stdin);
    BTree t = NULL;
    Result s;
    InitBTree(t);
    char ch_m[1024];
    char ch[1024];
    int m;
    int cnt = scanf("%s %s", ch, ch_m);
    if (1) {
        while (1) {
            cnt = scanf("%s %s", ch, ch_m);
            if (cnt == -1)
                break;
            if (cnt == 2 && isnumber(ch_m, m)) {
                if (!strcmp(ch, "insert")) {
                    s = SearchBTree(t, m);
                    if (s.tag == true)
                        out << "Ҫ�����" << m << "�Ѵ���" << endl;
                    else {
                        InsertBTree(t, s.i, m, s.pt);
                        PrintBTree(t, 0, out);
                    }
                }
                else if (!strcmp(ch, "delete")) {
                    bool flag = BTreeDelete(t, m);
                    if (!flag)
                        out << "Ҫɾ����" << m << "������" << endl;
                    else
                        PrintBTree(t, 0, out);
                }
                else if (!strcmp(ch, "find")) {
                    s = SearchBTree(t, m);
                    if (s.tag == false)
                        out << "δ�ҵ��ڵ�" << m << endl;
                    else
                        PrintSearchBTree(t, m, out);
                }
            }
        }
    }
    else {
        while (1) {
            cnt = scanf("%s %s", ch, ch_m);
            if (cnt == -1)
                break;
            if (cnt == 2 && isnumber(ch_m, m)) {
                if (!strcmp(ch, "insert")) {
                    s = SearchBTree(t, m);
                    if (s.tag == true)
                        out << "Ҫ����Ľڵ�" << m << "�Ѵ���" << endl;
                    else {
                        InsertBTree(t, s.i, m, s.pt);
                        PrintBTree(t, 0, out);
                    }
                }
                else if (!strcmp(ch, "delete")) {
                    bool flag = BTreeDelete(t, m);
                    if (!flag)
                        out << "Ҫɾ���Ľڵ�" << m << "������" << endl;
                    else
                        PrintBTree(t, 0, out);
                }
                else if (!strcmp(ch, "find")) {
                    s = SearchBTree(t, m);
                    if (s.tag == false)
                        out << "δ�ҵ��ڵ�" << m << endl;
                    else {
                        out << "�ҵ��ڵ�" << m << "��·��Ϊ��" << endl;
                        PrintSearchBTree(t, m, out);
                    }
                }
                else
                    out << "����ָ�����" << endl;
            }
            else
                out << "����ָ�����" << endl;
            out << endl;
        }
    }
    DestroyBTree(t);
    return 0;
}