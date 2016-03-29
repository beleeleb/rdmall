#include "threadpool.h" 
#include <algorithm> //for foreach


namespace RD3
{

//---------------------------------------------------------------------------------------------------------------------------

//creates threads according to the num threads the user provided and initializes the vector accordingly
ThreadPool::ThreadPool(std::size_t numThreads_): m_numThreads(numThreads_), m_threads(m_numThreads), m_toRun(true)
{
	assert(numThreads_);
	for(size_t i = 0; i < m_numThreads; ++i)  		// The Ctor creates threads and keeps their shared ptrs inside a list
	{
		boost::shared_ptr<boost::thread> ptr(new boost::thread(&ThreadPool:: ThreadFuncIMP, this));
		m_threads.push_front(ptr);
	}
}

//---------------------------------------------------------------------------------------------------------------------------

void ThreadPool::ThreadFuncIMP()
{
	//this is a temporary vessel for the task and priority. will be destroyed upon the termination of the thread.
	boost::shared_ptr<taskpair> tmp;
	while(m_toRun)  //the thread will check the flag - and will know whether to take any more tasks to do or not
	{
		if(m_tasks.Deque(TIMER, &tmp)) //the thread activates the deque method of the waitablequeue. 100 stands for the time(in milliseconds) to timeout.
		{
			tmp->second->Do();
		}

	}


}

void ThreadPool::Add(boost::shared_ptr<TaskBase> task_, Priority p_)
{
	//boost::shared_ptr<mytask> tmp( new mytask(task_, p_)); //creates new mytask instance (passes to it user's task and his priority)
	boost::shared_ptr<taskpair> tmp( new taskpair(p_, task_)); //creates new mytask instance (passes to it user's task and his priority)
	m_tasks.Enqueue(tmp);  //enques the newly task to the queue
}


bool ThreadPool::Stop(std::size_t timeouttime_)//returns false if timeout time has passed, and true if job finished. value of timeout should be used in milliseconds unit
{
   m_toRun = false;  // the function will change the shared flag "m_toRun" to false to allow the threads finish their jobs. as a result, all threads should stop poping new tasks.
   bool okay = true;
   size_t timer = timeouttime_;

   boost::posix_time::ptime start(boost::posix_time::second_clock::local_time());

   for_each(m_threads.begin(), m_threads.end(), [&okay, &start, &timer](boost::shared_ptr<boost::thread> temp)
	{


			if(temp && (!temp->joinable()))	//the function will run foreach to try and join the threads.
            {

				temp->join();
				okay = false;	//if all the threads joined successfully the function will return true (meaning that all the jobs were finished before the time passed)
				pthread_cancel(temp->native_handle());
            }

			timer -= (boost::posix_time::second_clock::local_time() - start).total_milliseconds();
	}

	);

	return okay;	// if one or more threads didn't manage to join the function will return false.
}

void ThreadPool::SetNumThreads(std::size_t numThreads_)
{
	size_t counter = 0;
	size_t i = 0;

	for_each(m_threads.begin(), m_threads.end(), [&counter](boost::shared_ptr<boost::thread> temp)
		{
				if(temp)
	            {

					++counter;

	            }
		}
	);

	if(numThreads_ > counter) //if num of threads > num of threads in the vector
	{

		//the list will be resized to the new number of threads
		for(i = 0; i < (numThreads_ - counter); ++i) 	// the function will create new threads using threadpool's class - thread functor.
		{
			boost::shared_ptr<boost::thread> ptr(new boost::thread(&ThreadPool:: ThreadFuncIMP, this)); //a foreach will push the new thread ptrs to the list.
			m_threads.push_front(ptr);

		}

		return;

	}


	if(numThreads_ == counter)
	{
		return; //case the number of requested threads is equal to the number of current threads.
	}

	if(numThreads_ < counter)
	{
		boost::shared_ptr<TaskBase> ptr(new MethodTask<ThreadPool, int, void>(this, 7, &ThreadPool::ToxicAppleIMP));

		for(i = 0; i < (counter - numThreads_); ++i)
		{
			Add(ptr, HIGH);
		}

		//create toxic tasks that will halt the threads that take it (according to the requested number of threads by the user).

		//Invoke the Add function to add these toxic tasks into the queue and set their priority to the highest so they will be picked up first by the threads.
	}

	CleanIMP();

	return;
}

void ThreadPool::ToxicAppleIMP(int x_)
{
	pthread_cancel(pthread_self());
}

void ThreadPool::CleanIMP()
{

	for_each(m_threads.begin(), m_threads.end(), [](boost::shared_ptr<boost::thread> temp)
			{
					if(temp && !temp->joinable())
		            {
						temp.reset();
		            }
			}
	);

}
}
