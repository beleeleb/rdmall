/*
 * Yan 24/2/15
 * Reviewed by: Tal
 *
 *
 */
#ifndef __FACTORY_H__
#define  __FACTORY_H__

#include <tr1/memory>//for shared_ptr
#include <map> //for map
#include <exception> //for throwing exception
#include <stdexcept> //for logic_error
#include <iostream> //for cerr
#include <cassert> //for debug mode
#include "mydefs.h"

namespace RD3
{
/* T(Type) has to be polymorphic and include a polymorphic << operator method
 * K(Key) has to be copyable & Compatebile
 * D(Data) has to be copyable
 */
template <class T, class K, class D>
class Factory: private Uncopyable
{

public:
	//using the generated Ctor & Dtor

	void Add(T*(*func_)(D), K key_);

	std::tr1::shared_ptr<T> Create(K key_, D data_) const;

	class IterNotFound: public std::runtime_error
	{

	public:
		explicit IterNotFound(const std::string& error);

	};

private:

	std::map< K, T*(*)(D) > m_funcs;
};

template <class T, class K, class D>
inline Factory<T,K,D>::IterNotFound::IterNotFound(const std::string& error):runtime_error(error)
{}

template <class T, class K, class D>
void Factory<T,K,D>::Add(T*(*func)(D), K key_)
{
	assert(func && "pointer shouldn't be null");
	assert((m_funcs.end() == m_funcs.find(key_)) && "key wasn't found");

	m_funcs[key_] = func;
}

template <class T, class K, class D>
std::tr1::shared_ptr<T> Factory<T,K,D>::Create(K key_, D data_) const
{

	typename std::map< K, T*(*)(D) >::const_iterator it = m_funcs.find(key_);

	if(it == m_funcs.end())
	{
		throw IterNotFound("Iter not found at Create()");
	}

	return std::tr1::shared_ptr<T> (it->second(data_));
}


} //end of NS RD3
#endif /*  __FACTORY_H__ */
