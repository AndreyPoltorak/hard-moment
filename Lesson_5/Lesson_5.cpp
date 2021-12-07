

#include <iostream>
#include <iterator>
#include <set>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <map>
#include <windows.h>

#include <locale>



using namespace std;

template <typename T>
void slova(T begin, T end)
{
	set<string> set{};
	set.insert(begin, end);
	for (const auto& s : set)
	{
		cout << s.c_str() << endl;
	}
}

void break_into_sentences()
{
	
	
	

	multimap<int,string> Text;

	
	std::string buffer{};
	std::string sentences{};
	std::cout << "Вводите текст: "
		<< "(по окончанию ввода введите пустую строку)" << std::endl;

	do {
		getline(std::cin, buffer);
		for ( const auto &ch :buffer) {
			// Добавление элемента в конец вектора
			sentences += ch;
			if (ch == '.' || ch == '!' || ch == '?')
			{
				Text.insert({ sentences.length(), sentences });
				sentences = {};
			}
		}
	} while (buffer != "");

	multimap<int, string>::reverse_iterator it;

	for (it = Text.rbegin(); it != Text.rend(); it++) {

		cout << "(" << it->first << " : "

			<< it->second << ")" << endl;

	}


}


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 
	cout << "vector:" << endl;
	vector<string> v{
		"sss",
		"ss",
		"sss",
		"ssss",
		"sss",
	};
	slova(v.begin(), v.end());
	cout << "list:" << endl;
	list<string> l{
		"sss",
		"ss",
		"sss",
		"ssss",
		"sss",
	};
	slova(l.begin(), l.end());

	
	break_into_sentences();



	return 0;
}

