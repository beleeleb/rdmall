#include <iostream>
#include "bitset.h"

using namespace std;
using namespace rd3;

int main(int argc,char **argv,char **envp)
{
	DEBUG_ONLY(
	Bitset <128> set1;
	//set1.CountTrueBits ();

	set1.FlipAll();
	set1.PrintSet();
	cout << endl;
	//~set1;
	set1.FlipAll();
	set1.PrintSet();
	cout << endl;
	set1.Flip(15);
	//set1.Flip(40);
	//set1.Flip(100);

	//set1.Flip(120);

	set1.Set(1, 50);
	set1.Set(1, 51);
	set1.Set(1, 52);



	cout << endl;

	cout << "counter: \n" <<set1.CountTrueBits() << endl;
	set1.PrintSet();
	cout << endl;

	cout << set1.Get(50) <<endl;
	cout << set1.Get(51) <<endl;

	cout << set1.Get(44) <<endl;

	set1.PrintSet();
		cout << endl;

	/*set1.Set(1, 77);
	set1.Set(1, 78);
	set1.Set(1, 79);*/

	set1.Set(0, 15);
	set1.Set(0, 40);

	set1.PrintSet();

	set1 >>= 40;
	//set1 <<= 100;
	cout << endl;
	set1.PrintSet();



	set1 <<= 40;

	//~set1;
	cout << endl;
	set1.PrintSet();
	/*Bitset <128> set2;
	Bitset <128> set3;

	cout << (set1 == set2) << endl;
	cout << (set1 != set2) << endl;

	set1.SetOn();


	set2.PrintSet();

	cout << (set1 == set2) << endl;
	cout << (set1 != set2) << endl;
	cout << "******************************" << endl;
	for (int i = 0; i < 127; i ++)
	{
		set1.SetOff (i);
	}

	set3 = set1.Flip (1);

	set1.PrintSet();
	// Set2.PrintSet ();
	set3.PrintSet();

	cout << "******************************" << endl;
	set3 &= set1;

	set3.PrintSet();

	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;

	set3 = set1.FlipAll ();
	set1.PrintSet();
	set3.PrintSet();

	cout << "bit 1 in set1:" << set1.Get (127) << endl;

	cout << "Number of bits in first size_t:" << set3.CountTrueBits () << endl;


	Bitset <128> set4;
	// Bitset <128> set5;
	set4.PrintSet();
	set3.PrintSet();

	// Bool t = set4.Get ()
	set4 [5] = set3 [6];
	// Bitset <128> set6 = * (const_cast <Bitset <128> *> (& set4));
	// Set6 [1] = true;

	cout << "(set4 [5] == set3 [5]):" << (set4 [5] == set3 [5]) << endl;

	// Const Bitset <128> set6 (set4);
	// Const Bitset <128> set7 (set5);
	set4.PrintSet();
	//set7.PrintSet ();

	// Cout << "ret of set4 [15] == set5 [15]:" << (set6 [5] == set7 [5]) << endl;
	cout << "ret of set3 [15] == set1 [15]:" << (set1 [15] == set3 [15]) << endl;

	// Set2 | = set1;

	// Set2.PrintSet ();*/

	)// end of DEBUG ONLY
	return 0;
}
