/*
 * waitablequeue.h
 *
 *  Created on: Mar 8, 2015
 *      Author: yan
 *      Reviewed by:Aharon
 */

#ifndef __WAITABLEQUEUE_H__
#define __WAITABLEQUEUE_H__

#include <queue> //for prio queue
#include <functional>   // std::less_equal
#include <boost/thread/mutex.hpp> //mutex of threads
#include <boost/thread/thread.hpp> //for thread
#include <boost/interprocess/sync/interprocess_semaphore.hpp> //for semaphore
#include "lockthrow.h"

namespace RD3
{

//This utility allows holding items in a waitable priority queue. user should pass a Type(T) and a compare function(COMP)
template <class T, class COMP=std::less_equal<T>> //T has to be copyable and comparable, if T isn't comparbile, the user must provide his own compare function
class WaitableQueue: private Uncopyable
{

public:
	explicit WaitableQueue();
	//Using generated Dtor

	void Enqueue(T t_);  //throw lock

	//Deque returns true if a task finished and false if it has't finished on time. Warning! might throw exceptions
	//timeout_ should be in milliseconds
	//t_ shouldn't be NULL, the task that will be dequed, will be copied to t_
	bool Deque(std::size_t timeout_ , T* t_);

private:

	std::priority_queue< T, std::vector<T>, COMP > m_queue;
	boost::timed_mutex m_mutex;
	boost::interprocess::interprocess_semaphore m_sem;

	class NoTasks: public std::runtime_error
	{
	public:
		NoTasks(const std::string& error);
	};
};

/*********************************WaitableQueue Implementation*************************************************************************************/

template <class T, class COMP>
WaitableQueue<T, COMP>::WaitableQueue(): m_sem(0)
{}

template <class T, class COMP>
void WaitableQueue<T, COMP>::Enqueue(T t_) //this function allows adding items to the queue (shared pointers of tasks in our case).
{
	LockrThrower tmp(&m_mutex, &m_sem, 0);

	m_queue.push(t_);

	m_sem.post();

}

template <class T, class COMP>
bool WaitableQueue<T, COMP>::Deque(std::size_t timeout_, T* t_)
{

	boost::posix_time::ptime time = boost::get_system_time()+ boost::posix_time::milliseconds(timeout_);

	if(!m_sem.timed_wait(time)) //timed semaphore - thread will wait on the semaphore for a definite period of time, false if time passed and have acquired, true if acquired successfully
	{
		return false;
	}

	LockrThrower(&m_mutex, &m_sem, 1);

	if(m_queue.empty()) //if lock was aquired - check that there are tasks in queue
	{
		throw NoTasks("No tasks in queue!\n");
		return false;
	}

	*t_ = m_queue.top(); //if everything is okay, keep the task in the dedicated pointer.
	m_queue.pop(); //pop out the task out of the queue

	return true;
}

template <class T, class COMP>
WaitableQueue<T, COMP>::NoTasks::NoTasks(const std::string& error): runtime_error(error)
{}

}//end of NS RD3

#endif /* __WAITABLEQUEUE_H__ */


