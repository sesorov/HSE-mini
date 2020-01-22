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

void calculate(string * input, int len)
{
    int result = 0;
    int op_type = 0;
    int temp_op_type = op_type;
    for (int i = 0; i < len; i++)
    {
        if (input[i] == "+")
        {
            temp_op_type = op_type;
            op_type = 0;
            continue;
        }
        else if (input[i] == "-")
        {
            temp_op_type = op_type;
            op_type = 1;
            continue;
        }
        else if (input[i] == "*")
        {
            temp_op_type = op_type;
            op_type = 2;
            continue;
        }
        else if (input[i] == "/")
        {
            temp_op_type = op_type;
            op_type = 3;
            continue;
        }
        else
        switch(op_type)
        {
            case 0: //+
            {
                //print << "SUM: " << std::stoi(input[i]) << endl;
                result += std::stoi(input[i]);
                break;
            }
            case 1: //-
            {
                //print << "SUB: " << std::stoi(input[i]) << endl;
                result -= std::stoi(input[i]);
                break;
            }
            case 2:
            {
                if (temp_op_type == 0)
                {
                    result -= std::stoi(input[i - 2]);
                    result += (std::stoi(input[i - 2]) * std::stoi(input[i]));
                    //i+=2;
                    continue;
                }
                else if (temp_op_type == 1)
                {
                    result += std::stoi(input[i - 2]);
                    result -= (std::stoi(input[i - 2]) * std::stoi(input[i]));
                    //i+=2;
                    continue;
                }
                
            }
            case 3:
            {
                if (temp_op_type == 0)
                {
                    result -= std::stoi(input[i - 2]);
                    result += (std::stoi(input[i - 2]) / std::stoi(input[i]));
                    //i+=2;
                    continue;
                }
                else if (temp_op_type == 1)
                {
                    result += std::stoi(input[i - 2]);
                    result -= (std::stoi(input[i - 2]) / std::stoi(input[i]));
                    //i+=2;
                    continue;
                }
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
    print << endl << "Expression: ";
    std::cin.ignore();
    std::getline(std::cin, t);
    split(t, n);
    calculate(n, len);
    return EXIT_SUCCESS;
}
