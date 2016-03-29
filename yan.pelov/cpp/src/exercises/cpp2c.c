/*
 * cpp2c.c
 *
 *  Created on: Feb 28, 2015
 *      Author: galizorea
 */
#include <stdio.h>
#include <stdlib.h>
static int s_count = 0;

typedef struct Animal
{
	int m_id;
	void (**m_vt)(struct Animal*);
} Animal;

void Animal__Ctor(Animal * ani)
{
	ani->m_id = ++s_count;
	printf("Animal::Ctor() %d\n", ani->m_id);
}

void Animal__CCtor(Animal * ani)
{
	ani->m_id = ++s_count;
	printf("Animal::CCtor() %d\n", ani->m_id);
}

void Animal__Display(Animal * ani)
{
	printf("Animal::Display() : %d\n", ani->m_id);
}

void Animal__Dtor(Animal* ani)
{
	--s_count;
	printf("Animal::Dtor()%d\n", ani->m_id);
}

void PrintCount()
{
	printf("s_count: %d\n", s_count);
}

int GetID(Animal* ani)
{
	return ani->m_id;
}

void * Animal_vt [2] = {&Animal__Dtor, &Animal__Display};

typedef struct Centipede
{
	Animal m_papa;
	int m_numLegs;
} Centipede;

void Centipede__Dtor(Centipede * cen)
{
	cen->m_papa.m_vt = Animal_vt;

	printf("Centipede::dtor()\n");
	Animal__Dtor(&cen->m_papa);
}

void Centipede__Display(Centipede * cen)
{
	printf("Centipede::Display() ID:%d  num legs:%d\n", GetID(&cen->m_papa), cen->m_numLegs);
}

void BuyShues(Centipede * cen)
{
	printf("Centipede::BuyShues() ID:%d\n", GetID(&cen->m_papa));
}

void* Centipede_vt [3] = {&Centipede__Dtor, &Centipede__Display, &BuyShues};

void Centipede__Ctor(Centipede * cen)
{
	Animal__Ctor(&cen->m_papa);
	cen->m_papa.m_vt = Centipede_vt;
	cen->m_numLegs = 46;
	printf("Centipede::Ctor()\n");
}

void Centipede__CCtor(Centipede * cen, Centipede * new)
{
	Animal__CCtor(&new->m_papa);
	cen->m_papa.m_vt = Centipede_vt;
	new->m_numLegs = 46;
	printf("Centipede::CCtor()\n");
}

typedef struct Animal Squirl;

void Squirl__Dtor(Squirl * squ)
{
	squ->m_vt = Animal_vt;

	printf("Squirl::dtor()\n");
	Animal__Dtor(squ);
}

void Squirl__Display(Squirl * squ)
{
	printf("Squirl::Display() ID:%d\n", GetID(squ));
}

void* Squirl_vt [2] = {&Squirl__Dtor, &Squirl__Display};

void Squirl__Ctor(Squirl * squ)
{
	Animal__Ctor(squ);
	squ->m_vt = Squirl_vt;
	printf("Squirl::Ctor()\n");
}

void Squirl__CCtor(Squirl * squ, Squirl * new)
{
	Animal__CCtor(new);
	squ->m_vt = Squirl_vt;
	printf("Squirl::CCtor()\n");
}

void Foo1(Animal * ani)
{
	ani->m_vt[1](ani);
}

void Foo2(){
	PrintCount();
}

void Foo3(int i, Animal * ani)
{
	Centipede ret;
	Centipede__Ctor(&ret);
	printf("Foo(int i)\n");
	Centipede__Display(&ret);
	Animal__CCtor(ani);
	Centipede__Dtor(&ret);
}

int main()
{
	Centipede c;
	
	Centipede__Ctor(&c);

	Foo1(&c.m_papa);
	Animal tmp;
	Foo3(3, &tmp);

	Animal__Display(&tmp);
	Animal__Dtor(&tmp);
	
	Animal * arr[3];
	
	arr[0] = malloc(sizeof(Centipede));
	Centipede__Ctor(*(arr+0));
	
	arr[1] = malloc(sizeof(Squirl));
	Squirl__Ctor(*(arr+1));
	
	arr[2] = malloc(sizeof(Centipede));
	Centipede__Ctor(*(arr+2));
	
	int i;
	
	for(i = 0; i < 3; ++i)
	{
		(arr[i]->m_vt[1])(arr[i]);
		
	}
	
	for(i = 0; i < 3; ++i)
	{
		(arr[i]->m_vt[0])(arr[i]);
		free(arr[i]);
	}
	
	Animal arr2[3];
	Centipede__Ctor(&arr2[0]);
	Animal__CCtor(&arr2[0]);
	Centipede__Dtor(&arr2[0]);
	
	//Squirl__Ctor(&arr2[1]);
	//Animal__CCtor(&arr2[1]);
	//Squirl__Dtor(&arr2[1]);
	
	//Animal__Ctor(&arr[2]);
	
	
	
	
	//Centipede__Dtor(&c);

	return 0;
}

