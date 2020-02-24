#include <iostream>
using namespace std;

template <typename T>
void Dump(T n, int r)
{
    T mask;
    switch (r)
    {
        case 2:
        {
            int size(8 * sizeof(T) - 1);
            switch (sizeof(T))
            {
                case 1 :                        // char
                    mask = 0100;
                    break;
                    
                case 2 :                        // short int
                    mask = 040000;
                    break;
                    
                case 4 :                        // int or long int
                    mask = 010000000000;
                    break;
            }
            cout << (n < 0 ? '1' : '0');        // 7 or 15 or 31
            for (int i = 0; i < size; ++i)
            {
                cout << (n & mask ? '1' : '0');    // 6 - 0 or 14 - 0 or 30 - 0
                mask >>= 1;
            }
            cout << endl;
            break;
        }
        case 8:
        {
            int size((8 * sizeof(T)) / 3);
            int base(3 * ((8 * sizeof(T) / 3) - 1));
            switch (sizeof(T))
            {
                case 1 :                                    // char
                    mask = 070;
                    cout << char(((n >> 6) & 03) + 48);        // 2
                    break;
                    
                case 2 :                                    // short int
                    mask = 070000;
                    cout << (n < 0 ? '1' : '0');            // 5
                    break;
                    
                case 4 :                                    // int or long int
                    mask = 07000000000;
                    cout << char(((n >> 30) & 03) + 48);    // 10
                    break;
            }
            for (int i = 0; i < size; ++i, mask >>= 3)
                cout << char(((n & mask) >> base - i * 3) + 48);    // 1 - 0 or 4 - 0 or 9 - 0
            cout << endl;
            break;
        }
        case 16:
        {
            int size(2 * sizeof(T) - 1);
            int base(8 * (sizeof(T) - 1));
            int digit((n >> (8 * sizeof(T) - 4)) & 0xf);
            switch (sizeof(T))
            {
                case 1 :                                    // char
                    mask = 0xf;
                    break;
                    
                case 2 :                                    // short int
                    mask = 0xf00;
                    break;
                    
                case 4 :                                    // int or long int
                    mask = 0xf000000;
                    break;
            }
            cout << (digit > 9 ? char(digit + 87) : char(digit + 48));        // 1 or 3 or 7
            for (int i = 0; i < size; ++i, mask >>= 4)
            {
                digit = (n & mask) >> base - i * 4;
                cout << (digit > 9 ? char(digit + 87) : char(digit + 48));    // 0 or 2 - 0 or 6 - 0
            }
            cout << endl;
            break;
        }
        default:
            cout << "Error: wrong radix value. '2/8/16' expected, got " << r << endl;
            break;
    }
}

int main()
{
    int n = 0, r = 0;
    short int sn = 0;
    char cn = 0;
    int input = 0;
    do
    {
        cout << "0 for int\n1 for short int\n2 for char\nType: ";
        cin >> input;
        if (input == 0 || input == 1 || input == 2) break;
    }
    while (true);
    do
    {
        cout << "Number: ";
        switch (input)
        {
            case 0: //int
                cin >> n;
                break;
            case 1: //short int
                cin >> sn;
                break;
            case 2: //char
                cin >> cn;
                break;
            default:
                cout << "Wrong input." << endl;
                break;
        }
        if (cin.good())
        {
            cout << "Radix: ";
            cin >> r;
            if (cin.good())
            {
                break;
            }
        }
        else
        {
            cout << "Invalid data!\n";
            cin.clear();
            while(cin.get() != '\n');
        }
    }
    while(true);
    switch(input)
    {
        case 0: //int
            Dump<int>(n, r);
            break;
        case 1: //short int
            Dump<short int>(sn, r);
            break;
        case 2: //char
            Dump<char>(cn, r);
            break;
        default:
            cout << "Wrong input." << endl;
            break;
    }
    return 0;
}
