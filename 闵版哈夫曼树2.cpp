#include <stdio.h>
#include <stdlib.h>

//��������ı��ļ����ַ�����
#define MAXSIZE 100

typedef struct NODE
{
    char c;
    //���Ȩ��
    int weight;
    //��¼����ʾ�Ķ����ƣ���0��1
    int binary;
    //�Ƿ��Ѿ������ý�㣬1Ϊ������0Ϊδ����
    int flag;

    struct NODE *lchild, *rchild, *parent;

} NODE, *PNODE;

typedef struct
{
    int valuse[MAXSIZE];
    int top;
} STACK;

/**
 * ջ����ز���
 **/
void initStack(STACK &stack)
{
    stack.top = 0;
}

void push(STACK &stack, int value)
{
    stack.valuse[stack.top++] = value;
}

int pop(STACK &stack)
{
    if (stack.top == 0)
        return -1;
    stack.top--;
    return stack.valuse[stack.top];
}

//��ʼ�������
void initNode(PNODE node)
{
    node->lchild = NULL;
    node->parent = NULL;
    node->rchild = NULL;
    node->flag = 0;
    node->weight = 0;
    node->c = -1;
    node->binary = 0;
}

/**
 * �������
 * 
 * param �½ڵ��Ȩ��
 **/
PNODE createNode(int weight)
{
    PNODE node = (PNODE)malloc(sizeof(NODE));
    if (node)
    {
        initNode(node);
        node->weight = weight;
    }
    return node;
}

/**
 * �����ַ��ı���
 * �������е�Ҷ�ӽ�㣬�ҵ����ַ����Ӧ��Ҷ�ӽ�㣬���ϱ�������·����ջ
 * 
 * param c ��������ַ�
 * param childrenNodes Ҷ�ӽ��ļ���
 * param lenOfNodes Ҷ�ӽ��ĸ���
 * return ���ر����Ҷ�ӽ��·����ջ
 **/
STACK charEncode(char c, PNODE childrenNodes, int lenOfNodes)
{
    STACK stack;
    initStack(stack);
    for (int i = 0; i < lenOfNodes; i++)
    {
        if (c == childrenNodes[i].c)
        {
            PNODE tmp = &childrenNodes[i];
            while (tmp->parent != NULL)
            {
                push(stack, tmp->binary);
                tmp = tmp->parent;
            }
            break;
        }
    }
    return stack;
}

/**
 * �����ַ����ı���
 * 
 * param str ��������ַ���
 * param childrenNodes ����������Ҷ�ӽڵ�ļ���
 * param lenOfNodes Ҷ�ӽ��ĸ���
 * return ���ر����Ķ������ַ���
 **/
char *strEncode(char *str, PNODE childrenNodes, int lenOfNodes)
{
    char *result = (char *)malloc(sizeof(char) * MAXSIZE * lenOfNodes);
    int len = 0;
    while (*str != '\0')
    {
        STACK stack = charEncode(*str, childrenNodes, lenOfNodes);
        while (stack.top > 0)
        {
            result[len++] = pop(stack) + '0';
        }
        str++;
    }
    result[len] = '\0';
    return result;
}

/**
 * ��ȡȨ����С�Ľ��
 * 
 * param nodes Ҷ�ӽ��ļ���
 * param lenOfNodes Ҷ�ӽ��ĸ���
 * return ���ظ�Ҷ�ӽ��ĵ�ַ�������еĽ�㶼�Ѵ���������NULL
 **/
PNODE getMinWeightNode(PNODE nodes, int lenOfNodes)
{
    PNODE node;
    int min = 0, i;

    //���Ѵ������Ľ����й���
    while (min < lenOfNodes)
    {
        if (nodes[min].flag == 0)
        {
            break;
        }
        min++;
    }

    if (min == lenOfNodes)
    {
        return NULL;
    }

    //����δ�����Ľ����Ȩ����С�Ľ��
    for (i = min + 1; i < lenOfNodes; i++)
    {
        if (nodes[i].flag == 0 && nodes[i].weight < nodes[min].weight)
        {
            min = i;
            continue;
        }
    }

    nodes[min].flag = 1;
    return &nodes[min];
}

/**
 * ����Ҷ�ӽ�㴴����������
 * 
 * param nodes Ҷ�ӽ��ļ���
 * param lenOfNode Ҷ�ӽ��ĸ���
 * param childNode �ӽ���һ��
 **/
