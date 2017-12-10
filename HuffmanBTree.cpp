// HuffmanBTree.cpp : 定义控制台应用程序的入口点。
//注意STL容器的迭代器操作，避免越界
//new char[x]也不会只创建x个位置，仍需增加结束的特殊字符；C++不能直接char[x]，只能是确定的数
//char*和string可以直接相互赋值
//txt文件好像不能判断换行符'\n'

#include "stdafx.h"
#include"HuffmanTree.h"

char* letter(char* input);//返回一段字符串中不重复的字母
int* letterWeight(char* input);//返回一段字符串中不重复的字母对应的数量
void outputLetter(char* s);//输出，要求输入为进行char* letter()后的数组
void outputWeight(int* g);//同上
int letterNum(char* input);//统计一段字符串中的不同字母个数
void Encode();//控制台编码
void Decode();//解码
void ReadMe();//提示
void save(char* l,string* lw,int ln);
int main()
{
	ReadMe();
	char c1;
	do
	{
		cout << "请输入指令：";
		cin >> c1;
		while (c1 != 'd'&&c1 != 'e'&&c1 != 'x')
		{
			cout << "请输入正确的指令：";
			cin >> c1;
		}
		switch (c1)
		{
		case'd':
			Decode();
			break;
		case'e':
			Encode();
			break;
		default:
			break;
		}
	} while ((c1) != 'x');
    return 0;
}

char * letter(char * input)
{
	int a[26] = { 0 }, i = 0, j = 0;
	while (input[j]!='\0')
	{
		i = input[j];
		a[i - 97]++;
		j++;
	}
	char* r = new char[27];
	j = 0;
	for ( i = 0; i < 26; i++)
	{
		if (a[i] > 0)
		{
			r[j] = i + 97;
			j++;
		}
	}
	r[j] = 0;
	return r;
}

int * letterWeight(char * input)
{
	int a[26] = { 0 }, i = 0, j = 0;
	while (input[j] != '\0')
	{
		i = input[j];
		a[i - 97]++;
		j++;
	}
	int* r = new int[27];
	j = 0;
	for (i = 0; i < 26; i++)
	{
		if (a[i] > 0)
		{
			r[j] = a[i];
			j++;
		}
	}
	r[j] = '\0';
	return r;
}

void outputLetter(char * s)
{
	cout << "字母串中出现的字母有：" << endl;
	for (int i = 0; i < 27; i++)
	{
		if (s[i] != '\0')
		{
			cout << s[i] << " ";
		}
		else
		{
			cout << endl;
			break;
		}
	}
}

void outputWeight(int * g)
{
	cout << "它们出现的次数分别是：" << endl;
	for (int i = 0; i < 27; i++)
	{
		if (g[i] != 0)
		{
			cout << g[i] << " ";
		}
		else
		{
			cout << endl;
			break;
		}
	}
}

int letterNum(char * input)
{
	int a[26] = { 0 }, i = 0, j = 0;
	while (input[j] != '\0')
	{
		i = input[j];
		a[i - 97]++;
		j++;
	}
	int num = 0;
	j = 0;
	for (i = 0; i < 26; i++)
	{
		if (a[i] > 0)
		{
			num++;
		}
	}
	return num;
}

void Encode()
{
	cout << "请输入文件名" << endl;
	char filename[100] = { 0 };
	cin >> filename;
	fstream f;
	f.open(filename, ios::in);
	while (f.fail())
	{
		cout << "打开文件失败" << endl;
		cout << "请输入正确的已存在的文件名" << endl;
		cin >> filename;
		f.open(filename, ios::in);
	}
	cout << "文件打开成功" << endl;
	char *s = new char[1000];
	int i = 0;
	while (!f.eof())
	{
		f >> s[i];
		i++;
	}
	char* s2 = letter(s);
	int* g = letterWeight(s);
	int num = letterNum(s);
	HuffmanTree<char, int>* tree = new HuffmanTree<char, int>(s2, g, num);
	outputLetter(s2);
	outputWeight(g);
	for (i = 0; i < num; i++)
	{
		cout << s2[i] << ": ";
		string str=tree->Encode(s2[i]);
		for (int i = 0; i < str.size(); i++)
		{
			cout << str[i];
		}
		cout << endl;
	}
	f.close();
	save(s2,tree->LeafCharCodes,num);
	tree->~HuffmanTree();
	cout << endl;
}

void Decode()
{
	cout << "请输入文件名" << endl;
	char filename[100] = { 0 };
	cin >> filename;
	fstream f;
	f.open(filename, ios::in);
	while (f.fail())
	{
		cout << "打开文件失败" << endl;
		cout << "请输入正确的已存在的文件名" << endl;
		cin >> filename;
		f.open(filename, ios::in);
	}
	cout << "文件打开成功" << endl;
	char tmp[26] = { 0 };
	char tmp2[1000] = { 0 };
	char c = '0';
	int num = 0, num2 = 0;
	while (!f.eof())
	{
		f >> c;
		if (c!='*')
		{
			tmp[num] = c;
			num++;
		}
		else
		{
			break;
		}
	}
	char* letter = new char[num+1];
	int* weight = new int[num+1];
	for (int i = 0; i < num; i++)
	{
		letter[i] = tmp[i];
	}
	letter[num] = '\0';
	for (int i = 0; i < num; i++)
	{
		f >> weight[i];
	}
	weight[num] = 0;
	while (!f.eof())
	{
		f >> tmp2[num2];
		num2++;
	}
	char* code = new char[num2 + 1];
	char* out = new char[num2 + 1];
	int j = 0;
	for (int i = 0; i < num2; i++)
	{
		code[i] = tmp2[i];
	}
	HuffmanTree<char, int>* tree = new HuffmanTree<char, int>(letter, weight, num);
	cout << "原来的编码为：" << endl;
	list<char> charList=tree->Decode(code);						
	list<char>::iterator it = charList.begin();
	for (it; it != charList.end(); it++)
	{
		cout << *it;
		out[j] = *it;
		j++;
	}
	cout << endl;
	f.close();
	save(out,NULL,j);
	tree->~HuffmanTree();
	cout << endl;
}

void ReadMe()
{
	cout << "本程序只用于已有文件操作，请在文件中修改数据" << endl;
	cout << "提供文件：decode.txt, encode.txt, encode2.txt" << endl;
	cout << "输入d进行解码，输入e进行编码，输入x退出" << endl;
	cout << endl;
}

void save(char* l,string* lw, int ln)
{
	cout << "输入s保存结果，输入其他键返回上一级" << endl;
	char c;
	cin >> c;
	if (c != 's')
	{
		return;
	}
	else
	{
		char name[80] = { 0 };
		cout << "请输入目标文件名，若不存在将自动创建 ";
		cin >> name;
		fstream f;
		f.open(name, ios::out);
		while (f.fail())
		{
			cout << "打开文件失败" << endl;
			cout << "请输入正确的文件名 ";
			cin >> name;
			f.open(name, ios::out);
		}
		if (lw == NULL)
		{
			for (int i = 0; i < ln; i++)
			{
				f << l[i];
			}
		}
		else
		{
			for (int i = 0; i < ln; i++)
			{
				f << l[i] << " " ;
				for (int j = 0; j < lw[i+1].size(); j++)
				{
					f << lw[i+1][j];
				}
				f << endl;
			}
		}
		cout << "保存成功" << endl;
		f.close();
	}
}
