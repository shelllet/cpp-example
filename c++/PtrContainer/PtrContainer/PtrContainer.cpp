// PtrContainer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_inserter.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <sstream>
class animal {
public:
	std::string name;

	int legs;

	bool has_tail;

	
	std::ostream& operator<< (std::ostream& os) const {
		os << "name: " << name << '\n'
			<< "legs: " << legs << "\n"
			<< "tail: " << has_tail;

		return os;
	}
	friend std::ostream& operator<< (std::ostream& os, const animal& a) {
		os << "name: " << a.name << '\n'
			<< "legs: " << a.legs << "\n"
			<< "tail: " << a.has_tail;

		return os;
	}
	constexpr bool operator()(const animal& _Left, const animal& _Right) const {
		return _Left.legs < _Right.legs;
	}
};

//std::ostream& operator<< (std::ostream& os, const animal& a) {
//	os << "name: " << a.name << '\n'
//		<< "legs: " << a.legs << "\n"
//		<< "tail: " << a.has_tail;
//
//	return os;
//}



int main()
{
	boost::ptr_set<animal, animal> animals;

	animals.insert(new animal{ "dog", 4,  true });
	animals.insert(new animal{ "cat", 1,  true });
	animals.insert(new animal{ "duck", 2,  false });


	const animal obj = *animals.begin();

	//std::ostream myout(std::cout.rdbuf());

	obj.operator<<(std::cout);
	std::cout << obj;
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
