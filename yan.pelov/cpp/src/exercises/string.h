/*
 *	YAN PELOV
 */
#ifndef __STRING_H__
#define  __STRING_H__

#include <cstddef> //used for size_t
#include <iostream>

namespace RD3
{

class String;

std::ostream& operator<<(std::ostream& os_, const String& str_);  
std::istream& operator>>(std::istream& is_, String& str_);  

class String
{
public:
	 
	String(const char* str_="");
	
	~String();
	
	String(const String& str_);  
	
	String& operator=(const String& str_);
	String& operator=(const char* str_);
		
	bool operator==(const String& str_) const; //strings comparison
	bool operator<(const String& str_) const; //lexigrapic strings comparison
	bool operator>(const String& str_) const; //lexigrapic strings comparison
	
	char& operator[](std::size_t index_);
	char operator[](std::size_t index_) const;
	
	std::size_t Len() const; //counts the number of chars	

	const char* CStr() const;
			
private:
	char* m_str;
	void CopyIMP(const char* str_);
	void DelIMP(char* str_);
	size_t* RefIMP();
	
};

} // namespace rd3
#endif /*  __STRING_H__ */ 
