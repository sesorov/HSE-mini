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
	return dump;
}

/*void binaryDump(short int n, int* p)
{
	short int mask(040000);
	p[15] = (n < 0 ? 1 : 0);
	for (int i = 0; i < 15; ++i, mask >>= 1)
		p[15 - i - 1] = n & mask ? 1 : 0; // 14 - 0
}

template <typename T>
string fpDump(T* pFloat) 
{
	int *p = new int[8 * sizeof(T)];
	short int* pShort = reinterpret_cast<short int*>(pFloat);
	int size(sizeof(T) / sizeof(short int));
	int index = 0;
	for (int i = 0; i < size; ++i)
	{
		index = size - i - 1;
		binaryDump(pShort[index], p + 16 * index);
	}
	string dump = "";
	for (int i = 0; i < 8 * sizeof(T); ++i) {
		dump += to_string(p[8 * sizeof(T) - i - 1]);
	}
	return dump;
}

template <typename T>
void print(int* p)
{
	int size(8 * sizeof(T));
	for (int i = 0; i < size; ++i) // 31 - 0 or 63 - 0
		cout << p[size - i - 1];
	cout << endl;
}*/

int main()
{
	//char* p = getenv("USERPROFILE");
	ofstream out;
	out.open("text.txt");
	ifstream inFile("text.txt");
	if (!inFile)
	{
		cout << "Invalid opening file!\n";
		return EXIT_FAILURE;
	}
	else
		out << "test" << endl;
	out.close();
	return EXIT_SUCCESS;
}
