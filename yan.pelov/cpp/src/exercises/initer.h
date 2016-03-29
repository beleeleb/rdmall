/*
 * Yan 16/2/15
 *
 */
#ifndef __INITER_H__
#define  __INITER_H__

#include <iostream>
#include <cstring> //for memset
#include "mydefs.h"

#define G_DEC(T, g_t) extern T g_t; extern bool g_tShould; static Tiniter<T> g_tInit(&g_t, &g_tShould) //to be used in the desired h file
#define G_DEF(T, g_t) double g_t[sizeof(T)]; bool g_tShould = true //to be used in the desired cpp file

template <class T>
class Tiniter
{
public:
	Tiniter(T* t_, bool* should_);
	~Tiniter();

private:
	T* m_t;
	bool m_should;
};

template <class T>
inline Tiniter<T>::Tiniter(T* t_, bool* should_): m_t(t_), m_should(*should_)
{
	if(m_should)
	{
		new(m_t) T;
		*should_ = false;
	}
}

template <class T>
inline Tiniter<T>::~Tiniter()
{
	if(m_should)
	{
		m_t -> ~T();
		memset(m_t, 0xdeadbeef, sizeof(T));
	}
}

class X
{
public:
	X();
	~X();
	void PrintX();

private:
	int m_var1;
	int m_var2;
	int* m_ptr;
};


inline X::X():m_var1(30), m_var2(100), m_ptr(new int[40])
{}

inline X::~X()
{
	delete m_ptr;
}

inline void X::PrintX()
{
	std::cerr << "Diamonds are forever!" << std::endl;
}


#endif /*  __INITER_H__ */
