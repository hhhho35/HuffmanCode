#pragma once
template<class WeightType>
struct HuffmanTreeNode
{
	WeightType weight;
	unsigned int parent, leftChild, rightChild;

	HuffmanTreeNode();
	HuffmanTreeNode(WeightType w1, int p = 0, int l = 0, int r = 0);
};

template<class WeightType>
inline HuffmanTreeNode<WeightType>::HuffmanTreeNode()
{
	weight = 0, parent = 0, leftChild = 0, rightChild = 0;
}

template<class WeightType>
inline HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType w1, int p, int l, int r)
{
	weight = w1, parent = p, leftChild = l, rightChild = r;
}
