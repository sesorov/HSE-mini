#include <iostream>
#define print std::cout
using std::endl;
using std::string;

int main(int argc, const char * argv[])
{
    using namespace std;
    int result = atoi(argv[1]);
    for (int i = 2; i < argc; i += 2)
    {
        if (*argv[i] == '+') result += atoi(argv[i + 1]);
        if (*argv[i] == '-') result -= atoi(argv[i + 1]);
        if (*argv[i] == 'x')
        {
            if (*argv[i - 2] == '-')
            {
                result += atoi(argv[i - 1]);
                result -= (atoi(argv[i+1]) * atoi(argv[i-1]));
            }
            else if (*argv[i - 2] == '+')
            {
                result -= atoi(argv[i - 1]);
                result += (atoi(argv[i+1]) * atoi(argv[i-1]));
            }
            else result *= atoi(argv[i + 1]);
        }
        if (*argv[i] == '/')
        {
            if (!atoi(argv[i+1]))
            {
                printf("Error: division by zero.\n");
                exit(1);
            }
            else
            {
                if (*argv[i - 2] == '-')
                {
                    result += atoi(argv[i - 1]);
                    result -= (atoi(argv[i-1]) / atoi(argv[i+1]));
                }
                else if (*argv[i - 2] == '+')
                {
                    result -= atoi(argv[i - 1]);
                    result += (atoi(argv[i-1]) / atoi(argv[i+1]));
                }
                else result /= atoi(argv[i + 1]);
            }
        }
    }
    cout << result << endl;
    return EXIT_SUCCESS;
}
