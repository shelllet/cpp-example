// primitive_types.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";


    int a = 10;

     bool b = true;
     unsigned char c = 'жа';
    std::cout << "c: " << c << std::endl;
     float f = 0.5f;
    double d = 0.5;


    //
    wchar_t t = 'жа';
    std::cout << "t: " << t << std::endl;

    std::cout << "int: " << sizeof(int) << std::endl;
    std::cout << "bool: " << sizeof(bool) << std::endl;
    std::cout << "char: " << sizeof(char) << std::endl;
    std::cout << "float: " << sizeof(float) << std::endl;
    std::cout << "double: " << sizeof(double) << std::endl;
    std::cout << "wchar_t: " << sizeof(wchar_t) << std::endl;

    std::cout << "short --------------" << std::endl;
	std::cout << "int: " << sizeof(short) << std::endl;
	std::cout << "bool: " << sizeof(bool) << std::endl;
	std::cout << "char: " << sizeof(char) << std::endl;
	std::cout << "float: " << sizeof(float) << std::endl;
	std::cout << "double: " << sizeof(double) << std::endl;
	std::cout << "wchar_t: " << sizeof(wchar_t) << std::endl;


	std::cout << "long --------------" << std::endl;
	std::cout << "int: " << sizeof(long long) << std::endl;
	std::cout << "bool: " << sizeof( bool) << std::endl;
	std::cout << "char: " << sizeof(char) << std::endl;
	std::cout << "long float: " << sizeof(long float) << std::endl;
	std::cout << "long double: " << sizeof(long double) << std::endl;
	std::cout << "long double: " << sizeof(long long) << std::endl;
	std::cout << "wchar_t: " << sizeof(wchar_t) << std::endl;
    class A {

    };
    struct B {};
   // std::cout << "void: " << sizeof(void) << std::endl;
   std::cout << "A: " << sizeof(A) << std::endl;
   std::cout << "B: " << sizeof(B) << std::endl;


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
