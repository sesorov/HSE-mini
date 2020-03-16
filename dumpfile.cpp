#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
string Dump(T n) //binary
{
	T mask;
	string dump = "";
	int size(8 * sizeof(T) - 1);
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
	dump += (n < 0 ? '1' : '0');        // 7 or 15 or 31
	for (int i = 0; i < size; ++i)
	{
		dump += (n & mask ? '1' : '0');    // 6 - 0 or 14 - 0 or 30 - 0
		mask >>= 1;
	}
	return dump + '\n';
}

void write(string content, string path)
{
	ofstream out;
	out.open(path);
	ifstream inFile(path);
	if (!inFile)
	{
		cout << "Invalid opening file!\n";
		cout << "Directory: " + path;
	}
	else
		out << content;
	out.close();
	cout << "Your data has been successfully written to " + path;
}

string read() 
{
	return "";
}

template<class T>
T get(std::istream& is) 
{
	T result;
	is >> result;
	return result;
}

int main()
{
	int input = 0, n = 0, sn = 0, cn = 0;
	string dump = "", path = "text.txt";
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
			dump = Dump<int>(n);
			break;
		case 1: //short int
			cin >> sn;
			dump = Dump<short int>(sn);
			break;
		case 2: //char
			cin >> cn;
			dump = Dump<char>(cn);
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
	cout << "Would you like to change file path? (Y/N): ";
	if (get<string>(cin) == "Y")
	{
		cout << "New path (ending with filename.txt): ";
		cin >> path;
	}
	else if (get<string>(cin) != "N") cout << "Wrong answer. PATH set to standard.";
	write(dump, path);
	return EXIT_SUCCESS;
}
