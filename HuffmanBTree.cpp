// HuffmanBTree.cpp : �������̨Ӧ�ó������ڵ㡣
//ע��STL�����ĵ���������������Խ��
//new char[x]Ҳ����ֻ����x��λ�ã��������ӽ����������ַ���C++����ֱ��char[x]��ֻ����ȷ������
//char*��string����ֱ���໥��ֵ
//txt�ļ��������жϻ��з�'\n'

#include "stdafx.h"
#include"HuffmanTree.h"

char* letter(char* input);//����һ���ַ����в��ظ�����ĸ
int* letterWeight(char* input);//����һ���ַ����в��ظ�����ĸ��Ӧ������
void outputLetter(char* s);//�����Ҫ������Ϊ����char* letter()�������
void outputWeight(int* g);//ͬ��
int letterNum(char* input);//ͳ��һ���ַ����еĲ�ͬ��ĸ����
void Encode();//����̨����
void Decode();//����
void ReadMe();//��ʾ
void save(char* l,string* lw,int ln);
int main()
{
	ReadMe();
	char c1;
	do
	{
		cout << "������ָ�";
		cin >> c1;
		while (c1 != 'd'&&c1 != 'e'&&c1 != 'x')
		{
			cout << "��������ȷ��ָ�";
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
	cout << "��ĸ���г��ֵ���ĸ�У�" << endl;
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
	cout << "���ǳ��ֵĴ����ֱ��ǣ�" << endl;
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
	cout << "�������ļ���" << endl;
	char filename[100] = { 0 };
	cin >> filename;
	fstream f;
	f.open(filename, ios::in);
	while (f.fail())
	{
		cout << "���ļ�ʧ��" << endl;
		cout << "��������ȷ���Ѵ��ڵ��ļ���" << endl;
		cin >> filename;
		f.open(filename, ios::in);
	}
	cout << "�ļ��򿪳ɹ�" << endl;
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
	cout << "�������ļ���" << endl;
	char filename[100] = { 0 };
	cin >> filename;
	fstream f;
	f.open(filename, ios::in);
	while (f.fail())
	{
		cout << "���ļ�ʧ��" << endl;
		cout << "��������ȷ���Ѵ��ڵ��ļ���" << endl;
		cin >> filename;
		f.open(filename, ios::in);
	}
	cout << "�ļ��򿪳ɹ�" << endl;
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
	cout << "ԭ���ı���Ϊ��" << endl;
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
	cout << "������ֻ���������ļ������������ļ����޸�����" << endl;
	cout << "�ṩ�ļ���decode.txt, encode.txt, encode2.txt" << endl;
	cout << "����d���н��룬����e���б��룬����x�˳�" << endl;
	cout << endl;
}

void save(char* l,string* lw, int ln)
{
	cout << "����s������������������������һ��" << endl;
	char c;
	cin >> c;
	if (c != 's')
	{
		return;
	}
	else
	{
		char name[80] = { 0 };
		cout << "������Ŀ���ļ������������ڽ��Զ����� ";
		cin >> name;
		fstream f;
		f.open(name, ios::out);
		while (f.fail())
		{
			cout << "���ļ�ʧ��" << endl;
			cout << "��������ȷ���ļ��� ";
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
		cout << "����ɹ�" << endl;
		f.close();
	}
}
