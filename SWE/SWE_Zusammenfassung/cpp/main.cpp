#include "derivedclass.h"
#include <iostream>

int main()
{
    try
    {
        // Create an instance of derivedclass with a size of 5
        derivedclass<int> myDerived(5);

        // Add some values to the derived class
        myDerived.addValue(10);
        myDerived.addValue(20);
        myDerived += 30;

        // Access values using operator[]
        std::cout << "Value at index 0: " << myDerived[0] << std::endl;
        std::cout << "Value at index 1: " << myDerived[1] << std::endl;
        std::cout << "Value at index 2: " << myDerived.getValue(2) << std::endl;

        // Demonstrate copy constructor
        derivedclass<int> copiedDerived(myDerived);
        std::cout << "Copied: " << copiedDerived << std::endl;

        // Demonstrate move constructor
        derivedclass<int> movedDerived(std::move(myDerived));
        std::cout << "Moved: " << movedDerived << std::endl;

        // Iterate through the values using the iterator
        std::cout << "Iterating through values: ";
        for (auto it = movedDerived.begin(); it != movedDerived.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}