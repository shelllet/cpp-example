// boost_spirit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <iostream>
#include <string>
int main()
{
	std::vector<float> outputs;

	std::string input = " 300,    300 ";

	auto it = input.begin();

	//input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());

	using namespace boost::spirit;

	//boost::split(input, outputs, boost::is_any_of(","));
	qi::phrase_parse(it, input.end(), qi::float_ % lexeme[lit(',') | lit(' ')], ascii::space | '(' | ')', outputs);


	//std::transform(outputs.begin(), outputs.end(), std::back_inserter(results), [](auto& _1) {
	//	
	//		return static_cast<float>(std::get<int>(_1));
	//	return std::get<float>(_1);
	//	});

	for (auto& x : outputs)
		std::cout << x << std::endl;
	return 0;
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
