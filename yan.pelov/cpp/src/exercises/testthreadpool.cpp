/*******************************************************************************
Name: Noam Moshe
Date:
Used:
File: N/A
*******************************************************************************/


#include <iostream>

#include "threadpool.h"

using namespace std;
using namespace RD3;

/*************************/
/*** test class ***/

class NoamClass
{
public:

	int function1(int param_)
	{
		cout << "in function1" << param_ << "\n";
		return 7;
	}

	int function2(int param_)
	{
		while(1)
		{
			cout << "in function2 " << param_ << "\n";
			sleep(1);
		}
		return 11;
	}

private:
};

class Apple
{
public:
	int Print(int a){

		std::cout << "Hey Apple!" << std::endl;
		return 0;
	};

	int Sleep(int a)
	{
		while(1)
		{
		usleep(100000);
		std::cout << "i am still here" << std::endl;
		}

		return 0;
	};
};

/***********************/
/*** main function ***/

int main(int argc,char **argv,char **envp)
{
	cout <<"Hello Code monkey\n";


	/***************************************************************************/

	/* Test 1 - insert task to thredpoll
	 *
	 * #1 Create Threadpool
	 * #2 Create task
	 */


/*	// #1
	ThreadPool myThreadpool1(3);

	// #2
	// class who wants thredpool service
	NoamClass myclass;


	//explicit ReturnerTask(C* obj_, P param_ ,R(C::*method_)(P));
	// Create task
	boost::shared_ptr<TaskBase> sp(new ReturnerTask<NoamClass, int, int > (&myclass, 666, &NoamClass::function1));


	// add task
		myThreadpool1.Add(sp);
		sleep(3);

		myThreadpool1.Stop(3);


	// add task*/

	/***************************************************************************/

	/* Test 2 - SetNumThread down
	 *
	 * #1 Create Threadpool
	 */


/*	// #1
	ThreadPool myThreadpool2(10);

	// #2
	// class who wants thredpool service
	NoamClass myclass;

	// Create task
	boost::shared_ptr<TaskBase> sp(new ReturnerTask<NoamClass, int, int > (&myclass, 666, &NoamClass::function1));
	// add task
	myThreadpool2.Add(sp);

	myThreadpool2.SetNumThreads(2);

	sleep(1);

	myThreadpool2.Stop(5);
*/
	/**************************************************************************/

	/* Test 3 - SetNumThread up
	 *
	 * #1 Create Threadpool
	 */

/*
	// #1
	ThreadPool myThreadpool3(3);

	// #2
	// class who wants thredpool service
	NoamClass myclass;

	// Create task
	boost::shared_ptr<TaskBase> sp(new ReturnerTask<NoamClass, int, int > (&myclass, 666, &NoamClass::function1));
	// add task
	myThreadpool3.Add(sp);

	myThreadpool3.SetNumThreads(50);

	myThreadpool3.Stop(15);*/

	/**************************************************************************/

	/* Test 4 - ReturnTask check
	 *
	 * #1 Create Threadpool
	 */

/*
	// #1
	ThreadPool myThreadpool4(3);

	// #2
	// class who wants thredpool service
	NoamClass myclass;

	// Create task
	ReturnerTask< NoamClass,int,int>* ptr=(new ReturnerTask<NoamClass, int, int >(&myclass, 666, &NoamClass::function1));

	boost::shared_ptr<TaskBase> sp(ptr);
	// add task
	myThreadpool4.Add(sp);



	while (! ptr->IsDone() )
	{
		cout <<"waiting...\n";
		sleep(1);
	}
	cout <<"return value:" <<ptr->GetRet() <<"\n";
	myThreadpool4.Stop(2);*/

	/**************************************************************************/


	/**************************************************************************/

	/* Test 6 - detache task to threadpoll
	 *
	 * #1 Create Threadpool
	 * #2 Create task
	 */


	// #1
	ThreadPool myThreadpool6(10);

	// #2
	// class who wants thredpool service
	NoamClass myclass;

	// Create task
	boost::shared_ptr<TaskBase> sp(new ReturnerTask<NoamClass, int, int > (&myclass, 666, &NoamClass::function2));
	// add task
	myThreadpool6.Add(sp);

	sleep(3);

	myThreadpool6.SetNumThreads(5);


	myThreadpool6.Stop(3);




	/**************************************************************************/
sleep(3);
	cout <<"**********************************\n";
	return (0);
}








/*#include <iostream>
#include <unistd.h>
#include "threadpool.h"

using namespace RD3;
class Apple
{
public:
	void Print(int a){std::cout << "Hey Apple!" << std::endl;};

	void Sleep(int a){while(1){
		usleep(100000);
		std::cout << "i am still here" << std::endl;}};
};

int main(int argc,char **argv,char **envp) 
{

	ThreadPool mypool(3);

	Apple p;

	boost::shared_ptr<TaskBase> ptr(new MethodTask<Apple, int, void>(&p, 7, &Apple::Print));

	boost::shared_ptr<TaskBase> ptr2(new MethodTask<Apple, int, void>(&p, 7, &Apple::Sleep));


	mypool.Add(ptr);
	mypool.Add(ptr2);
	mypool.Add(ptr);

	sleep(2);



	//mypool.SetNumThreads(40);

	//mypool.Add(ptr2);
	//mypool.Add(ptr);

	//mypool.SetNumThreads(20);

	//mypool.SetNumThreads(20);

	mypool.Stop(50);
	sleep(3);



	return 0;
}
*/
