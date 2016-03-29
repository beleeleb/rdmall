/*
 * Yan Pelov
 */
#ifndef __OSIT_H__
#define  __OSIT_H__

#include <fstream>

using namespace std;
namespace rd3
{

template<class P>
class OstreamIter
{
	class OstreamProxy;

public:

	explicit OstreamIter(ofstream&);
	
	OstreamProxy operator*();

	void operator++(void);
	
private:
	
	ofstream* const m_os; //const added
	
	class OstreamProxy{
	public:
		
		explicit OstreamProxy(ofstream&);

		void operator=(const P&);

	private:
		ofstream*const  m_osp;//const added

	};
	
};

template<class P>
inline OstreamIter<P>::OstreamIter(ofstream& os_):m_os(&os_)
{}

template<class P>
inline typename OstreamIter<P>::OstreamProxy OstreamIter<P>::operator*()
{
	return OstreamProxy(*m_os);
}

template<class P>
inline void OstreamIter<P>::operator++(void)
{}

template<class P>
inline OstreamIter<P>::OstreamProxy::OstreamProxy(ofstream& osp_):m_osp(&osp_)
{}

template<class P>
inline void OstreamIter<P>::OstreamProxy::operator=(const P& p_)
{
	*m_osp << p_;
}

}	

#endif /*  __OSIT_H__ */ 
