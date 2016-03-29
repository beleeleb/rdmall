
#include <vector>
#include <iostream>
#include <fstream>
#include "osit.h"

using namespace std;
using namespace rd3;

template<class I, class O>
O mycopy(I f, I t, O d)
{
	while(f!=t)
	{
		*d = *f;
		++f;
		++d;
	}

	return d;
}

int main()
{
	vector<int> v;
	int i;

	v.push_back(44);
	v.push_back(55);
	v.push_back(66);
	v.push_back(77);

	for(i = 0; i < 4; ++i )
	{
	    cout << v[i] << "\n";
	}

	ofstream f("osit.txt");
	OstreamIter <int> o(f);

	mycopy(v.begin(), v.end(), o);

	f.close();

	return 0;
}
