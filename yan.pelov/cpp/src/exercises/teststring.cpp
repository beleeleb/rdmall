#include <iostream>
#include "string.h"

using namespace std;

using namespace RD3;

int main(int argc,char **argv,char **envp)
{
	char name[] = "yan";
	String s1(name);
	String s2(s1);
	
	cout << s1.CStr() << endl;
	cout << s1.Len() << endl;
	cout << s2.CStr() << endl;
	cout << s2.Len() << endl;
	
	if(s1==s2) cout << "equal" << endl;
	else cout << "not equal" << endl;
	
	char elem1[] = "A";
	char elem2[] = "B";
	String s3(elem1), s4(elem2);
	if(s3 < s4) cout << "smaller" << endl;
	else cout << "bigger" << endl;
	
	if(s3 > s4) cout << "bigger" << endl;
		else cout << "smaller" << endl;
	
	String s6, s7, s8;
	s6 = s2;
	s7 = s2;
	s8 = s2.CStr();
	cout << "s6: "<<s6.CStr() << endl;
	cout << "s7: "<<s7.CStr() << endl;
	cout << "s8: "<<s8.CStr() << endl;
	cout << "s2: "<<s2.CStr() << endl;

	s3 = s1;
	s3 = "avina";
	cout << s3.CStr() << endl;
	
	s3[3] = 'C';
	cout << s3.CStr() << endl;
	
	if(s3[0] == 'a') cout << "same" << endl;
	else cout << "not same" << endl;
	
	cout << s3 << endl;
	
	String s5;

	cin >>s5;
	
	cout << s5 << endl;
		
	return 0;
}
