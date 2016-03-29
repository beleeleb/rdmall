/*
 * mydefs.h
 *
 *  Created on: Feb 15, 2015
 *      Author: guy
 */

#ifndef _MYDEFS_H_
#define _MYDEFS_H_

#ifdef DEBUG 				//to be moved to a seprate utils macro
#define DEBUG_ONLY(x) x
#else
#define DEBUG_ONLY(x)
#endif

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

namespace RD3
{

class Uncopyable
{

protected:

	Uncopyable() {}
	~Uncopyable() {}

private:

	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);

};


class Unassignable
{

protected:

	Unassignable() {}
	~Unassignable() {}

private:
	Unassignable& operator=(const Unassignable&);

};


}

#endif /* EXERCISES_MYDEFS_H_ */
