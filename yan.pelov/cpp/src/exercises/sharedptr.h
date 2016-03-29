#ifndef __SHAREDPTR_H__
#define  __SHAREDPTR_H__

#ifndef __SHAREDPTR_H__
#define __SHAREDPTR_H__

/* Debug function macro */
#ifdef DEBUG
#define DEBUG_ONLY(x) x
#else
#define DEBUG_ONLY(x)
#endif

#include <cctype> //for size_t
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

template <class T>
class SharedPtr
{
public:
	explicit SharedPtr(T* ptr_ = 0); //ctor, ptr_ default init to null
	explicit SharedPtr(const SharedPtr& ptr_); //ctor overload, init via another shp

	~SharedPtr(); //dtor
	SharedPtr(const SharedPtr& o_); //cctor
	SharedPtr& operator=(const SharedPtr& o_);

	T operator*()const;
	T* operator->()const;

	template <class O>
	SharedPtr(const SharedPtr<O>& o_); //cctor of shp

	template <class O>
	inline SharedPtr& operator=(const SharedPtr<O>& o_); ////ator from another shp

private:
	boost::mutex mutex; //for locking
	T* m_ptr;
	size_t* m_count;


	void CopyIMP(const SharedPtr& o_);
	void DelIMP();

};

template <class T>
inline SharedPtr<T>::SharedPtr(T* ptr_):m_ptr(ptr_), m_count(new size_t(1))
{
}

template <class T>
inline SharedPtr<T>::SharedPtr(const SharedPtr& ptr_)
{
	boost::mutex::scoped_lock scoped_lock(mutex); //apply lock
	++(*o_.m_count); //increment counter;
	CopyIMP(ptr_);
}

template <class T>
inline SharedPtr<T>::~SharedPtr()
{

}

template <class T>
inline SharedPtr<T>::SharedPtr(const SharedPtr& o_)
{
}

template <class T>
inline SharedPtr& SharedPtr<T>::operator=(const SharedPtr& o_)
{

}

template <class T>
inline T operator*()const;
	T* operator->()const;

	template <class O>
	SharedPtr(const SharedPtr<O>& o_); //cctor of shp

	template <class O>
	inline SharedPtr& operator=(const SharedPtr<O>& o_); ////ator from another shp*/

#endif /*  __SHAREDPTR_H__ */
