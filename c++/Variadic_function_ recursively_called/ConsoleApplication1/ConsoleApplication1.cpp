// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <any>


void format(std::string& result, const std::string& fmt, const std::vector<std::any>& values)
{
	std::cout << "invoked." << std::endl;
}


template <
	typename T,
	typename... Args>
void format(std::string& result, const char* fmt, Args... args)
//void format(std::string& result, const char* fmt, T arg1, Args... args)
/// Appends the formatted string to result.
{
	std::vector<std::any> values;
	//values.reserve(sizeof...(Args) + 1);
	//values.emplace_back(arg1);
	values.reserve(sizeof...(Args));
	values.insert(values.end(), { args... });
	format(result, fmt, values);

}


template <
	typename T,
	typename... Args>
std::string format(const char* fmt, T arg1, Args... args)
/// Returns the formatted string.
{
	std::vector<std::any> values;
	values.reserve(sizeof...(Args) + 1);
	values.emplace_back(arg1);
	values.insert(values.end(), { args... });
	std::string result;
	::format(result, fmt, values);
	return result;
}

int main()
{
	std::string connector = "sqlite", connectionString="c:\\sqlite.db";

	format("%s:///%s", connector, connectionString);
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
