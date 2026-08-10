#include <Array.hpp>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#define MAX_VAL 750

int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = std::rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = std::rand();
    }
    delete [] mirror;//

    std::cout << std::endl << "=== Test: an empty array ===" << std::endl;
    {
        Array<int> empty;

        std::cout << "size() = " << empty.size() << std::endl;
        try
        {
            std::cout << empty[0] << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "Caught: " << e.what() << std::endl;
        }
    }

    std::cout << std::endl << "=== Test: elements are default initialized ===" << std::endl;
    {
        Array<int> fresh(3);

        std::cout << "size() = " << fresh.size() << std::endl;
        for (unsigned int i = 0; i < fresh.size(); i++)
            std::cout << "fresh[" << i << "] = " << fresh[i] << std::endl;
    }

    std::cout << std::endl << "=== Test: copies are independent ===" << std::endl;
    {
        Array<std::string> original(2);

        original[0] = "first";
        original[1] = "second";

        Array<std::string> copied(original);
        Array<std::string> assigned;

        assigned = original;
        original[0] = "changed";

        std::cout << "original[0] = " << original[0] << std::endl;
        std::cout << "copied[0]   = " << copied[0] << std::endl;
        std::cout << "assigned[0] = " << assigned[0] << std::endl;
    }

    std::cout << std::endl << "=== Test: a const array can still be read ===" << std::endl;
    {
        Array<int>       writable(2);

        writable[0] = 21;
        writable[1] = 42;

        const Array<int> readable(writable);

        std::cout << "readable[1] = " << readable[1] << ", size() = "
            << readable.size() << std::endl;
        try
        {
            std::cout << readable[2] << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "Caught: " << e.what() << std::endl;
        }
    }

    std::cout << std::endl << "=== End of tests ===" << std::endl;
    return 0;
}
