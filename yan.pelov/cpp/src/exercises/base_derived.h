#ifndef __BASE_DERIVED_H__
#define  __BASE_DERIVED_H__

#include <iostream>
using namespace std;

class Base
{
public:
	Base(int i): m_i(i), m_iptr(&m_i) {}

	virtual void foo() { cout << *(m_iptr) << endl; }
	virtual void bar() { cout << m_i << endl; }

protected:
	virtual ~Base() = 0;

private:
	int m_i;
	int *m_iptr;
};

inline Base::~Base() {}

class Derived: public Base
{
public:
	Derived(int i, char c): Base(i), m_c(c), m_c2(c) {}
	void bar() { foo(); Base::foo(); }

private:
	void foo() { cout << m_c << endl; }
	char m_c, m_c2;
};

class OtherDerived: public Base
{
};

#endif // __BASE_DERIVED_H__
