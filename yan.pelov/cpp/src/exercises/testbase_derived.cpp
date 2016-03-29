#include <iostream>
using namespace std;

#include "base_derived.h"

int main(int argc, char** argv, char** envp)
{
	Derived d1(5, 'x');
	Derived d2(3, 'w');

	Base *b1 = &d1;
	b1->foo();
	b1->bar();

	Base *b2 = &d2;
	*b2 = *b1;
	b2->foo();
	d2.bar();

	return 0;
}
