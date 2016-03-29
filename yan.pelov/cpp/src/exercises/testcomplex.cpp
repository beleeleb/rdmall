#include "complex.h"
#include "complexinl.h"

using namespace rd3;

int main(int argc,char **argv,char **envp) 
{
	double A = 3.666;
	double B = 53.3;
	
	Complex moshe(A, B);
	
	std::cout << moshe << std::endl;
	
	Complex haim(4,6);  //implicit conversion test
	
	std::cout << haim << std::endl;
	
	haim.SetR(3.666);
	haim.SetI(53.3);
	
	std::cout << haim.GetI() << std::endl;
	std::cout << haim.GetR() << std::endl;
	
	bool res = (haim != moshe);
	Complex john;
	john = moshe + haim;
	std::cout << res << std::endl; 
	
	std::cout << haim << std::endl;

	std::cout <<  john << std::endl;

	haim-=moshe;
	
	std::cout << haim << std::endl;
	
	Complex yan;
	
	/*std::cin >> yan;
	
	std::cout << yan << std::endl;*/
	
	std::ifstream infile("outfile.txt");
	
	infile >> yan;
	
	std::cout << yan << std::endl;
	
	/*std::ofstream outfile;
	
	std::cout << yan << std::endl;*/
	
	/*outfile.open("infile.txt");
	
	outfile << yan << std::endl;
	
	outfile.close();*/
	
	return 0;

}
