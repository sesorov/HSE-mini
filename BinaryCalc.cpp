#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

bool ONE_OCT[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
bool ONE_HEX[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
bool ONE_32[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

template <typename T>
void Dump(T n, bool* output)    // Получаем двоичную интерпретацию числа (длиной 8/16/32)
{
    T mask;
    const int size(8 * sizeof(T) - 1);
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
    output[0] = (n < 0 ? 1 : 0);        // 7 or 15 or 31
    for (int i = 0; i < size; ++i)
    {
        output[i + 1] = (n & mask ? 1 : 0);    // 6 - 0 or 14 - 0 or 30 - 0
        mask >>= 1;
    }
}

class StoreException
{
private:
    string error_msg;

public:
    StoreException(string error_text) :
        error_msg(error_text) {}

    const char* getError() { return error_msg.c_str(); }
};

int count_bits(int number)
{
    if (number >= -128 && number < 128)
        return 8;
    else if (number >= -32768 && number < 32768)
        return 16;
    else
        return 32;
}

template <typename T>
class Binary // класс для двоичного числа 
{
private:
    static const int size = 8 * sizeof(T);
    

    void calc_dec(bool* binary)     // вычисление десятичного по двоичному
    {
        int num = 0;                // заготовка под десятичное
        if (binary[0])              // если первая цифра двоичного - 1, т.е. оно отрицательное
        {
            bool inverted[size] = { 0 };                               // заготовка под инвертированный массив
            for (uint8_t i = 0; i < size; i++)                         // цикл по всем 8 битам, uint8_t 
                inverted[i] = !bin[i];                              // побитово записываем инвертированные (обратные - 0 на 1, 1 на 0) биты входного массива binary в инвертированный inverted
            Binary temp = Binary(inverted);
            try
            {
                bool one[size] = { 0 };
                one[size - 1] = 1;
                temp = temp + Binary(one);  // складываем инвертированное и единицу (в двоичном виде!), чтобы получить дополнительный код числа 
                for (uint8_t i = size-1; i > 0; i--)                         // идя в обратную сторону, по классике вычисляем десятичное значение путем умножения степени двойки на 1/0 (см. перевод из двоичного в десятичное)
                    num += (int)pow(2, size-1 - i) * temp.bin[i];
            }
            catch (StoreException& ex)
            {
                num = pow(2, size-1);
            }
            set_dec((T)-num);                                    // записываем результат в приватную переменную dec (с минусом спереди, так как число - отрицательное! (см. if (binary[0])))
        }
        else // иначе, если число - положительное (первая цифра 0)
        {
            for (uint8_t i = size-1; i > 0; i--)             // просто по классике вычисляем десятичное с помощью степеней двойки
                num += (int)pow(2, size-1 - i) * binary[i];
            set_dec((T)num);                         // записываем результат в приватную переменную dec
        }
    }
    void set_bin(bool* new_bin)                 // просто функция, которая поэлементно копирует входной массив в приватный bin
    {
        for (uint8_t i = 0; i < size; i++)
            bin[i] = new_bin[i];
    }
    void set_dec(T decimal)                  // просто функция, записывающая входное число в приватную dec
    {
        dec = decimal;
    }
public:
    T dec;
    bool bin[size] = { 0 };    // 8 бит, все заполнены нулями (сначала)

    Binary()
    {
        dec = 0;    // если на вход при создании экземпляра не приходит ничего - то ставим 0
    }

    Binary(T dec) : dec(dec)  // на вход приходит десятичное число 
    {
        bool temp[size] = { 0 };   // создаем массив-шаблон, в который дальше запишем двоичную интерпретацию полученного числа (dec)
        Dump<T>(dec, temp);  // записываем двоичную интерпретацию в заготовленный массив через функцию дампа
        set_bin(temp);          // так как у нас переменная bin приватная, то записываем в нее значение через спец. функцию
    }

    Binary(bool* binary)         // на вход приходит двоичное число
    {
        set_bin(binary);            // сохраняем его
        calc_dec(binary);           // вычисляем десятичное
    }

    void prt_dec()    
    {
        cout << int(dec);
        cout << endl;
    }

    void prt_bin()
    {
        calc_dec(bin);
        for (uint8_t i = 0; i < size; i++)
            cout << bin[i];
        cout << endl;
    }
};

template <typename T>
const Binary<T> operator+(const Binary<T>& left, const Binary<T>& right)                // перегрузка +
{
    const int size = 8 * sizeof(T);
    bool sum[size] = { 0 };
    int r = 0;
    for (uint8_t i = 0; i < size; i++)                                     // идем по очереди от 0 до 7 включительно (при этом внутри цикла мы идем от 7 до 0, т.е. с конца!)
    {
        sum[size - 1 - i] = (left.bin[size - 1 - i] + right.bin[size - 1 - i] + r) % 2;       // сумму записываем с конца - суммируем два бита с конца, прибавляем к ним r - остаток и ищем остаток от деления на 2 (если получилось 1+1=2, то в итоге запишем 1, а вторую единицу перенесем в след. разряд)
        r = (left.bin[size - 1 - i] + right.bin[size - 1 - i] + r) / 2;              // остаток в случае, если, к примеру, оба бита равны 1 (сумма равна 2) и нам нужно перенести остаток дальше
    }
    if ((left.bin[0] == right.bin[0]) && left.bin[0] != sum[0])
        throw StoreException("Error: binary overflow.");
    return Binary<T>(sum);                                  // возвращаем всегда в такуих функциях-перегрузках экземпляр класса!
}

template <typename T>
const Binary<T> operator++(Binary<T>& num, int)         // перегрузка ПОСТФИКСНОГО ++ (инкремент - мы увеличиваем значение на 1, но, в отличие от префиксного, возвращаем старое значение)
{
    const int size = 8 * sizeof(T);
    Binary<T> old = Binary<T>(num.bin);                 // сохраняем старое значение функции (пока что - текущее)
    num = num + Binary<T>(size == 8 ? ONE_OCT: size == 16 ? ONE_HEX : ONE_32);                         // увеличиваем значение переменной, поданной на вход, на 1
    return old;                                         // возвращаем СТАРОЕ значение (в случае с префиксным ++ мы возвращали бы новое)
}

template <typename T>
const Binary<T> operator-(const Binary<T>& left, const Binary<T>& right)        // перегрузка - (алгоритм: получаем отрицательную версию числа справа от минуса и складываем её с левой частью)
{
    const int size = 8 * sizeof(T);
    bool inverted[size] = { 0 };                               // готвим массив для инвертированного числа (чтобы получить отрицательную версию положительного двоичного числа, нужно к его инвертированной версии добавить двоичную единицу)
    for (uint8_t i = 0; i < size; i++)                         // инвертируем в цикле
        inverted[i] = !right.bin[i];
    return left + (Binary<T>(inverted) + Binary<T>(size == 8 ? ONE_OCT : size == 16 ? ONE_HEX : ONE_32));   // как и сказано выше, возвращаем сумму левой части (т.к. разность у нас left - right) и отрицательную версию правой через сумму инвертированного и единицы
}

template <typename T>
const Binary<T> operator--(Binary<T>& num, int)        // перегрузка ПОСТФИКСНОГО -- (декремент - мы уменьшаем значение на 1, но, в отличие от префиксного, возвращаем старое значение)
{
    const int size = 8 * sizeof(T);
    Binary<T> old = Binary<T>(num.bin);         // сохраняем старое
    num = num - Binary<T>(size == 8 ? ONE_OCT : size == 16 ? ONE_HEX : ONE_32);                 // уменьшаем на 1
    return old;                                 // возвращаем старое
}

template <typename T>
const Binary<T> operator*(const Binary<T>& left, const Binary<T>& right)    // перегрузка * (умножения): выглядит как left умножить на right
{
    const int size = 8 * sizeof(T);
    Binary<T> temp = Binary<T>(left.dec);           // сохраняем левую часть в отдельную переменную, т.к. const мы менять не можем
    if (right.dec == 0 || left.dec == 0)                             // если справа/слева 0 - сразу возвращаем 0
        return Binary<T>((T)0);                  // (T)0 так как иначе компилятору может показаться, что мы передаем массив из одного bool, что выкинет ошибку
    for (int i = 1; i < abs(right.dec); i++)    // идем с единицы до модуля числа, на которое умножаем (оно может быть меньше 0)
        temp = temp + left;
    if (right.bin[0] == 1)
    {
        bool inverted[size] = { 0 };                               // готвим массив для инвертированного числа (чтобы получить отрицательную версию положительного двоичного числа, нужно к его инвертированной версии добавить двоичную единицу)
        for (uint8_t i = 0; i < size; i++)                         // инвертируем в цикле
            inverted[i] = !temp.bin[i];
        temp = Binary<T>(inverted) + Binary<T>(size == 8 ? ONE_OCT : size == 16 ? ONE_HEX : ONE_32);
    }
    return temp;
}

template <typename T>
ostream& operator<<(ostream& output, const Binary<T>& num)
{
    const int size = 8 * sizeof(T);
    printf("Binary of %d:\t", (int)num.dec);
    for (uint8_t i = 0; i < size; i++)
        output << num.bin[i];
    return output;
}

bool is_numeric(string input)
{
    for (int i = 0; i < input.length(); i++)
        if (!isdigit(input[i]))
            return false;
    return true;
}

void get_params(string* params)
{
    string input = "";
    bool is_correct = false;

    while (!is_correct)
    {
        uint8_t params_counter = 0;

        cout << "Type desired action using structure: NUMBER_1 x NUMBER_2, where x is +/-/*." << endl;
        getline(cin, input);
        string temp = input;

        stringstream ss(temp);
        while (ss >> temp)
            params_counter++;

        if (params_counter != 3)
        {
            cout << "Incorrect input: wrong parameters count.";
        }
        else
        {
            temp = input;
            params_counter = 0;
            stringstream ss(temp);
            while (ss >> temp)
                params[params_counter++] = temp;

            if (!is_numeric(params[0].substr(1, params[0].length())) || !is_numeric(params[2].substr(1, params[2].length())))
                cout << "Incorrect input: wrong number.";
            else
            {
                if (params[1] == "+" || params[1] == "-" || params[1] == "*")
                    is_correct = true;
                else
                    cout << "Incorrect action: use only +/-/*\n";
            }
        }
    }
}

void perform(string* params, int max_size = 0)
{
    try
    {
        int left = stoi(params[0]);
        int right = stoi(params[2]);

        int l_size = count_bits(left);
        int r_size = count_bits(right);

        int _size = l_size > r_size ? l_size : r_size;

        max_size = !max_size ? _size : max_size;

        switch (max_size)
        {
        case 8:
        {

            Binary<char> a = Binary<char>((char)left);
            Binary<char> b = Binary<char>((char)right);
        
            if (params[1] == "+")
            {
                try
                {
                    cout << "[Result] " << a + b << endl;
                    printf("Binary of %d:\t", left);
                    a.prt_bin();
                    printf("Binary of %d:\t", right);
                    b.prt_bin();
                    break;
                }
                catch (StoreException& ex)
                {
                    perform(params, 16);
                    break;
                }
            }
            else if (params[1] == "-")
            {
                try
                {
                    cout << "[Result] " << a - b << endl;
                    printf("Binary of %d:\t", left);
                    a.prt_bin();
                    printf("Binary of %d:\t", right);
                    b.prt_bin();
                    break;
                }
                catch (StoreException& ex)
                {
                    perform(params, 16);
                    break;
                }
            }
            else if (params[1] == "*")
            {
                try
                {
                    cout << "[Result] " << a * b << endl;
                    printf("Binary of %d:\t", left);
                    a.prt_bin();
                    printf("Binary of %d:\t", right);
                    b.prt_bin();
                    break;
                }
                catch (StoreException& ex)
                {
                    perform(params, 16);
                    break;
                }
            }
            else
                cout << "Error: wrong action." << endl;
            break;
        }
        case 16:
        {
            Binary<short> a = Binary<short>((short)left);
            Binary<short> b = Binary<short>((short)right);
            if (params[1] == "+")
            {
                try
                {
                    cout << "[Result] " << a + b << endl;
                    printf("Binary of %d:\t", left);
                    a.prt_bin();
                    printf("Binary of %d:\t", right);
                    b.prt_bin();
                    break;
                }
                catch (StoreException& ex)
                {
                    perform(params, 32);
                    break;
                }
            }
            else if (params[1] == "-")
            {
                try
                {
                    cout << "[Result] " << a - b << endl;
                    printf("Binary of %d:\t", left);
                    a.prt_bin();
                    printf("Binary of %d:\t", right);
                    b.prt_bin();
                    break;
                }
                catch (StoreException& ex)
                {
                    perform(params, 32);
                    break;
                }
            }
            else if (params[1] == "*")
            {
                try
                {
                    cout << "[Result] " << a * b << endl;
                    printf("Binary of %d:\t", left);
                    a.prt_bin();
                    printf("Binary of %d:\t", right);
                    b.prt_bin();
                    break;
                }
                catch (StoreException& ex)
                {
                    perform(params, 32);
                    break;
                }
            }
            else
                cout << "Error: wrong action." << endl;
            break;
        }
        case 32:
        {
            Binary<int> a = Binary<int>(left);
            Binary<int> b = Binary<int>(right);
            try
            {
                if (params[1] == "+")
                    cout << "[Result] " << a + b << endl;
                else if (params[1] == "-")
                    cout << "[Result] " << a - b << endl;
                else if (params[1] == "*")
                    cout << "[Result] " << a * b << endl;
                else
                    cout << "Error: wrong action." << endl;
                printf("Binary of %d:\t", left);
                a.prt_bin();
                printf("Binary of %d:\t", right);
                b.prt_bin();
                break;
            }
            catch (StoreException& ex)
            {
                cout << "Too large numbers!" << endl;
                break;
            }
        }
        default:
            break;
        }
    }
    catch (const out_of_range& e)
    {
        cout << "Numbers are too large." << endl;
    }
}

int main()
{
    while (true)
    {
        string params[3] = { "" };

        get_params(params);

        perform(params);
    }

    return 0;
}
