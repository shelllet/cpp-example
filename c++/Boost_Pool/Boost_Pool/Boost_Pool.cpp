// Boost_Pool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <boost/pool/pool_alloc.hpp>
#include <chrono>
#define MAX_COUNT 100000000
int main()
{

	{
		std::vector<int> v;
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < MAX_COUNT; ++i)
			v.push_back(i);
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> diff = end - start;
		std::cout << "# 1.elapse: " << diff.count() << std::endl;
	}




	{


		std::vector<int, boost::pool_allocator<int, boost::default_user_allocator_new_delete, boost::details::pool::default_mutex, 32, 128>> v;
		auto start = std::chrono::system_clock::now();
		for (int i = 0; i < MAX_COUNT; ++i)
			v.push_back(i);

		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> diff = end - start;
		std::cout << "# 2.elapse: " << diff.count() << std::endl;

		v.clear();
		boost::singleton_pool<boost::pool_allocator_tag, sizeof(int)>::
			purge_memory();
	}

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
