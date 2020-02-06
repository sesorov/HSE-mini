#include <iostream>
#include <math.h>
const int TO_8 = 0377;
const int REVERSE_EVEN = 0125;
const int REVERSE_ODD = 0252;
const int TO_32 = 037777777400;

int reverse(int number, bool type)
{
    number &= TO_8;
    number ^= (type ? REVERSE_ODD : REVERSE_EVEN);
    return number ^ TO_32;
}

int main()
{
    using namespace std;
    bool type = 0;
    int input = 0;
    cout << "Enter the number (-128 to 127): ";
    cin >> input;
    if (input > 128 || input < -127)
    {
        cout << "Please, check the input. It should be from -128 to 127." << endl;
        return EXIT_FAILURE;
    }
    cout << "Reverse even (type 0) or odd (type 1) positions: ";
    cin >> type;
    cout << "Reversed " << (type ? "odd bits: " : "even bits: ") << reverse(input, type) << endl;;
    return EXIT_SUCCESS;
}
