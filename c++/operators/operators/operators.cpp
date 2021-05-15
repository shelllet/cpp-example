// operators.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>
int main()
{
    std::cout << "Hello World!\n";
    int x;
    std::cin >> x;

    std::cout << "\n" << x;

    int y = 10;


    std::cout << "\nmodulo" << x % y << std::endl;

    printf("%s\n", "ss");

    int r = rand() % 10;


    int z = x > 10 ? 5 : 3;

    std::cout << "z: " << z << std::endl;


    y -= 5;
    y = y - 5;

    y += 50;

    y++;
    y--;

    ++y;
    --y;

    y = 10;
    std::cout << y++ << std::endl;
    std::cout << ++y << std::endl;

    std::cout << !true << std::endl;
    std::cout << (0 && 1) << std::endl;
    std::cout << (0 || 1) << std::endl;

    int a=0, b=0, c=0;
    
    if (c = a + b, c) {

    }

    x & 5;
    x | 5;

    x >> 5;
    x << 5;
    
    c = 0b101;

    std::bitset<5> bc = c >> 1;
    std::cout << bc <<std::endl;

    c = 0b101;
	bc = static_cast<std::int64_t>(c) << 1;
	std::cout << bc << std::endl;

    sizeof(int);
    class A {
    public:
        int a;
    };
    sizeof(A);

    A* p = 0;
    *p;

    p->a = 10;

   
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
