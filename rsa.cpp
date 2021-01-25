#include <iostream>
#include <cmath>


bool isPrime(long int prime);
long int multiplyNumbers(long int p, long int q);
long int functionOfEueler(long int p, long int q);
long int calculateE(long int t);
long int greatestCommonDivisor( long int e, long int t );
long int calculateD(long int e, long int t);
long long encrypt(long int i, long int e, long int n);
long long decrypt(long long i, long int d, long int n);


int main()
{
    // Инициализация переменных
    long int p, q, n, t, e, d, msg;
    bool flag;
    long long encryptedText, decryptedText;


    std::cout << "Welcome to RSA program" << std::endl << std::endl;

    // Ввод первого простого числа
    do {
        std::cout << "Enter a prime number p:" << std::endl;
        std::cin >> p;

        flag = isPrime(p);

        if(!flag)
        {
            std::cout << "\nWRONG INPUT (This number is not Prime. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself)\n" << std::endl;
        }

    } while(!flag);

    // Ввод второго простого числа
    do {
        std::cout << "Enter a prime number q:" << std::endl;
        std::cin >> q;

        flag = isPrime(q);

        if(!flag)
        {
            std::cout << "\nWRONG INPUT (This number is not Prime. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself)\n" << std::endl;
        }

    } while(!flag);

    // Умножение
    n = multiplyNumbers(p, q);

    // функция Ейлера
    t = functionOfEueler(p, q);

    // Расчёт открытой экспоненты
    e = calculateE(t);

    //Расчёт секретной экспоненты
    d = calculateD(e, t);

    // Публикация открытого ключа
    std::cout << "Opening key = {" << e << ", " << n << "}" << std::endl;

    // Ввод сообщения
    std::cout << "\nEnter a message: " << std::endl;
    std::cin >> msg;

    // Шифрование сообщения
    encryptedText = encrypt(msg, e, n);
    std::cout << "\nEncrypted message: " << encryptedText << std::endl;

    // Расшифровка сообщения
    decryptedText = decrypt(encryptedText, d, n);
    std::cout << "\nDecrypted text: " << decryptedText << std::endl;

    return 0;
}

// Проверка на простоту
bool isPrime(long int prime)
{
    long int i, j;

    j = (long int)sqrt((long double)prime);

    for(i = 2; i <= j; i++)
    {
        if(prime % i == 0)
        {
            return false;
        }
    }

    return true;
}

// Умножение
long int multiplyNumbers(long int p, long int q)
{
    return p * q;
}

// Функция Ейлера
long int functionOfEueler(long int p, long int q)
{
    return (p - 1) * (q - 1);
}

// Калькулятор открытой экспоненты
long int calculateE(long int t)
{
    long int e;

    for ( e = 2; e < t; e++ )
    {
        if (greatestCommonDivisor( e, t ) == 1 )
        {
            return e;
        }
    }

    return -1;
}

// Найбольший общий делитель
long int greatestCommonDivisor( long int e, long int t )
{
    while ( e > 0 )
    {
        long int myTemp;

        myTemp = e;
        e = t % e;
        t = myTemp;
    }

    return t;
}

// Калькулятор секретной экспоненты
long int calculateD( long int e, long int t)
{

    long int d;
    long int k = 1;

    while (true)
    {
        k = k + t;

        if ( k % e == 0)
        {
            d = (k / e);
            return d;
        }
    }

}

// Шифрование
long long encrypt( long int i, long int e, long int n )
{
    long long result = 1;
    for(int j = 0; j < e; j++)
    {
        result = result * i % n;
    }

    return result;

}

// Расшифровка
long long decrypt(long long i, long int d, long int n)
{
    long long result = 1;
    for(int j = 0; j < d; j++)
    {
        result = result * i % n;
    }

    return result;
}
