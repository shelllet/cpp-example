// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


class A {
public:
    A(A* ptr) {
        std::cout << "called 1" << std::endl;
    }

	template<typename... TArgs>
    A(void *p, TArgs&&... args) { 
        std::cout << "called 2" << std::endl; 
    }
    template< typename... TArgs, typename = std::enable_if_t<not std::is_same_v<A*, TArgs...>>>
    A(TArgs&&... args) { 
        std::cout << "called 3" << std::endl; 
    }
};
int main()
{
    int p1 = 5;
    int p2 = 6;
    auto a = new A(&p1);

    

    new A(a);
    new A(p1);
    new A(p2);
    new A(nullptr,p1, p2);
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
