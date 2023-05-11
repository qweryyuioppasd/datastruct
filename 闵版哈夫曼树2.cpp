#include <stdio.h>
#include <stdlib.h>

//最大读入的文本文件的字符长度
#define MAXSIZE 100

typedef struct NODE
{
    char c;
    //结点权重
    int weight;
    //记录结点表示的二进制，左0右1
    int binary;
    //是否已经创建该结点，1为创建，0为未创建
    int flag;

    struct NODE *lchild, *rchild, *parent;

} NODE, *PNODE;

typedef struct
{
    int valuse[MAXSIZE];
    int top;
} STACK;

/**
 * 栈的相关操作
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

//初始化树结点
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
 * 创建结点
 * 
 * param 新节点的权重
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
 * 进行字符的编码
 * 遍历所有的叶子结点，找到与字符相对应的叶子结点，向上遍历，将路径入栈
 * 
 * param c 欲编码的字符
 * param childrenNodes 叶子结点的集合
 * param lenOfNodes 叶子结点的个数
 * return 返回保存该叶子结点路径的栈
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
 * 进行字符串的编码
 * 
 * param str 欲编码的字符串
 * param childrenNodes 哈夫曼树的叶子节点的集合
 * param lenOfNodes 叶子结点的个数
 * return 返回编码后的二进制字符串
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
 * 获取权重最小的结点
 * 
 * param nodes 叶子结点的集合
 * param lenOfNodes 叶子结点的个数
 * return 返回该叶子结点的地址，若所有的结点都已创建，返回NULL
 **/
PNODE getMinWeightNode(PNODE nodes, int lenOfNodes)
{
    PNODE node;
    int min = 0, i;

    //对已创建过的结点进行过滤
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

    //查找未创建的结点中权重最小的结点
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
 * 根据叶子结点创建哈夫曼树
 * 
 * param nodes 叶子结点的集合
 * param lenOfNode 叶子结点的个数
 * param childNode 子结点的一个
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
 * 将大写字母转成小写字母
 * 若区分大小写，哈夫曼树的度增加一倍，编码效率降低
 * 
 * param c 传入的字符
 * return 若传入的字符是大写字母则转换成小写字母，如是其他字符不做更改
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
 * 根据字符出现频率创建哈夫曼树
 * 返回哈夫曼树根结点
 * 
 * param buff 用来保存读取的字符串的数组
 * param nodes 用来记录所有的叶子结点
 * param lenOfNodes 用来保存叶子结点的个数
 **/
PNODE readFromSource(const char *filePath, char *buff, PNODE childrenNodes, int &lenOfNodes)
{

    //记录字符串长度
    int lenOfStr = 0, i;

    //记录当前读取的字符
    char c;

    FILE *file = fopen(filePath, "rb");

    if (file == NULL)
    {
        puts("Can't find source file!");
        exit(0);
    }

    //一个字符一个字符读入本地文本
    c = fgetc(file);
    while (!feof(file))
    {
        c = charTolowercase(c);
        //初始化结点
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
 * 将编码后的字符串存入本地文件
 * param filePath 欲存放的本地文件路径
 * param result 编码后的二进制结果
 **/
void writeResult(const char *filePath, char *result)
{
    FILE *fp = fopen(filePath, "wb");
    if (fputs(result, fp) >= 0)
    {
        printf("生成结果成功\r\n");
    }
    fclose(fp);
}

/**
 * 将编码后的二进制字符串进行解码
 * param str 欲解码的二进制字符串
 * param 哈夫曼树根结点
 * return 返回解码后的字符串
 * 
 * tips:哈夫曼树是根据原字符串构造而来，一棵树对应一种编码方式
 **/
char *strDecode(const char *str, PNODE TreeRoot)
{
    const char *tmp = str;
    char *result = (char *)malloc(sizeof(char) * MAXSIZE);
    //用来记录结果字符串的长度
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

    //确保source.txt和exe处于同目录
    PNODE root = readFromSource("source.txt", buff, childrenNodes, len);

    writeResult("result.txt", strEncode(buff, childrenNodes, len));

    printf("%s", strDecode("11111111111110111111111110011101111111111011001110011111111101111111101111111011111101111101100111101010", root));

    return 0;
}


