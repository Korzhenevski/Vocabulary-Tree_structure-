#include"Tree.h"

Tree::Tree()
{
	root = nullptr;
	height = 0;
	wordlen = 0;
}
Tree::~Tree()
{
	if (root != nullptr)
	{
		delete root;
	}
}
void Tree::Insert(Node *z)
{
	if (z->word != "")
	{
		int num = 0;
		Node *x = root;
		Node *y = nullptr;
		string word1, word2;
		word1 = z->word;
		word1[0] = tolower(word1[0]);
		while (x != nullptr)
		{
			y = x;
			word2 = x->word;
			word2[0] = tolower(word2[0]);
			if (word1 < word2)
				x = x->left;
			else
				x = x->right;
			num++;
		}
		if (y == nullptr)
		{
			z->depth = 0;
			root = z;
		}
		else
		{
			z->depth = num;
			word2 = y->word;
			word2[0] = tolower(word2[0]);
			if (word1 < word2)
				y->left = z;
			else y->right = z;
			z->p = y;
		}
		if (num > height)
			height = num;
		if (word1.length() > wordlen)
			wordlen = word1.length();
	}
}
void Tree::Inorder(Node *x)
{
	if (x != nullptr)
	{
		Inorder(x->left);
		cout << x->word << endl;
		Inorder(x->right);
	}
}
int Tree::GetHeight()
{
	return height;
}
void Tree::PrintHor(Node *node, int x, int y, int n, HANDLE out_handle)
{
	if (node != nullptr)
	{
		n /= 2;
		COORD c = { x, y };
		SetConsoleCursorPosition(out_handle, c);
		cout << node->word;
		PrintHor(node->left, x + wordlen, y+n, n, out_handle);
		PrintHor(node->right, x + wordlen, y-n, n, out_handle);
	}
}
Node* Tree::Search(string str)
{
	Node *x = root;
	string word1 = x->word;
	word1[0] = tolower(word1[0]);
	while (x!=nullptr && word1!=str)
	{
		if (str < word1)
			x = x->left;
		else
			x = x->right;
		if (x != nullptr)
		{
			word1 = x->word;
			word1[0] = tolower(word1[0]);
		}
	}
	return x;
}
Node* Tree::Minimum(Node *x)
{
	while (x->left != nullptr)
		x = x->left;
	return x;
}
Node* Tree::Successor(Node *x)
{
	if (x->right != nullptr)
		return Minimum(x->right);
	Node *y = x->p;
	while (y != nullptr && x == y->right)
	{ 
		x = y;
		y = y->p;
	}
	return y;
}
void Tree::Delete(Node *&z)
{
	Node *y, *x;
	if (z->left == nullptr || z->right == nullptr)
		y = z;
	else
		y = Successor(z);
	if (y->left != nullptr)
		x = y->left;
	else
		x = y->right;
	if (x != nullptr)
		x->p = y->p;
	if (y->p == nullptr)
		root = x;
	else if (y == y->p->left)
		y->p->left = x;
	else y->p->right = x;
	InorderDecDepth(x);
	if (y != z)
		z->word = y->word;
	y->left = y->right = nullptr;
	delete y;
	height = SetHeight(root);
}
int Tree::SetHeight(Node *x)
{
	if (x == nullptr)
		return 0;
	int a, b, c;
	a = SetHeight(x->left);
	b = SetHeight(x->right);
	c = x->depth;
	if (a < b) a = b;
	return	(a > c) ? a : c;
}	
void Tree::InorderDecDepth(Node *x)
{
	if (x != nullptr)
	{
		InorderDecDepth(x->left);
		x->depth--;
		InorderDecDepth(x->right);
	}
}

void PrintTreeHor(Tree *tree, HANDLE out_handle)
{
	system("cls");
	if (tree->root == nullptr)
		cout << "Словник порожній.\n";
	else
	{
		cout << "Словник у вигляді дерева:\n";
		int y = pow(2, tree->GetHeight() + 1);
		tree->PrintHor(tree->root, 0, (y - 1) / 2 + 2, y / 2, out_handle);
		COORD c = { 0, y+2 };
		SetConsoleCursorPosition(out_handle, c);
	}
}
void Print(Tree *tree)
{
	system("cls");
	cout << "Словник: \n\n";
	tree->Inorder(tree->root);
	cout << endl;
}
void Search(Tree *tree, string path)
{
	LARGE_INTEGER treetime1, treetime2, filetime1, filetime2;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	string str, str2;
	cout << "Введіть слово, яке ви шукаєте: ";
	cin >> str;
	cout << endl << endl;
	str2 = str;
	str2[0] = tolower(str2[0]);
	QueryPerformanceCounter(&treetime1);
	Node *x = tree->Search(str2);
	QueryPerformanceCounter(&treetime2);
	ifstream in(path);
	bool success = 0;
	string word;
	QueryPerformanceCounter(&filetime1);
	while (!in.eof())
	{
		getline(in, word);
		word[0] = tolower(word[0]);
		if (word == str2)
		{
			success = 1;
			break;
		}
	}
	QueryPerformanceCounter(&filetime2);
	in.close();
	cout << "Час пошуку у дереві: " << (treetime2.QuadPart - treetime1.QuadPart)*1000.0 / frequency.QuadPart << endl << "Час пошуку у файлі: " << (filetime2.QuadPart - filetime1.QuadPart)*1000.0 / frequency.QuadPart << endl
		<< "Результат: ";
	if (success && x != nullptr)
		cout << "Дане слово є у словнику.\n\n";
	else
	{
		char ans;
		cout << "Дане слово відсутнє. Бажаєте його додати?(Так - '1'/ Ні - '0')\n";
		do
		{
			cin >> ans;
			if (ans == '1')
			{
				x = new Node(str);
				tree->Insert(x);
				ofstream out(path, ios::app);
				out << "\n" << str;
				out.close();
			}
			if (ans != '1' && ans != '0')
				cout << "Будь ласка, зробіть свій вибір.\n";
		} while (ans != '1' && ans != '0');
	}
}
void Insert(Tree *tree, string path)
{
	string str;
	cout << "Введіть слово, яке Ви хочете додати: ";
	cin >> str;
	cout << endl << endl;
	Node *x = tree->Search(str);
	if (x != nullptr)
		cout << "Дане слово вже є у словнику.\n\n";
	else
	{
		x = new Node(str);
		tree->Insert(x);
		ofstream out(path, ios::app);
		out << "\n" << str;
		out.close();
	}
}
void Delete(Tree *tree, string path)
{
	string str;
	cout << "Введіть слово, яке Ви хочете видалити: ";
	cin >> str;
	cout << endl << endl;
	Node *x = tree->Search(str);
	if (x == nullptr)
		cout << "Даного слова немає у словнику.\n\n";
	else
	{
		if (x->p == nullptr)
			cout << 1;
		tree->Delete(x);
		fstream file(path);
		string text, output = "";
		while (!file.eof())
		{
			getline(file, text);
			if (text != str)
			{
				output += text + "\n";
			}
		}
		file.close();
		file.open("D:\\Tree.txt", ios::out);
		output.resize(output.size() - 1);
		file << output;
		file.close();
	}
}