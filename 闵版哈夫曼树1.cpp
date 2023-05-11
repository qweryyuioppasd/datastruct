/*
Descripttion: 
Version: 1.0
Author: ͿȻ 18�ƿ�3�� 
Date: 2021-05-31 9:00:00
*/

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std; 

#define MaxSize 1024  // �����ļ������� 
#define OK 1
#define ERROR 0
typedef int Status;

typedef struct wordcnt{  // ͳ���ַ��Ͷ�Ӧ�Ĵ��� 
	char ch;
	int cnt = 0;
}Count;

typedef struct NumCount{  // ͳ�ƴ������ⲿ��װ 
	Count count[MaxSize];
	int length = 0;
}NumCount;

typedef struct HTree{  // ���������ṹ 
	char data; 
	int weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree; 

typedef struct HCode{ // ����ṹ 
	char data;
	char* str; 
}*HuffmanCode;


Status ReadData(char *source);  // �����ļ� 
Status WordCount(char *data,NumCount *paraCnt); // ͳ�ƴ��� 
Status Show(NumCount *paraCnt);   // չʾ���� 
Status CreateHuffmanTree(HuffmanTree &HT,int length,NumCount cntarray);  // ������������ 
Status select(HuffmanTree HT,int top,int *s1,int *s2);  // ѡ��Ȩ����С�������ڵ� 
Status CreateHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int length);  // �������������� 
Status Encode(char *data,HuffmanCode HC,int length);  // ��������ļ����룬д��txt�ļ� 
Status Decode(HuffmanTree HT,int length);  //��������ļ������� 

int main(int argc, char** argv) {
	char data[MaxSize];  
	NumCount Cntarray;
	ReadData(data);  // �������� 
	WordCount(data,&Cntarray);  // ͳ�ƴ��� 
//	Show(&Cntarray); //���Բ鿴ÿ�����ʳ��ֵĶ�Ӧ���� 
	HuffmanTree tree;
	CreateHuffmanTree(tree,Cntarray.length,Cntarray);  // ���� 
	HuffmanCode code;  
	CreateHuffmanCode(tree,code,Cntarray.length);  // �������� 
	Encode(data,code,Cntarray.length);  // ���ɱ����ļ� 
	Decode(tree,Cntarray.length);  // ���� 
	cout<<"Please view the generated TXT file to check the result"<<endl; 
	return 0;
}

Status ReadData(char *source)
{
	//���ļ��������� 
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
	int flag;// ��ʶ�Ƿ��Ѿ���¼ 
	int len = strlen(data);
	for(int i = 0;i < len;++i)
	{
		flag = 0;
		for(int j = 0;j < paraCnt->length;++j)
		{
			if(paraCnt->count[j].ch == data[i]) // �����м�¼��ֱ��++ 
			{
				++paraCnt->count[j].cnt;
				flag = 1;
				break;
			}
			
		}
		if(!flag) // û�м�¼�������� 
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
	int m = length*2-1;  // û�ж�Ϊ1�Ľڵ㣬���ܽ����2*Ҷ�ӽڵ���-1�� 
	HT = new HTNode[m+1];
	for(int i = 1;i <= m;++i)  // ��ʼ�� 
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
		select(HT,i-1,&s1,&s2);  // ��ǰ��ķ�Χ��ѡ��Ȩ����С�������ڵ� 
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;  // �õ�һ���½ڵ� 
	}
	return OK;
}

Status select(HuffmanTree HT,int top,int *s1,int *s2)
{
	int min = INT_MAX;
	for(int i = 1;i <= top;++i)  // ѡ��û��˫�׵Ľڵ��У�Ȩ����С�Ľڵ� 
	{
		if(HT[i].weight < min && HT[i].parent == 0)
		{
			min = HT[i].weight;
			*s1 = i;
		}
	}
	
	min = INT_MAX;
	for(int i = 1;i <= top;++i)  // ѡ��û��˫�׵Ľڵ��У�Ȩ�ش�С�Ľڵ� 
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
	char *cd = new char[length];  // �洢�������ʱ�ռ� 
	cd[length-1] = '\0';  // ����֮�����strcpy���� 
	int c,f,start;
	for(int i = 1;i <= length;++i)
	{
		start = length-1;  // start��ʾ��������ʱ�ռ��ڵ���ʼ�±꣬�����Ǵ�Ҷ�ӽڵ���ݣ������Ǵ����ʼ 
		c = i;
		f = HT[c].parent;
		while(f != 0)
		{
			--start;  // �����ǻ��ݣ����Դ���ʱ�ռ��������ؼ� 
			if(HT[f].lchild == c)
				cd[start] = '0';
			else 
				cd[start] = '1';
			c = f;
			f = HT[c].parent;
		}
		HC[i].str = new char[length-start];  // ���ʵ��ʹ�õı���ռ��С��length-start 
		HC[i].data = HT[i].data;
		strcpy(HC[i].str,&cd[start]);  // ��ʵ����ʼ��ַ��ʼ������������ṹ�� 
	}
	delete cd;
}

Status Encode(char *data,HuffmanCode HC,int length)
{
	ofstream outfile;
	outfile.open("code.txt");
	for(int i = 0;i < strlen(data);++i)  // ���ζ������ݣ����Ҷ�Ӧ�ı��룬д������ļ� 
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
	
	int root = 2*length-1;  // �Ӹ��ڵ㿪ʼ���� 
	for(int i = 0;i < strlen(codetxt);++i)
	{
		if(codetxt[i] == '0') root = HT[root].lchild;  //Ϊ0��ʾ������� 
		else if(codetxt[i] == '1') root = HT[root].rchild; //Ϊ1��ʾ���ұ��� 
		if(HT[root].lchild == 0 && HT[root].rchild == 0)  // ����Ѿ���Ҷ�ӽڵ㣬���������ļ��У�Ȼ�����»ص����ڵ� 
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


