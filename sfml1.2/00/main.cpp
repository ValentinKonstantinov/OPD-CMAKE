#include <iostream>

int main()
{

    int num = 1;
    // условие: пока num меньше или равно 100
    for (int num = 1; num <= 100; num += 1) // цикл выводит числа от 1 до 100
    {
        if ((num % 3 == 0) && (num % 5 == 0))
        {
            std::cout << "FizzBuzz" << std::endl;
        }
        else if (num % 3 == 0)
        {
            std::cout << "Fizz" << std::endl;
        }
        else if (num % 5 == 0)
        {
            std::cout << "Buzz" << std::endl;
        }
        else
        {
            std::cout << num << std::endl;
        }
    }
}