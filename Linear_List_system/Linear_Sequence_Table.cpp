/*----------------------------------------------
 |  Linear Table On Sequence Structure         |
 |  Author:qrq 2402                            |
 |  Date:2025.4.7                              |
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>
#include <algorithm>

typedef int status;
typedef int ElemType;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define MAXSIZE 11
using namespace std;

typedef struct sqlist
{
    ElemType *elem;
    int length;
    int listsize;
    char name[30];
} SqList;

typedef struct
{
    SqList elem[MAXSIZE];
    int length;
    int cur_index;
} LISTS;

/*--------------------------------------------------*/

status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList &L);
int ListLength(SqList &L);
status GetElem(SqList &L, int i, ElemType &e);
int LocateElem(SqList &L, ElemType e);
status PriorElem(SqList &L, ElemType cur, ElemType &pre_e);
status NextElem(SqList &L, ElemType cur, ElemType &next_e);
status ListInsert(SqList &L, int i, ElemType &e);
status ListDelete(SqList &L, int i, ElemType &e);
status ListTraverse(SqList &L);

status MaxSubArray(SqList &L);
int SubArrayNum(SqList &L, int k);
status SortList(SqList &L);
status SaveList(SqList L, char FileName[]);
status LoadList(SqList &L, char FileName[]);

int LocateList(LISTS Lists, char ListName[]);
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
status SwitchList(LISTS &Lists, char ListName[]);
void PrintLists(LISTS Lists);
void printMenu(LISTS &Lists);

/*--------------------------------------------------*/

status InitList(SqList &L)
{
    if (L.elem != NULL)
        return INFEASIBLE;

    L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    if (L.elem == NULL)
        return OVERFLOW;

    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    return OK;
}

status DestroyList(SqList &L)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;

    return OK;
}

status ClearList(SqList &L)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    L.length = 0;

    return OK;
}

status ListEmpty(SqList &L)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    return L.length == 0 ? TRUE : FALSE;
}

int ListLength(SqList &L)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    return L.length;
}

status GetElem(SqList &L, int i, ElemType &e)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    if (i < 1 || i > L.length)
        return ERROR;

    e = L.elem[i - 1];
    return OK;
}

int LocateElem(SqList &L, ElemType e)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    for (int i = 0; i < L.length; i++)
    {
        if (e == L.elem[i])
            return i + 1;
    }

    return ERROR;
}

status PriorElem(SqList &L, ElemType e, ElemType &pre)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    for (int i = 0; i < L.length; i++)
    {
        if (e == L.elem[i] && i == 0)
        {
            printf("��Ԫ��Ϊ��Ԫ�أ���ǰ��Ԫ�أ�\n");
            return ERROR;
        }

        if (e == L.elem[i] && i != 0)
        {
            pre = L.elem[i - 1];
            return OK;
        }
    }

    return ERROR;
}

status NextElem(SqList &L, ElemType e, ElemType &next)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    for (int i = 0; i < L.length; i++)
    {
        if (e == L.elem[i] && i != L.length - 1)
        {
            next = L.elem[i + 1];
            return OK;
        }
    }

    return ERROR;
}

status ListInsert(SqList &L, int i, ElemType &e)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    if (i < 1 || i > L.length + 1)
        return ERROR;

    if (L.length >= L.listsize)
    {
        ElemType *Newlist = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (Newlist == NULL)
            return OVERFLOW;

        L.elem = Newlist;
        L.listsize += LISTINCREMENT;
    }

    for (int p = L.length - 1; p >= i - 1; p--)
    {
        L.elem[p + 1] = L.elem[p];
    }
    L.elem[i - 1] = e;
    L.length++;

    return OK;
}

status ListDelete(SqList &L, int i, ElemType &e)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    if (i < 1 || i > L.length)
        return ERROR;

    e = L.elem[i - 1];
    for (int p = i - 1; p < L.length - 1; p++)
    {
        L.elem[p] = L.elem[p + 1];
    }
    L.length--;

    return OK;
}

