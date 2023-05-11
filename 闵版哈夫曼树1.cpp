/*
Descripttion: 
Version: 1.0
Author: 涂然 18计科3班 
Date: 2021-05-31 9:00:00
*/

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std; 

#define MaxSize 1024  // 读入文件的上限 
#define OK 1
#define ERROR 0
typedef int Status;

typedef struct wordcnt{  // 统计字符和对应的次数 
	char ch;
	int cnt = 0;
}Count;

typedef struct NumCount{  // 统计次数的外部封装 
	Count count[MaxSize];
	int length = 0;
}NumCount;

typedef struct HTree{  // 哈夫曼树结构 
	char data; 
	int weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree; 

typedef struct HCode{ // 编码结构 
	char data;
	char* str; 
}*HuffmanCode;


Status ReadData(char *source);  // 读入文件 
Status WordCount(char *data,NumCount *paraCnt); // 统计次数 
Status Show(NumCount *paraCnt);   // 展示次数 
Status CreateHuffmanTree(HuffmanTree &HT,int length,NumCount cntarray);  // 创建哈夫曼树 
Status select(HuffmanTree HT,int top,int *s1,int *s2);  // 选择权重最小的两个节点 
Status CreateHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int length);  // 创建哈夫曼编码 
Status Encode(char *data,HuffmanCode HC,int length);  // 将读入的文件编码，写到txt文件 
Status Decode(HuffmanTree HT,int length);  //读入编码文件，解码 

int main(int argc, char** argv) {
	char data[MaxSize];  
	NumCount Cntarray;
	ReadData(data);  // 读入数据 
	WordCount(data,&Cntarray);  // 统计次数 
//	Show(&Cntarray); //可以查看每个单词出现的对应次数 
	HuffmanTree tree;
	CreateHuffmanTree(tree,Cntarray.length,Cntarray);  // 建树 
	HuffmanCode code;  
	CreateHuffmanCode(tree,code,Cntarray.length);  // 创建编码 
	Encode(data,code,Cntarray.length);  // 生成编码文件 
	Decode(tree,Cntarray.length);  // 解码 
	cout<<"Please view the generated TXT file to check the result"<<endl; 
	return 0;
}

Status ReadData(char *source)
{
	//打开文件读入数据 
	ifstream infile;
	infile.open("in.txt");
	cout<<"Reading..."<<endl;
	cout<<"the input file is:"<<endl;
	infile.getline(source,MaxSize);
	cout<<source<<endl;
	infile.close();
	cout<<endl;
	return OK;
}

Status WordCount(char *data,NumCount *paraCnt)
{
	int flag;// 标识是否已经记录 
	int len = strlen(data);
	for(int i = 0;i < len;++i)
	{
		flag = 0;
		for(int j = 0;j < paraCnt->length;++j)
		{
			if(paraCnt->count[j].ch == data[i]) // 若已有记录，直接++ 
			{
				++paraCnt->count[j].cnt;
				flag = 1;
				break;
			}
			
		}
		if(!flag) // 没有记录，则新增 
		{
			paraCnt->count[paraCnt->length].ch = data[i];
			++paraCnt->count[paraCnt->length].cnt;
			++paraCnt->length;
		}
	}
	return OK;
}

Status Show(NumCount *paraCnt)
{
	cout<<"the length is "<<paraCnt->length<<endl;
	for(int i = 0;i < paraCnt->length;++i)
	{
		cout<<"The character "<<paraCnt->count[i].ch<<"  appears  "<<paraCnt->count[i].cnt<<endl;
	}
	cout<<endl;
	return OK;
}

Status CreateHuffmanTree(HuffmanTree &HT,int length,NumCount cntarray)
{
	if(length <= 1) return ERROR;
	int s1,s2;
	int m = length*2-1;  // 没有度为1的节点，则总结点是2*叶子节点数-1个 
	HT = new HTNode[m+1];
	for(int i = 1;i <= m;++i)  // 初始化 
	{
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	
	for(int i = 1;i <= length;++i) 
	{
		HT[i].data = cntarray.count[i-1].ch;
		HT[i].weight = cntarray.count[i-1].cnt;
	}
	
	for(int i = length + 1;i <= m;++i)
	{
		select(HT,i-1,&s1,&s2);  // 从前面的范围里选择权重最小的两个节点 
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;  // 得到一个新节点 
	}
	return OK;
}

Status select(HuffmanTree HT,int top,int *s1,int *s2)
{
	int min = INT_MAX;
	for(int i = 1;i <= top;++i)  // 选择没有双亲的节点中，权重最小的节点 
	{
		if(HT[i].weight < min && HT[i].parent == 0)
		{
			min = HT[i].weight;
			*s1 = i;
		}
	}
	
	min = INT_MAX;
	for(int i = 1;i <= top;++i)  // 选择没有双亲的节点中，权重次小的节点 
	{
		if(HT[i].weight < min && i != *s1 && HT[i].parent == 0)
		{
			min = HT[i].weight;
			*s2 = i;
		}
	}
	return OK;	
}

Status CreateHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int length)
{
	HC = new HCode[length+1];
	char *cd = new char[length];  // 存储编码的临时空间 
	cd[length-1] = '\0';  // 方便之后调用strcpy函数 
	int c,f,start;
	for(int i = 1;i <= length;++i)
	{
		start = length-1;  // start表示编码在临时空间内的起始下标，由于是从叶子节点回溯，所以是从最后开始 
		c = i;
		f = HT[c].parent;
		while(f != 0)
		{
			--start;  // 由于是回溯，所以从临时空间的最后往回计 
			if(HT[f].lchild == c)
				cd[start] = '0';
			else 
				cd[start] = '1';
			c = f;
			f = HT[c].parent;
		}
		HC[i].str = new char[length-start];  // 最后，实际使用的编码空间大小是length-start 
		HC[i].data = HT[i].data;
		strcpy(HC[i].str,&cd[start]);  // 从实际起始地址开始，拷贝到编码结构中 
	}
	delete cd;
}

Status Encode(char *data,HuffmanCode HC,int length)
{
	ofstream outfile;
	outfile.open("code.txt");
	for(int i = 0;i < strlen(data);++i)  // 依次读入数据，查找对应的编码，写入编码文件 
	{
		for(int j = 1;j <= length;++j)
		{
			if(data[i] == HC[j].data)
			{
				outfile<<HC[j].str;
			}
		}
	}
	outfile.close();
	cout<<"the code txt has been written"<<endl;
	cout<<endl;
	return OK;
}

Status Decode(HuffmanTree HT,int length)
{
	char codetxt[MaxSize*length];
	ifstream infile;
	infile.open("code.txt");
	infile.getline(codetxt,MaxSize*length);
	infile.close();
	
	ofstream outfile;
   	outfile.open("out.txt");
	
	int root = 2*length-1;  // 从根节点开始遍历 
	for(int i = 0;i < strlen(codetxt);++i)
	{
		if(codetxt[i] == '0') root = HT[root].lchild;  //为0表示向左遍历 
		else if(codetxt[i] == '1') root = HT[root].rchild; //为1表示向右遍历 
		if(HT[root].lchild == 0 && HT[root].rchild == 0)  // 如果已经是叶子节点，输出到输出文件中，然后重新回到根节点 
		{
			outfile<<HT[root].data;
			root = 2*length-1;
		}
	}
	outfile.close();
	cout<<"the output txt has been written"<<endl;
	cout<<endl;
	return OK;
}


