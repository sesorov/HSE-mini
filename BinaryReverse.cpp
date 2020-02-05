#include <iostream>
#include <math.h>

template <size_t N>
int length(int (&array)[N])
{
    const size_t n = N;
    return n;
}
int BinarytoOctal(int binaryNum) {
    int octalNum = 0, decimalNum = 0, count = 0;
    
    while(binaryNum != 0) {
        decimalNum += (binaryNum % 10) * pow(2, count);
        ++count;
        binaryNum /= 10;
    }
    count = 1;
    while (decimalNum != 0) {
        octalNum += (decimalNum % 8) * count;
        decimalNum /= 8;
        count *= 10;
    }
    return octalNum;
}
int OctalToDecimal(int n)
{
    int num = n;
    int dec_value = 0;
    int base = 1;
    
    int temp = num;
    while (temp) 
    {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 8;
    }
    
    return dec_value;
}
int reversCode(int n)
{
    using namespace std;
    std::bitset<8> bitN_2 = n;
    std::string n_2s = bitN_2.to_string();
    for (int i = 1; i < n_2s.size(); i+=2)
    {
        //n_2s[i] = (n_2s[i]) ? '0' : '1';
        if (n_2s[i] == '0') n_2s[i] = '1';
        else n_2s[i] = '0';
    }
    std::cout << n_2s << std::endl;
    for (int i = 0; i < n_2s.size(); i++)
    {
        if (n_2s[i] == '0') n_2s[i] = '1';
        else n_2s[i] = '0';
    }
    //std::cout << n_2s << std::endl;
    int n_2 = BinarytoOctal(stoi(n_2s));
    n_2++;
    //cout << n_2 << endl;
    return OctalToDecimal(n_2);
}

int main()
{
    using namespace std;
    std::cout << reversCode(-17) << endl;
    return EXIT_SUCCESS;
}
