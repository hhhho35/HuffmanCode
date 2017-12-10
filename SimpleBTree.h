#pragma once
struct TreeNode
{
	int weight;
	int par, lchild, rchild;

	TreeNode(){}
	TreeNode(int w, int p = 0, int l = 0, int r = 0)
	{
		weight = w, par = p, lchild = l, rchild = r;
	}
};

class SimpleBTree
{
protected:
	TreeNode* nodes;
	char* LeafChars;
	string* LeafCharCodes;
	int curPos;
	int num;

	void Select(int cur, int &r1, int& r2);
	void CreatHuffmanTree(char ch[], int w[], int n);
public:
	SimpleBTree();
	~SimpleBTree();
};

