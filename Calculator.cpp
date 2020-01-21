#include <iostream>
#define print std::cout
using std::endl;
using std::string;

int length(string * array)
{
    return *(&array + 1) - array;
}

void printArray(string * array, int len)
{
    for (int i = 0; i < len; i++)
    {
        print << array[i] << " ";
    }
    print << endl;
}

void split(string raw, string * out)
{
    string word = "";
    int counter = 0;
    for (int i = 0; i < raw.length(); i++)
    {
        if (raw[i] != ' ')
        {
            word += raw[i];
        }
        else
        {
            out[counter++] = word;
            word = "";
        }
        if (i == raw.length()-1) out[counter++] = word;
    }
}

void setOperators(string * input, int len)
{
    for(int i = 0; i < len; i++)
    {
        if (input[i] == "+")
            input[i] = "SUM";
        if (input[i] == "-")
            input[i] = "SUB";
    }
}

void calculate(string * input, int len)
{
    int result = 0;
    int op_type = 0;
    print << "len: " << len << endl;
    for (int i = 0; i < len; i++)
    {
        if (input[i] == "SUM")
        {
            op_type = 0;
            continue;
        }
        else if (input[i] == "SUB")
        {
            op_type = 1;
            continue;
        }
        else
        switch(op_type)
        {
            case 0: //+
            {
                print << "SUM: " << std::stoi(input[i]) << endl;
                result += std::stoi(input[i]);
                break;
            }
            case 1: //-
            {
                print << "SUB: " << std::stoi(input[i]) << endl;
                result -= std::stoi(input[i]);
                break;
            }
            default:
                break;
        }
    }
    print << "RES: " << result << endl;
}

int main(int argc, const char * argv[])
{
    string t = "";
    print << "Num of elements: ";
    int len = 0;
    std::cin >> len;
    len = len * 2 - 1;
    string n[len];
    print << endl << "Expression: " <<endl;
    std::cin.ignore();
    std::getline(std::cin, t);
    split(t, n);
    printArray(n, len);
    setOperators(n, len);
    printArray(n, len);
    calculate(n, len);
    return EXIT_SUCCESS;
}