PNODE createHuffmanTree(PNODE nodes, int lenOfNodes, PNODE childNode)
{
    PNODE minWeightNode, parentNode;

    minWeightNode = getMinWeightNode(nodes, lenOfNodes);

    if (!minWeightNode)
        return childNode;

    if (!childNode)
    {
        parentNode = minWeightNode;
    }
    else
    {
        parentNode = createNode(childNode->weight + minWeightNode->weight);

        if (childNode->weight < minWeightNode->weight)
        {
            parentNode->lchild = childNode;
            parentNode->rchild = minWeightNode;
        }
        else
        {
            parentNode->rchild = childNode;
            parentNode->lchild = minWeightNode;
        }
        parentNode->lchild->binary = 0;
        parentNode->rchild->binary = 1;

        childNode->parent = minWeightNode->parent = parentNode;
    }

    createHuffmanTree(nodes, lenOfNodes, parentNode);
}

/**
 * ����д��ĸת��Сд��ĸ
 * �����ִ�Сд�����������Ķ�����һ��������Ч�ʽ���
 * 
 * param c ������ַ�
 * return ��������ַ��Ǵ�д��ĸ��ת����Сд��ĸ�����������ַ���������
**/
char charTolowercase(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        c += 'a' - 'A';
    }
    return c;
}

/**
 * �����ַ�����Ƶ�ʴ�����������
 * ���ع������������
 * 
 * param buff ���������ȡ���ַ���������
 * param nodes ������¼���е�Ҷ�ӽ��
 * param lenOfNodes ��������Ҷ�ӽ��ĸ���
 **/
PNODE readFromSource(const char *filePath, char *buff, PNODE childrenNodes, int &lenOfNodes)
{

    //��¼�ַ�������
    int lenOfStr = 0, i;

    //��¼��ǰ��ȡ���ַ�
    char c;

    FILE *file = fopen(filePath, "rb");

    if (file == NULL)
    {
        puts("Can't find source file!");
        exit(0);
    }

    //һ���ַ�һ���ַ����뱾���ı�
    c = fgetc(file);
    while (!feof(file))
    {
        c = charTolowercase(c);
        //��ʼ�����
        initNode(&childrenNodes[lenOfNodes]);

        buff[lenOfStr++] = c;
        for (i = 0; i < lenOfNodes; i++)
        {
            if (childrenNodes[i].c == c)
            {
                childrenNodes[i].weight++;
                break;
            }
        }
        if (i == lenOfNodes)
        {
            childrenNodes[lenOfNodes].c = c;
            childrenNodes[lenOfNodes++].weight++;
        }
        c = fgetc(file);
    }
    buff[lenOfStr] = '\0';

    fclose(file);
    return createHuffmanTree(childrenNodes, lenOfNodes, NULL);
}

/**
 * ���������ַ������뱾���ļ�
 * param filePath ����ŵı����ļ�·��
 * param result �����Ķ����ƽ��
 **/
void writeResult(const char *filePath, char *result)
{
    FILE *fp = fopen(filePath, "wb");
    if (fputs(result, fp) >= 0)
    {
        printf("���ɽ���ɹ�\r\n");
    }
    fclose(fp);
}

/**
 * �������Ķ������ַ������н���
 * param str ������Ķ������ַ���
 * param �������������
 * return ���ؽ������ַ���
 * 
 * tips:���������Ǹ���ԭ�ַ������������һ������Ӧһ�ֱ��뷽ʽ
 **/
char *strDecode(const char *str, PNODE TreeRoot)
{
    const char *tmp = str;
    char *result = (char *)malloc(sizeof(char) * MAXSIZE);
    //������¼����ַ����ĳ���
    int len = 0;
    while (*tmp != '\0')
    {
        PNODE tmpNode = TreeRoot;
        while (tmpNode->lchild && tmpNode->rchild)
        {
            tmpNode = *tmp == '0' ? tmpNode->lchild : tmpNode->rchild;
            tmp++;
        }
        result[len++] = tmpNode->c;
    }
    result[len] = '\0';
    return result;
}

int main()
{
    char buff[MAXSIZE];

    NODE childrenNodes[MAXSIZE];

    int len = 0;

    //ȷ��source.txt��exe����ͬĿ¼
    PNODE root = readFromSource("source.txt", buff, childrenNodes, len);

    writeResult("result.txt", strEncode(buff, childrenNodes, len));

    printf("%s", strDecode("11111111111110111111111110011101111111111011001110011111111101111111101111111011111101111101100111101010", root));

    return 0;
}


