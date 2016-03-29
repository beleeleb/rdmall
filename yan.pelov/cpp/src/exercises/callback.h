#ifndef __CALLBACK_H__
#define  __CALLBACK_H__

/*This program allows creating a communication between a client and a publisher.
 * T has to be copyable.
 *
 */

#include <list> //for list container
#include <iostream> //for debug cerr
#include <algorithm> //for foreach
#include <cassert> //for assert check
#include "mydefs.h" //for debug purposes

namespace RD3
{

//Forward Declaration
template <class T> //T stands for type of publisher (could be a newspaper for example).
class Dispatcher;

/*
 * CallBackBase is An abstract wrapping class for CallBack class
 */
template<class T> //T stands for type of publisher (could be a newspaper for example).
class CallbackBase: private Uncopyable
{
public:
	CallbackBase();
	virtual ~CallbackBase();

private:
	/*
	 * Warning!! This is a pure virtual function.
	 * It must be implemented in its derived classes.
	 * Notify activates the Recievers method.
	 */
	virtual void Notify(T) = 0;

	Dispatcher<T>* m_disp;

	void LinkIMP(Dispatcher<T>* newd_);
	void UnLinkIMP();

	friend class Dispatcher<T>; //This friend declaration is needed, in order to allow communication between the publisher and the client.
};

template<class T, class R > //T type - type of publisher, R RCVR - the receiver
class Callback: public CallbackBase<T>
{
public:
	explicit Callback(R* rcvr_, void(R::* const func_)(T));
	virtual ~Callback(){};

private:
	R* m_rcvr; //who is the receiver to receive the service
	void(R::* const func)(T); // what does the receiver do with the service

	virtual void Notify(T);

};

/*
 * Dispatcher: executes Reciever's methods by request
 */
template<class T> //T type - type of publisher
class Dispatcher: private Uncopyable
{
public:
	//using generated Ctor
	~Dispatcher();

	void Add(CallbackBase<T>* cb_); //Add a receiver to service
	void Broadcast(T t_) const; //Activates subscribers methods.

private:

	void RemoveIMP(CallbackBase<T>* cb_); //removes a receiver

	friend class CallbackBase<T>; // used so CallBackBase will be able to remove a receiver

	std::list < CallbackBase<T>* > m_masterlist;
	mutable std::list < CallbackBase<T>* > m_broadcastlist;
};

/*********************************************************************************/

template<class T>
CallbackBase<T>::CallbackBase():m_disp(0)
{
	DEBUG_ONLY(std::cout << "CBB Ctor" << std::endl;)
}


template<class T>
CallbackBase<T>::~CallbackBase()
{
	m_disp->m_masterlist.remove(this);
}

template<class T>
void CallbackBase<T>::LinkIMP(Dispatcher<T>* newd_)
{
	assert(newd_ && "null");
	m_disp = newd_;
}

template<class T>
void CallbackBase<T>::UnLinkIMP()
{
	m_disp = 0;
}

template<class T, class R >
inline Callback<T, R>::Callback(R* rcvr_, void(R::* const func_)(T)):m_rcvr(rcvr_), func(func_)
{
	DEBUG_ONLY(std::cout << "CB Ctor" << std::endl;)
}

template<class T, class R>
void Callback<T, R>::Notify(T t_)
{
	(*(m_rcvr).*func)(t_);
}

template<class T>
void Dispatcher<T>::Add(CallbackBase<T>* o_)
{
	m_masterlist.push_back(o_);
	o_->LinkIMP(this);
}

template<class T>
void Dispatcher<T>::Broadcast(T t_) const
{
	m_broadcastlist = m_masterlist; // copies the list (in order to prevent changes during Broadcasting time).

	for_each(m_broadcastlist.begin(), m_broadcastlist.end(), [t_](CallbackBase<T>* cb_)
	{
		if(cb_)
		{
			cb_->Notify(t_);
			cb_ = 0;
		}
	}

	);
}

template<class T>
inline Dispatcher<T>::~Dispatcher()
{

	for_each(m_masterlist.begin(), m_masterlist.end(), [](CallbackBase<T> *cb_)
	{
		RemoveIMP(cb_);
	});

	for_each(m_broadcastlist.begin(), m_broadcastlist.end(), [](CallbackBase<T> *cb_)
	{
		RemoveIMP(cb_);
	}
	);

}

template<class T>
void Dispatcher<T>::RemoveIMP(CallbackBase<T> *cb_)
{
	m_masterlist.remove(cb_);
	cb_->UnLinkIMP();
}


} //end of namespace RD3



#endif /*  __CALLBACK_H__ */
