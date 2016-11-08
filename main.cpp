#include"Tree.h"

int main()
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(out_handle, &csbiInfo);
	COORD maxWindow = GetLargestConsoleWindowSize(out_handle);// размер самого большого возможного консольного окна
	COORD window = { maxWindow.X, csbiInfo.dwSize.Y }; 
	SMALL_RECT srctWindow = { 0, 0, maxWindow.X - 1, maxWindow.Y-1};
	SMALL_RECT minWindow = { 0, 0, 0, 0 };
	SetConsoleWindowInfo(out_handle, true, &minWindow);
	SetConsoleScreenBufferSize(out_handle, window);
	SetConsoleWindowInfo(out_handle, true, &srctWindow);
	HANDLE hCon = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (hCon != INVALID_HANDLE_VALUE) {
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = 14;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = 400;
		wcscpy_s(cfi.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(hCon, FALSE, &cfi);
	}
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Tree *tree = new Tree;
	string word;
	Node *x;
	string path = "Tree.txt";
	ifstream in(path);
	int n = 0;
	if (in.is_open())
	{
		while (!in.eof())
		{
			getline(in, word);
			if (word == "") continue;
			x = new Node(word);
			tree->Insert(x);
		}
	}
	in.close();
	char ans;
	do
	{
		cout << "Файл зі словами має розташування: D:\\Tree.txt.\n\n"
			<< "Оберіть подальшу дію:\n" << "1.Вивести слова на екран у вигляді дерева\n" << "2.Вивести слова на екран в алфавітному порядку\n"
			<< "3.Знайти слово у словнику\n" << "4.Додати слово до словника\n" << "5.Видалити слово зі словника\n"
			<< "Для виходу натисніть 0.\n" << "Ваш вибір: ";
		cin >> ans;
		cin.clear();
		cin.sync();
		switch (ans)
		{
		case'1': PrintTreeHor(tree, out_handle); break;
		case'2': Print(tree); break;
		case'3': Search(tree, path); break;
		case'4': Insert(tree, path); break;
		case'5': Delete(tree, path); break;
		default: break;
		}
		if (ans != '1' && ans != '2' && ans != '3' && ans != '4' && ans != '5' && ans != '0')
			cout << "Будь ласка, зробіть свій вибір." << endl;
		if (ans == '0')
		{
			cout << "Для виходу повторно введіть 0. Для продовження роботи введіть будь-який інший символ.\n";
			cin >> ans;
			cin.clear();
			cin.sync();
		}
	} while (ans != '0');
	delete tree;
	cout << "\n\nСеанс завершений. Дякую за роботу. Для виходу натисніть ENTER.\n";
	cin.sync();
	cin.get();
	return 0;
}