/*
 * lockerthrower.h
 *
 *  Created on: Mar 9, 2015
 *      Author: guy
 */

#ifndef __LOCKTHROW_H__
#define __LOCKTHROW_H__

#include <stdexcept>
#include <string>
#include <boost/chrono/chrono.hpp>
#include <boost/thread/mutex.hpp> //mutex of threads
#include <boost/interprocess/sync/interprocess_semaphore.hpp> //for semaphore

#include "mydefs.h" //for debug purposes and uncopyable

namespace RD3
{

class LockrThrower
{
public:
	LockrThrower(boost::timed_mutex *mtx_, boost::interprocess::interprocess_semaphore* sem_, size_t flag_);
	~LockrThrower();


private:

	class NotAquired: public std::runtime_error
	{
	public:
		NotAquired(const std::string& error);
	};


	static const std::size_t timer = 200;

	boost::timed_mutex* m_mutex;
	boost::interprocess::interprocess_semaphore* m_sem;
};


/***************/
inline LockrThrower::LockrThrower(boost::timed_mutex* mtx_, boost::interprocess::interprocess_semaphore* sem_, size_t flag_): m_mutex(mtx_), m_sem(sem_)
{
	if(!m_mutex->timed_lock( boost::get_system_time()+ boost::posix_time::milliseconds(timer)))
	{
		if(flag_)
		{
			m_sem->post();
		}

		throw NotAquired("Lock Not Aquired!\n");
	}
}

inline LockrThrower::~LockrThrower()
{
	m_mutex->unlock();
}


inline LockrThrower::NotAquired::NotAquired(const std::string& error): runtime_error(error)
{}


}

#endif /* __LOCKTHROW_H__ */
