#include <iostream>
#include <math.h>
using namespace std;

void binaryDump(short int n, int* p)
{
    short int mask(040000);
    p[15] = (n < 0 ? 1 : 0);
    for (int i = 0; i < 15; ++i, mask >>= 1)
        p[15-i-1] = n & mask ? 1 : 0; // 14 - 0
}

template <typename T>
void print(int* p)
{
    int size(8 * sizeof(T));
    for (int i = 0; i < size; ++i) // 31 - 0 or 63 - 0
        cout << p[size-i-1];
    cout << endl;
}

template <typename T>
void printFields(int* p)
{
    int size(8 * sizeof(T));
    cout << (p[size-1] < 0 ? 1 : 0); // 31 or 63
    switch (sizeof(T)) {
        case 4 :
            cout << ' ';
            for (int i = 0; i < 8; ++i) // 30 - 23
                cout << p[size-1-i-1];
            cout << ' ';
            for (int i = 0; i < 23; ++i) // 22 - 0
                cout << p[size-8-i-2];
            break;
        case 8 :
            cout << ' ';
            for (int i = 0; i < 11; ++i) // 62 - 52
                cout << p[size-1-i-1];
            cout << ' ';
            for (int i = 0; i < 52; ++i) // 51 - 0
                cout << p[size-11-i-2];
            break;
    }
    cout << endl;
}
template <typename T>
void pack(T* pFloat, int* p) {
    short int* pShort = reinterpret_cast<short int*>(pFloat);
    int size(sizeof(T) / sizeof(short int));
    int index = 0;
    for (int i = 0; i < size; ++i)
    {
        index = size - i - 1;
        binaryDump(pShort[index], p + 16 * index);
    }
    cout << endl;
}

template <typename T>
T unpack(int* p)
{
    T S = (p[sizeof(T) * 8 - 1] == 1 ? (-1) : 1), E = (sizeof(T) == 4 ? -127 : -1023), M = 1;
    switch (sizeof(T)) {
        case 4 :
        {
            for(int i = 23; i < 31; i++)
                E += (p[i] == 1 ? pow(2, i - 23) : 0);
            for(int i = 0; i < 23; i++)
                M += (p[i] == 1 ? pow(2, i - 23) : 0);
            break;
        }
        case 8 : {
            for(int i = 52; i < 63; i++)
                E += (p[i] == 1 ? pow(2, i - 52) : 0);
            for(int i = 0; i < 52; i++)
                M += (p[i] == 1 ? pow(2, i - 52) : 0);
            break;
        }
    }
    return S * M * pow(2, E);
}

int main()
{
    int* p;
    
    float f;
    do
    {
        cout << "Float number: ";
        cin >> f;
        if (cin.good())
            break;
        else
        {
            cout << "Invalid input. Please, try again.\n";
            cin.clear();
            while(cin.get() != '\n');
        }
    }
    while (1);
    p = new int[8*sizeof(float)];
    pack<float>(&f, p);
    print<float>(p);
    printFields<float>(p);
    cout << "Unpacked: " << unpack<float>(p) << endl;
    delete[] p;
    
    cout << endl;
    
    double d;
    do
    {
        cout << "Double number: ";
        cin >> d;
        if (cin.good())
            break;
        else
        {
            cout << "Invalid input. Please, try again.\n";
            cin.clear();
            while(cin.get() != '\n');
        }
    }
    while (1);
    p = new int[8*sizeof(double)];
    pack<double>(&d, p);
    print<double>(p);
    printFields<double>(p);
    cout << "Unpacked: " << unpack<double>(p) << endl;
    delete[] p;

    return 0;
}
