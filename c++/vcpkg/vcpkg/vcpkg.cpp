// vcpkg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/lexical_cast.hpp>

struct A {
    int value;

    friend std::ostream& operator<< (std::ostream& os, const A& a) {
        os << a.value;
        return os;
    }
    
    friend std::istream& operator>> (std::istream& is, A& a) {
        is >> a.value;
        return is;
    }


};


int main()
{
    std::cout << "Hello World!\n";

    auto string = boost::lexical_cast<std::string>(10);



    std::cout << string << std::endl;

    std::cout << boost::lexical_cast<int>(string);


  auto a =  boost::lexical_cast<A>(123);

  std::cout << a.value << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