status ListTraverse(SqList &L)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    for (int i = 0; i < L.length; i++)
    {
        printf("%d", L.elem[i]);
        if (i != L.length - 1)
            printf(" ");
    }
    printf("\n");

    return OK;
}

status MaxSubArray(SqList &L)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    int currentMax = L.elem[0];
    int Max = L.elem[0];

    for (int i = 1; i < L.length; i++)
    {
        currentMax = max(L.elem[i], currentMax + L.elem[i]);
        Max = max(Max, currentMax);
    }

    return Max;
}

int SubArrayNum(SqList &L, int k)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    unordered_map<int, int> prefixSum;
    prefixSum[0] = 1;
    int sum = 0, cnt = 0;

    for (int i = 0; i < L.length; i++)
    {
        sum += L.elem[i];
        cnt += prefixSum[sum - k];
        prefixSum[sum]++;
    }

    return cnt;
}

status SortList(SqList &L)
{
    if (L.elem == NULL)
        return INFEASIBLE;

    sort(L.elem, L.elem + L.length);
    return OK;
}

status SaveList(SqList L, char FileName[])
{
    if (L.elem == NULL)
        return INFEASIBLE;

    FILE *fp = fopen(FileName, "w");
    if (fp == NULL)
        return ERROR;

    for (int i = 0; i < L.length; i++)
    {
        fprintf(fp, "%d ", L.elem[i]);
    }
    fclose(fp);

    return OK;
}

status LoadList(SqList &L, char FileName[])
{
    if (L.elem != NULL)
        return INFEASIBLE;

    FILE *fp = fopen(FileName, "r");
    if (fp == NULL)
        return ERROR;

    L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    if (L.elem == NULL)
    {
        fclose(fp);
        return OVERFLOW;
    }

    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    ElemType num;
    while (fscanf(fp, "%d", &num) == 1)
    {
        if (L.length >= L.listsize)
        {
            ElemType *Newlist = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
            if (Newlist == NULL)
            {
                fclose(fp);
                return OVERFLOW;
            }
            L.elem = Newlist;
            L.listsize += LISTINCREMENT;
        }
        L.elem[L.length++] = num;
    }

    fclose(fp);

    return OK;
}

status AddList(LISTS &Lists, char ListName[])
{
    if (Lists.length >= MAXSIZE)
        return ERROR;

    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
            return ERROR;
    }

    SqList &newList = Lists.elem[Lists.length];
    newList.elem = NULL;
    newList.length = 0;
    strcpy(newList.name, ListName);
    Lists.length++;

    Lists.cur_index = Lists.length - 1;
    return OK;
}

status RemoveList(LISTS &Lists, char ListName[])
{
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            free(Lists.elem[i].elem);
            for (int j = i; j < Lists.length - 1; j++)
            {
                Lists.elem[j] = Lists.elem[j + 1];
            }

            Lists.elem[Lists.length - 1].elem = NULL;
            Lists.elem[Lists.length - 1].length = 0;
            Lists.elem[Lists.length - 1].listsize = 0;
            memset(Lists.elem[Lists.length - 1].name, 0, 30);

            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}

int LocateList(LISTS Lists, char ListName[])
{
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            return i + 1;
        }
    }

    return ERROR;
}

void PrintLists(LISTS Lists)
{
    printf("��ǰ���Ա��б�\n");
    for (int i = 0; i < Lists.length; i++)
    {
        printf("%d. %s\n", i + 1, Lists.elem[i].name);
    }
}

void printMenu(LISTS &Lists)
{
    printf("\n\n");
    printf("--------------------------------------------------\n");
    printf("   Menu for Linear Table On Sequence Structure \n");
    printf("--------------------------------------------------\n");
    printf("��ǰ������Ϊ��%s\n", Lists.elem[Lists.cur_index].name);
    printf("        1.  InitList       11. ListDelete   \n");
    printf("        2.  DestroyList    12. ListTraverse \n");
    printf("        3.  ClearList      13. MaxSubArray  \n");
    printf("        4.  ListEmpty      14. SubArrayNum  \n");
    printf("        5.  ListLength     15. SortList     \n");
    printf("        6.  GetElem        16. SaveList     \n");
    printf("        7.  LocateElem     17. LoadList     \n");
    printf("        8.  PriorElem      18. AddList      \n");
    printf("        9.  NextElem       19. RemoveList   \n");
    printf("       10.  ListInsert     20. LocateList   \n");
    printf("       21.  SwitchList     22. PrintLists    \n");
    printf("        0.Exit    \n");
    printf("--------------------------------------------------\n");
    printf("�����빦�����[0~20]:");
}

