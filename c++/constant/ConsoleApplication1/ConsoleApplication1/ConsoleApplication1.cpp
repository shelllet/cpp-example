// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <locale>
#include <codecvt>

#define Max 255

int main()
{
    std::cout << "Hello World!\n";

   1.0;
   10;
   0x1b;
   15u;
   15ul;
   160ll;
   3.0f;

   std::cout << "\"Hello world\"" <<  std::endl;

   std::cout << R"("Hello world

        std::cout << "\"Hello world\"" <<  std::endl;
        std::cout << "\"Hello world\"" <<  std::endl;
")" << std::endl; 

   std::string s = "中文";
   std::u8string ustr = u8"中文";
  // s = ustr;
   std::wstring ws = L"中文";
   std::u16string u16;

  // std::wstring_convert<std::codecvt_utf8_utf16<char>> ss;

   int a = Max;

   const int A = 10;

   int array[A];
  
    // ::SetWindowText();

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
