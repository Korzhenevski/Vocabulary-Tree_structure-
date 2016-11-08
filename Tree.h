#include<iostream>
#include<string>
#include <Windows.h>
#include<fstream>
#include<ctime>
using namespace std;

struct Node
{
	Node *left;
	Node *right;
	Node *p;
	int depth;
	string word;
	Node();
	~Node();
	Node(string);
};

struct Tree
{
	int height;
	Node* root;
	int wordlen;
	Tree();
	~Tree();
	void Insert(Node *);
	void Inorder(Node*);
	void InorderDecDepth(Node *);
	int GetHeight();
	void PrintHor(Node*, int, int, int, HANDLE);
	Node* Search(string);
	void Delete(Node *&);
	Node* Successor(Node*);
	Node* Minimum(Node*);
	int SetHeight(Node*);
};

void PrintTreeHor(Tree *, HANDLE);
void Print(Tree *);
void Search(Tree *, string);
void Insert(Tree *, string);
void Delete(Tree *, string);
