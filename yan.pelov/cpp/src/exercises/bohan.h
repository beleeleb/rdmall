#ifndef __BOHAN_H__
#define  __BOHAN_H__

#include <vector>
#include <boost/thread/mutex.hpp> //mutex of threads
#include <boost/thread/thread.hpp> //for the use of threads
#include <boost/interprocess/sync/interprocess_semaphore.hpp> //for semaphore



namespace RD3
{
using namespace std;

template <class D>
class queue
{
public:
	explicit queue(size_t size_ = 5);
	void enque(D data_);
	D deque();

	std::vector<D> m_que;

private:
	size_t m_used;
	size_t m_start;
	size_t que_sz;
	boost::interprocess::interprocess_semaphore m_semwr;
	boost::interprocess::interprocess_semaphore m_semrd;
	boost::mutex m_mutex;


};
}
#endif /*  __BOHAN_H__ */
