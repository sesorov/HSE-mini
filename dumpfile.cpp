#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
void Dump(T n, string path) //binary
{
	T mask;
	ofstream file;
	file.open(path, ios::out);
	if (!file)
	{
		cout << "Invalid opening file!" << '\n';
		return;
	}
	int size(8 * sizeof(T));
	switch (sizeof(T))
	{
		case 1:                        // char
			mask = 0100;
			break;

		case 2:                        // short int
			mask = 040000;
			break;

		case 4:                        // int or long int
			mask = 010000000000;
			break;
	}
	file << (n < 0 ? '1' : '0');        // 7 or 15 or 31
	for (int i = 1; i < size; ++i)
	{
		file << (n & mask ? '1' : '0');    // 6 - 0 or 14 - 0 or 30 - 0
		mask >>= 1;
	}
	file << '\n';
	file.close();
}

template <typename T>
const char* read(string path) 
{
	char* input = new char[sizeof(T) * 8 + 1];
	ifstream in;
	in.open(path, ios::in);
	if (!in)
	{
		cout << "Invalid opening file!" << '\n';
		return "ERROR READING FILE";
	}
	else in.getline(input, sizeof(T) * 8 + 1);
	in.close();
	return input;
}

template<class T>
T get(istream& is) //для ввода пользователя без его сохранения (мгновенное использование)
{
	T result;
	is >> result;
	return result;
}

int main()
{
	int input = 0, n = 0, sn = 0, cn = 0;
	string dump = "", path = "text.txt";

	cout << "Would you like to change file path (standard path refers to the folder with this program)? (Y/N): ";
	if (get<char>(cin) == 'Y')
	{
		cout << "New path (ending with filename.txt): ";
		cin >> path;
	}
	else cout << "PATH set to standard.\n";
	do
	{
		cout << "0 for int\n1 for short int\n2 for char\nType: ";
		cin >> input;
		if (cin.good() && (input == 0 || input == 1 || input == 2)) break;
		else
		{
			cout << "Invalid data!\n";
			cin.clear();
			while (cin.get() != '\n');
		}
	} while (true);
	do
	{
		cout << "Number: ";
		switch (input)
		{
		case 0: //int
			cin >> n;
			Dump<int>(n, path);
			cout << read<int>(path);
			break;
		case 1: //short int
			cin >> sn;
			Dump<short int>(sn, path);
			cout << read<short int>(path);
			break;
		case 2: //char
			cin >> cn;
			Dump<char>(cn, path);
			cout << read<char>(path);
			break;
		default:
			cout << "Wrong input." << endl;
			break;
		}
		if (cin.good()) break;
		else
		{
			cout << "Invalid data!\n";
			cin.clear();
			while (cin.get() != '\n');
		}
	} while (true);
	return EXIT_SUCCESS;
}
