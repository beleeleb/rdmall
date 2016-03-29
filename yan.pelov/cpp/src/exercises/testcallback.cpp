#include <iostream>
#include "callback.h"
namespace RD3
{

template<class T> //type of newspaper
class Dog //potential subscriber
{
public:
	explicit Dog();
	~Dog();
	void Fetch(T t);
	void Remove(T);
	void Register(T t);

	Callback<T, Dog>* m_cb;

private:

};

template<class T>
Dog<T>::Dog():m_cb(new Callback<T, Dog<T>> (this, &Dog<T>::Fetch))
{}

template<class T>
Dog<T>::~Dog()
{
	 delete m_cb;
}

template<class T>
void Dog<T>::Fetch(T )
{
	std::cout << "I fetch!  " <<  std::endl;
}

template<class T>
void Dog<T>::Remove(T t)
{
	t.Unsubcribe(m_cb);
}

template<class T>
void Dog<T>::Register(T t)
{
	t.Enroll(m_cb);
}
//template<class T> //type of subscriber
class Haaretz //type of Newspaper Publisher
{
public:
	explicit Haaretz();
	//generated Ctor & Dtor
	void Enroll(CallbackBase<Haaretz>* cb);
	void Unsubcribe(CallbackBase<Haaretz>* cb);
	void Send();

private:
	Dispatcher<Haaretz>* m_disp;
};

Haaretz::Haaretz():m_disp(new Dispatcher<Haaretz>){}

void Haaretz::Enroll(CallbackBase<Haaretz>* cb)
{
	m_disp->Add(cb);
}

void Haaretz::Send()
{
	m_disp->Broadcast(*this);
}

void Haaretz::Unsubcribe(CallbackBase<Haaretz>* cb)
{
	//m_disp->RemoveIMP(cb);
}

} //endof namespace RD3

using namespace RD3;


int main(int argc,char **argv,char **envp) 
{
	Haaretz news1;
	Dog<Haaretz> dog1;
	Dog<Haaretz> dog2;
	Dog<Haaretz> dog3;
	Dog<Haaretz> dog4;
	//d.Register(rr);
	news1.Enroll(dog1.m_cb);
	news1.Enroll(dog2.m_cb);
	news1.Enroll(dog3.m_cb);
	news1.Enroll(dog4.m_cb);

	news1.Send();

	return 0;
}
