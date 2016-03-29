#include <iostream> //for cout
#include <fstream>
#include "factory.h"
#include "serializer.h"

namespace RD3
{

class Animal;

std::ostream& operator<<(std::ostream& os_, const Animal& m_);

class Animal
{
public:
	Animal() { std::cout << "Animal::Ctor()" << std::endl; }

	virtual ~Animal() { std::cout << "Animal::VDtor()" << std::endl; }

	Animal(const Animal& o_) { std::cout << "Animal::CCtor()" << std::endl; }

	virtual void Display() { std::cout << "I am Animal" << std::endl; }

	virtual void Legs()=0;

    virtual std::ostream& osPrint(std::ostream& os) const = 0;

private:

	Animal& operator=(const Animal&); // disabled

};

std::ostream& operator<<(std::ostream& os_, const Animal& m_)
{
	 return m_.osPrint(os_);
}


class Centipede: public Animal
{
public:
	Centipede(int num_):m_Legs(num_)
	{
		std::cout << "Centipede::Ctor()" << std::endl;
	}

	Centipede(std::istream& i_)
	{
		int ani;
		i_ >> ani;
		m_Legs = ani;
		std::cout << "Centipede::Ctor2()" << std::endl;
	}

	~Centipede() { std::cout << "Centipede::Dtor()" << std::endl; }

	Centipede(const Centipede &o_)
	{
		m_Legs = o_.m_Legs;
		std::cout << "Centipede::CCtor()" << std::endl;
	}

	void Display() { std::cout << "I am Centipede" << std::endl; }

	virtual void Legs() { std::cout << "I have: " << m_Legs << " legs." << std::endl; }

	std::ostream& osPrint(std::ostream& os_) const { return os_ << m_Legs; }


private:
	int m_Legs;
};

Centipede* makeC(int data_)
{
	return new Centipede(data_);
}
}

using namespace RD3;

int main(int argc,char **argv,char **envp) 
{
	std::tr1::shared_ptr<Animal> Obj;
	std::tr1::shared_ptr<Animal> Obj2;

	Factory<Centipede, int, int> f1;

	f1.Add(makeC, 5);

	try
	{
		Obj = f1.Create(5, 30);
	}

	catch(const std::runtime_error&  e) //to be changed to something more accurate
	{
		std::cerr << e.what() << std::endl;
	}

	Obj->Display();

	Centipede c1(100);

	Serializer<Animal> s1;

	std::ofstream myfile;

	myfile.open("example.txt");

	s1.Serialize(myfile, c1);
	myfile.close();

	std::ifstream input;
	input.open("example.txt");

	//s1.Add<Animal>();
	s1.Add<Centipede>();

	Obj2 = s1.Deserialize(input);

	std::cout << std::endl;
	Obj2->Display();

	Obj2->Legs();
	std::cout << std::endl;
	input.close();

	return 0;
}