int main()
{
    LISTS Lists;
    Lists.length = 1;
    Lists.cur_index = 0;
    Lists.elem[0].elem = NULL;
    char firstname[30];
    system("cls");
    printf("--------------------------------------------------\n");
    printf("����һ�������Ա�ϵͳ�����ԶԵ����������Ա���в���\n");
    printf("������CS2402 ����ǫ\n");
    printf("�ڿ�ʼ֮ǰ�����������һ�����Ա�����ƣ�\n");
    if (scanf("%s", firstname) != 1)
    {
        printf("����������������룺\n");
        scanf("%s", firstname);
    }
    printf("����ɹ�����һ�����Ա�������ǣ�%s\n", firstname);
    strcpy(Lists.elem[0].name, firstname);
    printf("������������˵����棬�������������\n");
    getchar();
    getchar();

    int op = 1;
    int i, e, k;
    int pre_e, cur_e, next_e;
    int Maxsub;
    int cnt;
    char filename[30], listname[30];

    while (op)
    {
        printMenu(Lists);
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            if (InitList(Lists.elem[Lists.cur_index]) == OK)
                printf("���Ա��ʼ���ɹ�!\n");
            else
                printf("���Ա��Ѵ��ڻ��ʼ��ʧ��!\n");
            break;

        case 2:
            if (DestroyList(Lists.elem[Lists.cur_index]) == OK)
                printf("�������٣�\n");
            else
                printf("�����ڣ�����ʧ�ܣ�\n");
            break;

        case 3:
            if (ClearList(Lists.elem[Lists.cur_index]) == OK)
                printf("������գ�\n");
            else
                printf("���ʧ�ܣ������ڣ�\n");
            break;

        case 4:
            if (ListEmpty(Lists.elem[Lists.cur_index]) == TRUE)
                printf("��Ϊ�գ�\n");
            else if (ListEmpty(Lists.elem[Lists.cur_index]) == FALSE)
                printf("��ǿգ�\n");
            else
                printf("�����ڣ�\n");
            break;

        case 5:
            if (ListLength(Lists.elem[Lists.cur_index]) != INFEASIBLE)
                printf("����Ϊ��%d\n", ListLength(Lists.elem[Lists.cur_index]));
            else
                printf("�����ڣ�\n");
            break;

        case 6:
            printf("������Ҫ��ȡ��Ԫ��λ�ã�");
            scanf("%d", &i);
            if (GetElem(Lists.elem[Lists.cur_index], i, e) == OK)
                printf("�� %d ��Ԫ��Ϊ��%d\n", i, e);
            else
                printf("λ�÷Ƿ�������ڣ�\n");
            break;

        case 7:
            printf("������Ҫ���ҵ�Ԫ��ֵ��");
            scanf("%d", &e);
            i = LocateElem(Lists.elem[Lists.cur_index], e);
            if (i != ERROR)
                printf("Ԫ�� %d ��λ��Ϊ��%d\n", e, i);
            else
                printf("����ʧ�ܣ�\n");
            break;

        case 8:
            printf("�����뵱ǰԪ��ֵ��");
            scanf("%d", &cur_e);
            if (PriorElem(Lists.elem[Lists.cur_index], cur_e, pre_e) == OK)
                printf("ǰ��Ԫ��Ϊ��%d\n", pre_e);
            else
                printf("Ѱ��ǰ��ʧ�ܣ�\n");
            break;

        case 9:
            printf("�����뵱ǰԪ��ֵ��");
            scanf("%d", &cur_e);
            if (NextElem(Lists.elem[Lists.cur_index], cur_e, next_e) == OK)
                printf("���Ԫ��Ϊ��%d\n", next_e);
            else
                printf("�޺��Ԫ�ػ�����ڣ�\n");
            break;

        case 10:
            printf("���������λ�ú�Ԫ��ֵ��");
            scanf("%d%d", &i, &e);
            if (ListInsert(Lists.elem[Lists.cur_index], i, e) == OK)
                printf("����ɹ���\n");
            else
                printf("����ʧ�ܣ�λ�÷Ƿ�������ڣ�\n");
            break;

        case 11:
            printf("������Ҫɾ����λ�ã�");
            scanf("%d", &i);
            if (ListDelete(Lists.elem[Lists.cur_index], i, e) == OK)
                printf("ɾ���ɹ���ɾ��Ԫ��Ϊ��%d\n", e);
            else
                printf("ɾ��ʧ�ܣ�λ�÷Ƿ�������ڣ�\n");
            break;

        case 12:
            printf("��ǰ������Ϊ��\n");
            if (ListTraverse(Lists.elem[Lists.cur_index]) == INFEASIBLE)
                printf("�����ڣ�\n");
            break;

        case 13:
            Maxsub = MaxSubArray(Lists.elem[Lists.cur_index]);
            if (Maxsub != INFEASIBLE)
                printf("����������Ϊ��%d\n", Maxsub);
            else
                printf("�����ڻ�Ƿ���\n");
            break;

        case 14:
            printf("������Ҫ��ѯ��������͵Ĵ�С��");
            scanf("%d", &k);
            cnt = SubArrayNum(Lists.elem[Lists.cur_index], k);
            if (cnt != INFEASIBLE)
                printf("��Ϊ%d�����������: %d\n", k, cnt);
            else
                printf("�����ڻ�Ƿ���\n");
            break;

        case 15:
            if (SortList(Lists.elem[Lists.cur_index]) == OK)
                printf("���Ա�������ɹ���\n");
            else
                printf("�����ڣ�\n");
            break;

        case 16:
            printf("�������ļ�����");
            scanf("%s", filename);
            if (SaveList(Lists.elem[Lists.cur_index], filename) == OK)
                printf("����ɹ���\n");
            else
                printf("����ʧ�ܻ�����ڣ�\n");
            break;

        case 17:
            printf("�������ļ�����");
            scanf("%s", filename);
            if (LoadList(Lists.elem[Lists.cur_index], filename) == OK)
                printf("���سɹ���\n");
            else
                printf("����ʧ�ܻ���Ѵ��ڣ�\n");
            break;

        case 18:
            printf("������Ҫ��ӵı�����");
            scanf("%s", listname);
            if (AddList(Lists, listname) == OK)
                printf("��ӳɹ���\n");
            else
                printf("���ʧ�ܣ����Ѵ��ڻ��ڴ治�㣡\n");
            break;

        case 19:
            printf("������Ҫɾ���ı�����");
            scanf("%s", listname);
            if (RemoveList(Lists, listname) == OK)
                printf("ɾ���ɹ���\n");
            else
                printf("ɾ��ʧ�ܣ������ڣ�\n");
            break;

        case 20:
            printf("������Ҫ���ҵı�����");
            scanf("%s", listname);
            i = LocateList(Lists, listname);
            if (i != ERROR)
                printf("�� %s ��λ��Ϊ��%d\n", listname, i);
            else
                printf("��δ�ҵ���\n");
            break;

        case 21:
            printf("������Ҫ�л����ı�����");
            scanf("%s", listname);
            i = LocateList(Lists, listname);
            if (i != ERROR)
            {
                Lists.cur_index = i - 1;
                printf("�л��ɹ�����ǰ������Ϊ��%s\n", Lists.elem[Lists.cur_index].name);
            }
            else
                printf("����ı����ڣ�\n");
            break;

        case 22:
            PrintLists(Lists);
            break;
        case 0:
            printf("�˳�����\n");
            break;

        default:
            printf("��Ч���������������룡\n");
            break;
        }

        if (op != 0)
        {
            printf("���س�������...\n");
            getchar();
            getchar();
        }
    }

    return 0;
}
