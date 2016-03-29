/*
 *   A thread pool program.
 *   Yan 8/3/15
 *   Reviewed By: Alex
 *
 *	The program implements a thread pool.
 * 	It uses a waitable queue to handle tasks insetred by the client.
 *
 */

#ifndef __THREADPOOL_H__
#define  __THREADPOOL_H__

#include <memory> //for shared_ptr
#include <list> //for list
#include "waitablequeue.h"

namespace RD3
{

class TaskBase: private Unassignable
{

public:

	virtual ~TaskBase(){};

private:

	virtual void Do() = 0; //Warning!! Must be implemented in the derived classes

	friend class ThreadPool;

}; //end of class TaskBase

template <class C, class P, class R> //C for Class, P for Param, R for Return
class MethodTask:  public TaskBase
{

public:

	explicit MethodTask(C* obj_, P param_, R(C::*method_)(P));

private:

	C* m_obj;
	P m_param;
	R(C::*m_method)(P);

	virtual void Do() //Invoke the method function provided by the client.
	{
		(*(m_obj).*m_method)(m_param);
	}

}; //end of class TaskBase

template <class C, class P, class R> //C for Class, P for Param, R for Return
class ReturnerTask:  public TaskBase
{

public:

	explicit ReturnerTask(C* obj_, P param_ ,R(C::*method_)(P));
	bool IsDone() const;
	R GetRet() const;

private:

	C* m_obj;
	P m_param;
	R(C::*m_method)(P);
	R m_r;
	bool m_isFinished;

	virtual void Do() //Invoke the method function provided by the client.
	{
		m_r = (*(m_obj).*m_method)(m_param); //keep the return value of the method function to a private member data
		m_isFinished = true; //change the flag that indicates that the task has been finished to true.
	}

}; //end of class ReturnerTask


template <class C, class P, class R> //C for Class, P for Param, R for Return
class WaitableTask:  public TaskBase
{
public:

	explicit WaitableTask(C* obj_, P param_, R(C::*method_)(P));
	bool Wait(std::size_t timeOut_) const; //give seconds units
	R GetRet() const;

private:

	C* m_obj;
	R(C::*m_method)(P);
	P m_param;
	R m_r;
	bool m_isFinished;

virtual void Do() //Invoke the method function provided by the client.
{
	m_r =(*(m_obj).*m_method)(m_param);
	m_isFinished = true;
}


};//end of class WaitableTask

class ThreadPool: private Uncopyable
{
public:

	enum Priority{HIGH = 2, MED, LOW};

	explicit ThreadPool(std::size_t numThreads_);
	//generated Dtor

	void Add(boost::shared_ptr<TaskBase> task_, Priority p_ = MED);
	bool Stop(std::size_t timeouttime_); //returns false if timeout time has passed, and true if job finished. value of timeout should be used in seconds unit

	int GetPriority() const;

	void SetNumThreads(std::size_t numThreads_);

private:

	static const size_t TIMER = 100;

	typedef std::pair<Priority, boost::shared_ptr<TaskBase>> taskpair;

	class CompIMP
	{

	public:
	  bool operator() (boost::shared_ptr<taskpair> x, boost::shared_ptr<taskpair> y)  {
		  return x->first <= y->first;
	  }

	};


	void ThreadFuncIMP();

	void ToxicAppleIMP(int x);

	void CleanIMP();

	std::size_t m_numThreads;

	std::list<boost::shared_ptr<boost::thread>> m_threads;

	bool m_toRun;

	WaitableQueue<boost::shared_ptr<taskpair>, CompIMP> m_tasks;

}; //end of class ThreadPool

/*********************************************************************************************************************/

template <class C, class P, class R>
MethodTask<C, P, R>::MethodTask(C* obj_, P param_, R(C::*method_)(P)):m_obj(obj_), m_param(param_), m_method(method_) //methodtask Ctor
{}

template <class C, class P, class R>
ReturnerTask<C, P, R>::ReturnerTask(C* obj_, P param_, R(C::*method_)(P)):m_obj(obj_), m_param(param_), m_method(method_), m_isFinished(false) //returntask Ctor
{}

template <class C, class P, class R>
bool ReturnerTask<C, P, R>::IsDone() const
{
	return m_isFinished; //return to the client the value of the flag that indicates whether the task has been finished or not.
}

template <class C, class P, class R>
R ReturnerTask<C, P, R>::GetRet() const
{
	return m_r; //return to the client the return value of the method function.
}


template <class C, class P, class R>
WaitableTask<C, P, R>::WaitableTask(C* obj_, P param_, R(C::*method_)(P)):m_obj(obj_), m_param(param_), m_method(method_), m_isFinished(false) //waittask Ctor
{}

template <class C, class P, class R>
bool WaitableTask<C, P, R>::Wait(std::size_t timeOut_) const
{
	if(m_isFinished) //the function will check whether the flag that indicates that the task has been finished is true.
	{
		return true; //if true it will return with a true value.
	}
    
	sleep(timeOut_);//if not, it will repeat the test once again after going to sleep for the period of time set by the client.

	return m_isFinished;//if the flag hasn't been yet changed to true, it will return false.
}

template <class C, class P, class R>
R WaitableTask<C, P, R>::GetRet() const
{
	return m_r; //return to the client the return value of the method function.
}

}//end of NS RD3
#endif /*  __THREADPOOL_H__ */
