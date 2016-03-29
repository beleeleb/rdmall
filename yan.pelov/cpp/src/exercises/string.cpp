#include <cstring>
#include <cassert>
#include "string.h"

namespace RD3
{

std::ostream& operator<<(std::ostream& os_, const String& str_)
{
	return os_<<str_.CStr();
}

std::istream& operator>>(std::istream& is_, String& str_)
{
	char buffer[20];
	is_>> buffer; 
	str_ = buffer;
	return is_;
}

String::String(const char* str_)
{
	assert(str_);
	String::CopyIMP(str_);  
}

String::~String()
{
	if(*RefIMP() > 1)
	{
		*RefIMP() -= 1;
	}

	else
	{
		delete[] RefIMP();
		 m_str = 0;
	}

}

String::String(const String& o_): m_str(o_.m_str)
{
	++*RefIMP();
}

String& String::operator=(const String& str_)
{
	assert(str_.m_str);

	if(*RefIMP() > 1)
	{
		*RefIMP() -= 1;
		return *this;
	}

	else
	{
		char * old = m_str;					
		String::CopyIMP(str_.CStr());
		String::DelIMP(old); 
		return *this;
	}


}

String& String::operator=(const char* str_)
{
	assert(str_);

	if(*RefIMP() > 1)
	{
		*RefIMP() -= 1;
		return *this;
	}

	else
	{
		char * old = m_str;
		String::CopyIMP(str_);
		String::DelIMP(old);
		return *this;
	}
}

bool String::operator==(const String& str_) const
{
	assert(str_.m_str);
	return !strcmp(m_str, str_.m_str);
}

bool String::operator<(const String& str_) const
{
	assert(str_.m_str);
	return (strcmp(m_str, str_.m_str) < 0);
}

bool String::operator>(const String& str_) const
{
	assert(str_.m_str);
	return (strcmp(m_str, str_.m_str) > 0);
}

char& String::operator[](std::size_t index_)
{	
	assert(index_ < strlen(m_str));

	if(*RefIMP() == 1)
	{
		return m_str[index_];
	}

	--*RefIMP();

	CopyIMP(m_str);

	return m_str[index_];

}

char String::operator[](std::size_t index_) const
{
	assert(index_ < strlen(m_str));
	return m_str[index_]; 
}

std::size_t String::Len() const
{
	return std::strlen(m_str);
}

const char* String::CStr()const
{
	return m_str;
}

void String::DelIMP(char* str_)
{
	str_ -=sizeof(size_t);
	delete[] str_;
	str_= reinterpret_cast<char*>(0xdeadbeef);
}

size_t* String::RefIMP()
{
	return reinterpret_cast<size_t*>(m_str) - 1;
}

void String::CopyIMP(const char* str_)
{		
	assert(str_);
	size_t size = std::strlen(str_) + 1;
	
	m_str = sizeof(size_t) + new char[sizeof(size_t) + size];

	*RefIMP() = 1;

	memcpy(m_str, str_, size);
}


}
