#include <iostream>
#include "bohan.h"

namespace RD3
{
template <class D>
queue<D>::queue(size_t size_):m_used(0), m_start(0), que_sz(size_)
{
	m_que.resize(que_sz);
}

template <class D>
void queue<D>::enque(D data_)
{
	if(m_used < que_sz)
	{
		m_que[(m_start + m_used) % que_sz] = data_;

		++m_used;
	}
}

template <class D>
D queue<D>::deque()
{
	D data;

	if(m_used)
	{
		data = m_que[m_start];
		m_que[m_start] = 0xDEADBEEF;
		m_start = (m_start + 1) % que_sz;
		--m_used;
	}

	return data;

}
}

using namespace RD3;
int main(int argc,char **argv,char **envp) 
{
//	size_t num = 4;
	queue<int> myque;
	myque.enque(100);
	myque.enque(200);
	myque.deque();
	myque.enque(700);
	myque.enque(300);
	myque.deque();
	myque.enque(400);

	for(size_t i = 0; i < myque.m_que.size(); ++i)
	{
		std::cout << myque.m_que[i] << std::endl;
	}

	return 0;

}
