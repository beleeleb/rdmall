/* Yan, 28/1/15*/
#ifndef __COMPLEX_H__
#define  __COMPLEX_H__

#include <iostream> //needed for stream
#include <fstream> //needed for fstream

namespace rd3
{

class Complex;

std::ostream& operator<<(std::ostream& os_, const Complex& str_);  
std::istream& operator>>(std::istream& is_, Complex& str_);  
//std::ofstream& operator<<(std::ofstream& os_, const Complex& str_);  
std::ifstream& operator>>(std::ifstream& is_, Complex& str_); 

bool operator==(const Complex& num1_, const Complex& num2_);
bool operator!=(const Complex& num1_, const Complex& num2_);
const Complex operator+(const Complex& num1_, const Complex& num2_);
const Complex operator-(const Complex& num1_, const Complex& num2_);

class Complex
{
	
public:
	Complex(const double real_ = 0, const double img_ = 0);
	//Complex(const int num1_, const int num2); // non explicit on purpose
	/* DEBUG ONLY ~Complex() */
	
	Complex& operator+=(const Complex& num_);
	Complex& operator-=(const Complex& num_);
	
	void SetR(const double num_); //sets a real number
	void SetI(const double num_); //sets an imaginary number	
	
	double GetR() const; //gets the real number
	double GetI() const; //gets the imaginary number
	
private:
	
	double m_real;
	double m_img;	
	
};

} //end of namespace rd3

#endif /*  __COMPLEX_H__ */ 
