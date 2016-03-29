#ifndef __SINGLETON_H__
#define  __SINGLETON_H__

#include <unistd.h> //for sleep
#include <stdlib.h> //for atexit
#include <cassert> //for assert
#include "mydefs.h"

DEBUG_ONLY(static int count = 0;)

namespace RD3
{

class Flower
{

public:
	void PrintFlower();
	Flower();

private:

	int m_yan;
	int m_moshe;
};

template<class T>
class Singleton
{

public:
	static T& Inst();

private:
	static volatile int shouldInit;
	static volatile bool isReady;

	static T* s_t;

	static void Destroyer();
};

template<class T>
T* Singleton<T>::s_t = NULL;


template<class T>
volatile int Singleton<T>::shouldInit = 0;

template<class T>
volatile bool Singleton<T>::isReady = false;


template<class T>
inline T& Singleton<T>::Inst()
{
	assert(s_t != reinterpret_cast<T*>(reinterpret_cast<char*>(0xdeadbeef)));

	if(!isReady)
	{
		if(!__sync_fetch_and_or( &shouldInit, 1 ))
		{
			s_t = new T;
			atexit(Destroyer);
			isReady = true;
		}

		while(!isReady)
		{
			sleep(0);
		}
	}

	return *s_t;
}


template<class T>
inline void Singleton<T>::Destroyer()
{
	delete s_t;
	s_t = reinterpret_cast<T*>(0xdeadbeef);
}

inline Flower::Flower():m_yan(1), m_moshe(2)
{
	DEBUG_ONLY(++count;)
}

inline void Flower::PrintFlower()
{
	DEBUG_ONLY(std::cerr << "I am flower" << std::endl;)
	DEBUG_ONLY(std::cerr << "construction counter: " << count << std::endl;)
}

/*
template<class T>
T& GetS()
{
	static T instance;
	return instance;
}

template<class T>
void DelS(T* t)
{
	delete t;
}

class MS
{

public:
	static int count;
	void Flower();
private:
	int m_yan;
	int m_moshe;
	int *m_tal;

	template<class T>
	friend T& GetS();

	template<class T><
	friend void DelS(T);

	MS();
	~MS();
	MS(const MS& ms_);

};

class HS
{

public:
	static int count;
	void Animal();
private:
	int m_yan;
	int m_moshe;
	int *m_tal;

	template<class T>
	friend T& GetS();

	HS();
	~HS();
	HS(const MS& ms_);

};

class DS
{

public:
	static int count;
	~DS();
	void Tree();
private:
	int m_yan;
	int m_moshe;
	int *m_tal;

	template<class T>
	friend T& GetS();

	DS();

	DS(const MS& ms_);

};*/
} // namespace rd3
#endif /*  __SINGLETON_H__ */
