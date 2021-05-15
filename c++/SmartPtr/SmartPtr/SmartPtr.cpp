// SmartPtr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

std::weak_ptr<int> gw;

void observe()
{
	std::cout << "use_count == " << gw.use_count() << ": ";
	if (auto spt = gw.lock()) { // Has to be copied into a shared_ptr before usage
		std::cout << *spt << "\n";
	}
	else {
		std::cout << "gw is expired\n";
	}
}


int main()
{
	gw  = std::make_shared<int>(42);



	observe();

	{

	std::unique_ptr<int> u = std::make_unique<int>(2);
	}

	int* p = new int(6);
	{
		{

			std::shared_ptr<int> p1( p );
	
		}
		{

			std::shared_ptr<int> p2(p);
		}

	}

    std::cout << "Hello World!\n";
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
