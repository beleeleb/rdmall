#include "complex.h"

namespace rd3
{

inline std::ostream& operator<<(std::ostream& os_, const Complex& num_)
{
	return os_<< "(" << num_.GetR() << "," << num_.GetI() << ")" ; 
}

inline std::istream& operator>>(std::istream& is_, Complex& num_)
{
	char ch[3];
	double A;
	double B;
	
	is_ >> ch[0] >> A >> ch[1]  >> B >> ch[2]; 
	num_.SetR(A);
	num_.SetI(B);
	//assert (charachtes ',(,),);	
	return is_;
}

/*inline std::ofstream& operator<<(std::ofstream& os_, const Complex& num_)
{
	
	//return os_;
	return os_<< "(" << num_.GetR() << "," << num_.GetI() << ")" ; 
	
}*/

inline std::ifstream& operator>>(std::ifstream& is_, Complex& num_)
{
	char ch[3];
	double A;
	double B;
	
	is_ >> ch[0] >> A >> ch[1]  >> B >> ch[2]; 
	num_.SetR(A);
	num_.SetI(B);
		
	return is_;
}

inline bool operator==(const Complex& num1_, const Complex& num2_)
{
	return ((num1_.GetR() == num2_.GetR()) && (num1_.GetI() == num2_.GetI())); 
}

inline bool operator!=(const Complex& num1_, const Complex& num2_)
{
	return !((num1_.GetR() == num2_.GetR()) && (num1_.GetI() == num2_.GetI())); 
}

inline const Complex operator+(const Complex& num1_, const Complex& num2_)
{
	Complex res(num1_);
	res += num2_;
		
	return res;
}

inline const Complex operator-(const Complex& num1_, const Complex& num2_)
{
	Complex res(num1_);
	res -= num2_;
	
	return res;
}


inline Complex::Complex(const double real_, const double img_): m_real(real_), m_img(img_)
{}
	
inline Complex& Complex::Complex::operator+=(const Complex& num_)
{
	m_real += num_.m_real;
	m_img  += num_.m_img;
	return *this;
}

inline Complex& Complex::operator-=(const Complex& num_)
{
	m_real -= num_.m_real;
	m_img  -= num_.m_img;
	return *this;
}

	
inline void Complex::SetR(const double num_)
{
	m_real = num_;
}

inline void Complex::SetI(const double num_)
{
	m_img = num_;	
}

inline double Complex::GetR() const
{
	return m_real;
}

inline double Complex::GetI() const
{
	return m_img;
}

} //end of namespace rd3
