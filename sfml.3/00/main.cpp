#include <iostream>

int main()
{
    int num = 0;
    while (num < 100)
    {
        if (num % 15)
        {
            std::cout << "FizzBuzz" << std::endl;
        }
        else if (num % 3)
        {
            std::cout << "Fizz" << std::endl;
        }
        else if (num % 5)
        {
            std::cout << "Buzz" << std::endl;
        }
        else
        {
            std::cout << num << std::endl;
        }
        num += 1;
    }
}