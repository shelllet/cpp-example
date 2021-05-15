// Construtor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int init_age() {
	std::cout << "init age£º" << __FUNCTION__ << std::endl;
	return 0;
}
int init_color() {
	std::cout << "init color£º" << __FUNCTION__ << std::endl;
	return 0;
}



class Animal {
public:
	static int test_this(Animal* e) {
		return e->extra;
	}
	Animal() try : color(init_color()), age(init_age()) {

	}
	catch (...) {

	}
	/*animal(int age) : age(test_this(this)) {


	}*/

	Animal(int age, int color) : age(age), color(color) {

	}
	Animal(int age) :Animal(age, 0xff) {

	}

public:
	int getAge() { return age; }
private:
	int color = 0xfffff;
	int age = 0;

	int extra = 0xff;
};

class Dog : public Animal {
public:
	Dog() {

	}
	Dog(int age) : Animal(age) {}
};
int main()
{
	Dog dog;

	Dog dog2 = 5;

	std::cout << dog.getAge() << std::endl;
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
