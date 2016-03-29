#include <iostream>
#include "singleton.h"

using namespace RD3;
using namespace std;

int main(int argc,char **argv,char **envp)
{
	/*class Foo f;
	class Bar b;*/

	//MS * p = NULL;
	/*DS& p9 = GetS<DS>();
	p9.Tree();
	MS& p3 = GetS<MS>();
	p3.Flower();

	HS& p6 = GetS<HS>();
	p6.Animal();*/

	//int i;

	/*Flower& f[1000];

	for(i = 0; i < 1000; ++i)
	{
		f[i] = Singleton<Flower>::Inst();
		f[i]->PrintFlower();
	}*/

	//Flower& f[2] = {Singleton<Flower>::Inst(), Singleton<Flower>::Inst()};



	Flower& g = Singleton<Flower>::Inst();
	g.PrintFlower();

	//flower.Inst();

	//flower.PrintFlower();

	//Flower p1 = Inst<Flower>();
//	DelS<DS>(p8);



	//DelS<DS>(p8);

	//f.Print();
	//b.Print();

	//DelS(p);
	return 0;
}
