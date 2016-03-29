/*
 * Yan 24/2/15
 * Reviewed by: Tal
 *
 *
 */

#ifndef __SERIALIZER_H__
#define  __SERIALIZER_H__

#include <typeinfo> //for type_info
#include <cstring> //for strcmp
#include "factory.h"
#include "mydefs.h"

namespace RD3
{
/*
 * T(Type) polymorphic, C(concrete) must be derived and must have a ctor that receives istream and has  << & >> ops
 *
 */

template <class T>
class Serializer: private Uncopyable
{
public:
	//using generated Ctor & Dtor

	void Serialize(std::ostream& o_, const T&) const;

	std::tr1::shared_ptr<T> Deserialize(std::istream& i_) const; //THROWS BadInput exception

	template<class C>
	void Add();

	class BadInput: public std::runtime_error //exception
	{

	public:
		explicit BadInput(const std::string& error);

	};

private:

	template <class C>
	static T* MakeIMP(std::istream& i_);

	Factory< T, const std::string, std::istream& > m_fact;
};

template <class T>
inline void Serializer<T>::Serialize(std::ostream& o_, const T& t_) const
{
	o_ << std::string(typeid(t_).name()) << ' ' << t_ << ' ' << "VVVVV";
}

template <class T>
inline std::tr1::shared_ptr<T> Serializer<T>::Deserialize(std::istream& i_) const
{

	std::string name;

	i_ >> name;

	std::tr1::shared_ptr<T> ret = m_fact.Create(name , i_);

	char buf[6];

	i_ >> buf;
	i_ >> buf;

	buf[5] = 0;

	if(0 != strcmp(buf, "VVVVV"))
	{
		throw BadInput("Bad Input!");
	}

	return ret;
}


template<typename T>
inline Serializer<T>::BadInput::BadInput(const std::string& error):runtime_error(error)
{}

template <class T>
template<class C>
inline T* Serializer<T>::MakeIMP(std::istream& i_)
{
	return new C(i_);
}

template <class T>
template<class C>
inline void Serializer<T>::Add()
{
	m_fact.Add(&MakeIMP<C>, std::string(typeid(C).name()));
}

} //end of NS RD3
#endif /*  __SERIALIZER_H__ */
