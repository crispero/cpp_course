#include <iostream>
#include <iostream>

int main()
{
    for (int num = 1; num <= 100; num += 1)
    {
       // если число делится на 3 и на 5 
       if ((num % 3 == 0) && (num % 5 == 0))
       {
           // выводим FizzBuzz
           std::cout << "FizzBuzz" << std::endl;
       }
       // если число делится на 3
       else if (num % 3 == 0)
       {
           // выводим Fizz
           std::cout << "Fizz" << std::endl;
       }
       // если число делится на 5
       else if (num % 5 == 0)
       { 
           // выводим Buzz
           std::cout << "Buzz" << std::endl;
       }
       else
       {
           // выводим число num
           std::cout << num << std::endl;
       }
   }
}

