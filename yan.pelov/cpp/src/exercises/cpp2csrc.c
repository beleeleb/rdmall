/*
 ============================================================================
 Name        : killmeplease.c
 Author      : Yan
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Animal
{
	int m_id;
	void(**m_vt)(struct Animal*);
} Animal;

static int s_count;

void Animal__Dtor(Animal* ani)
{
	--s_count;
	printf("Animal::Dtor() %d\n", ani->m_id);
}

void Animal__Display(Animal* ani)
{
	printf("Animal::Dispaly() %d\n", ani->m_id);
}

void(*animal_vt[2])(Animal*) = {&Animal__Dtor, &Animal__Display};

void Animal__Ctor(Animal* ani)
{
	ani->m_id = ++s_count;
	ani->m_vt = animal_vt;
	printf("Animal::Ctor() %d\n", ani->m_id);
}

void Animal__CCtor(Animal* curr, Animal* const new)
{
	curr->m_id = ++s_count;
	curr->m_vt = animal_vt;
	printf("Animal::CCtor() %d\n", curr->m_id);
}

static void PrintCount(void)
{
	printf("s_count: %d\n", s_count);
}

int GetID(Animal * ani)
{
	return ani->m_id;
}

typedef struct Centipede
{
	Animal m_papa;

	int m_numLegs;
} Centipede;

void Centipede__Dtor(Centipede* cen)
{
	printf("Centipede::dtor()\n");
	cen->m_papa.m_vt = animal_vt;
	Animal__Dtor(&(cen->m_papa));
}

void Centipede__Display(Centipede* cen)
{
	printf("Centipede::Dispaly() %d  num legs: %d\n", GetID(&(cen->m_papa)), cen->m_numLegs);
}

void BuyShues(Centipede* cen)
{
	printf("Centipede::BuyShues() ID:\n %d", GetID(&(cen->m_papa)));
}

void(*centipede_vt[3])(Centipede*) = {&Centipede__Dtor, &Centipede__Display, &BuyShues};

void Centipede__Ctor(Centipede* cen)
{
	Animal__Ctor(&(cen->m_papa));
	cen->m_papa.m_vt = centipede_vt;
	cen->m_numLegs = 46;
	printf("Centipede::Ctor()\n");
}

void Centipede__CCtor(Centipede* curr, Centipede* new)
{
	Animal__CCtor(&(curr->m_papa), &(new->m_papa));
	curr->m_papa.m_vt = centipede_vt;
	curr->m_numLegs = new->m_numLegs;
	printf("Centipede::CCtor()\n");
}

typedef struct Animal Squirl;

void Squirl__Dtor(Squirl* squ)
{
	printf("Squirl::dtor()\n");
	squ->m_vt = animal_vt;
	Animal__Dtor(squ);

}

void Squirl__Display(Squirl* squ)
{
	printf("Squirl::Display() ID: %d\n", GetID(squ));
}

void(*squ_vt[2])(Squirl*) = {&Squirl__Dtor, &Squirl__Display};

void Squirl__Ctor(Squirl* squ)
{
	Animal__Ctor(squ);
	squ->m_vt = squ_vt;
	printf("Squirl::Ctor()\n");
}

void Squirl__CCtor(Squirl* curr, Squirl* new)
{
	Animal__CCtor(curr, new);
	curr->m_vt = squ_vt;
	printf("Squirl::CCtor()\n");
}

void Foo(Animal* a)
{
	a->m_vt[1](a);
}

void FooP()
{
	PrintCount();
}

void FooAnimal(int i, Animal * ani)
{
	Centipede ret;
	Centipede__Ctor(&ret);

	printf("Foo(int i)\n");
	Centipede__Display(&ret);

	Animal__CCtor(ani, &ret);
	Centipede__Dtor(&ret);
}

void FiFi(Centipede c)
{
	Centipede__Display(&c);
}

typedef struct LegendaryAnimal
{
	Animal m_papa;
	Animal *m_a1;
	Animal *m_a2;
	Centipede m_c;
	Squirl m_sq;

} LegendaryAnimal;


void LegendaryAnimal__Dtor(LegendaryAnimal* leg)
{

	(leg->m_a1->m_vt)[0](leg->m_a1);
	free(leg->m_a1);

	(leg->m_a2->m_vt)[0](leg->m_a2);
	free(leg->m_a2);

	Squirl__Dtor(&(leg->m_sq));

	Centipede__Dtor(&(leg->m_c));

	leg->m_papa.m_vt = animal_vt;
	Animal__Dtor(&(leg->m_papa));
}

void LegendaryAnimal__Display(LegendaryAnimal* leg)
{
	leg->m_a1->m_vt[1](leg->m_a1);
	leg->m_a2->m_vt[1](leg->m_a2);

	Centipede__Display(&(leg->m_c));
	Squirl__Display(&(leg->m_sq));
}

void(*LegendaryAnimal_vt[2])(LegendaryAnimal*) = {&LegendaryAnimal__Dtor, &LegendaryAnimal__Display};

void LegendaryAnimal__Ctor(LegendaryAnimal* leg)
{
	Animal__Ctor(&(leg->m_papa));

	leg->m_a1 = malloc(sizeof(Centipede));
	Centipede__Ctor(leg->m_a1);

	leg->m_a2 = malloc(sizeof(Squirl));
	Squirl__Ctor(leg->m_a2);

	Centipede__Ctor(&(leg->m_c));
	Squirl__Ctor(&(leg->m_sq));

	leg->m_papa.m_vt = LegendaryAnimal_vt;
}

void LegendaryAnimal__CCtor(LegendaryAnimal* curr, LegendaryAnimal* new)
{

	Animal__CCtor(&(curr->m_papa), &(new->m_papa));

	curr->m_a1 = malloc(sizeof(Centipede));
	Centipede__CCtor(curr->m_a1, new->m_a1);

	curr->m_a2 = malloc(sizeof(Squirl));
	Squirl__CCtor(curr->m_a2, new->m_a2);

	Centipede__CCtor(&(curr->m_c), &(new->m_c));
	Squirl__CCtor(&(curr->m_sq), &(new->m_sq));

	curr->m_papa.m_vt = LegendaryAnimal_vt;

}

int main(void) {

	int i;

	Centipede cen;
	Centipede__Ctor(&cen);

	Foo(&cen);
	Animal a;
	FooAnimal(3, &a);

	Animal__Display(&a);
	Animal__Dtor(&a);


	Animal * array[3];

	array[0] = malloc(sizeof(Centipede));
	Centipede__Ctor(array[0]);

	array[1] = malloc(sizeof(Squirl));
	Squirl__Ctor(array[1]);

	array[2] = malloc(sizeof(Centipede));
	Centipede__Ctor(array[2]);


	for(i = 0; i < 3; ++i)
	{
		array[i]->m_vt[1](array[i]);
	}

	for(i = 0; i < 3; ++i)
	{
		array[i]->m_vt[0](array[i]);
		free(array[i]);
	}

	Animal array2[3];

	Centipede cen2;
	Squirl sq2;

	Centipede__Ctor(&cen2);
	Animal__CCtor(array2 + 0, &cen2);
	Centipede__Dtor(&cen2);

	Squirl__Ctor(&sq2);
	Animal__CCtor(array2 + 1, &sq2);
	Squirl__Dtor(&sq2);

	Animal__Ctor(array2 + 2);


	for(i = 0; i < 3; ++i)
	{
		Animal__Display(array2+i);
	}

	PrintCount();

	Centipede c2;

	Centipede__Ctor(&c2);

	PrintCount();

	Centipede arr3[4];

	for(i = 0; i < 4; ++i)
	{
		Centipede__Ctor(arr3 + i);
	}

	Squirl *arr4 = (1 + (size_t*)malloc(sizeof(size_t) + (4 * sizeof(Squirl))));

	*((size_t*)arr4 - 1) = 4;

	for(i = 0; i < *((size_t*)arr4 - 1); ++i)
	{
		Squirl__Ctor(arr4 + i);
	}

	for(i = *((size_t*)arr4 - 1) - 1; i >=0; --i)
	{
		Squirl__Dtor(arr4 + i);
	}

	printf("*************************************\n");

	LegendaryAnimal* la1 = malloc(sizeof(LegendaryAnimal));
	LegendaryAnimal__Ctor(la1);

	LegendaryAnimal* la2 = malloc(sizeof(LegendaryAnimal));
	LegendaryAnimal__CCtor(la2, la1);

	la1->m_papa.m_vt[1](la1);
	la2->m_papa.m_vt[1](la2);


	(la1->m_papa.m_vt[0])(la1);

	free(la1);

	(la2->m_papa.m_vt[1])(la2);
	(la2->m_papa.m_vt[0])(la2);

	free(la2);

	for(i = 3; i >= 0; --i)
	{
		Centipede__Dtor(&(arr3[i]));
	}

	Centipede__Dtor(&c2);

	for(i = 2; i >= 0; --i)
	{
		Animal__Dtor(&(array2[i]));
	}

	Centipede__Dtor(&cen);

	return 0;
}
