#include <iostream>
#define print std::cout
using std::endl;
using std::string;
const char SUM = 0;
const char SUB = 1;
const char MUL = 2;
const char DIV = 3;

void setOperation(char in, char &temp_OpType)
{
    switch (in)
    {
        case '+':
        {
            temp_OpType = SUM;
            break;
        }
        case '-':
        {
            temp_OpType = SUB;
            break;
        }
        case 'm':
        {
            temp_OpType = MUL;
            break;
        }
        case '/':
        {
            temp_OpType = DIV;
            break;
        }
        default:
            break;
    }
}

int main(int argc, const char * argv[])
{
    using namespace std;
    cout << argc << endl;
    char operation = SUM, temp_operation = operation;
    int res(0);
    for (int i = 1; i < argc; ++i)
    {
        if (operation == SUM) // +
        {
            if (i % 2 != 0)
            {
                res += atoi(argv[i]);
            }
            else
            {
                temp_operation = operation;
                setOperation(*argv[i], operation);
            }
        }
        else if (operation == SUB) // -
        {
            if (i % 2 != 0)
            {
                res -= atoi(argv[i]);
            }
            else
            {
                temp_operation = operation;
                setOperation(*argv[i], operation);
            }
        }
        else if (operation == MUL || operation == DIV)
        {
            if (i % 2 != 0)
            {
                switch (temp_operation)
                {
                    case SUM:
                    {
                        res -= atoi(argv[i - 2]);
                        res += (operation == MUL) ? (atoi(argv[i - 2]) * atoi(argv[i])) : (atoi(argv[i - 2]) / atoi(argv[i]));
                        break;
                    }
                    case SUB:
                    {
                        res += atoi(argv[i - 2]);
                        res -= (operation == MUL) ? atoi(argv[i - 2]) * atoi(argv[i]) : atoi(argv[i - 2]) / atoi(argv[i]);
                        break;
                    }
                    case MUL:
                    {
                        if (operation == MUL) res *= atoi(argv[i]);
                        else res /= atoi(argv[i]);
                        break;
                    }
                    case DIV:
                    {
                        if (operation == DIV) res /= atoi(argv[i]);
                        else res *= atoi(argv[i]);
                        break;
                    }
                    default:
                        break;
                }
            }
            else
            {
                temp_operation = operation;
                setOperation(*argv[i], operation);
            }
        }
    }
    cout << "Res = " << res << endl;
    return EXIT_SUCCESS;
}
