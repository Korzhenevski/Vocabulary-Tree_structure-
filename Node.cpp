#include"Tree.h"

Node::Node()
{
	p = left = right = nullptr;
}

Node::Node(string str)
{
	p = left = right = nullptr;
	word = str;
}
Node::~Node()
{
	if (left != nullptr)
		delete left;
	if (right != nullptr)
		delete right;
}