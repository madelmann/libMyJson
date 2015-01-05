
#ifndef Json_Exceptions_h
#define Json_Exceptions_h


// Library includes
#include <exception>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Json {
namespace Exceptions {


class Exception : public std::exception
{
public:
	Exception(const std::string& text)
	: mText(text)
	{ }
	virtual ~Exception() throw() { }

public:
#ifdef __WIN32
	const char* what() const {
		return mText.c_str();
	}
#elif defined __APPLE__
	const char* what() const throw() {
		return mText.c_str();
	}
#elif defined __linux
	virtual const char* what() const throw () {
		return mText.c_str();
	}
#endif

protected:

private:
	std::string	mText;
};

class DuplicateKey : public Exception
{
public:
	DuplicateKey(const std::string& text)
	: Exception(text)
	{ }
};

class InvalidArrayIndex : public Exception
{
public:
	InvalidArrayIndex(const std::string& text)
	: Exception(text)
	{ }
};

class InvalidJsonString : public Exception
{
public:
	InvalidJsonString(const std::string& text)
	: Exception(text)
	{ }
};

class InvalidKey : public Exception
{
public:
	InvalidKey(const std::string& text)
	: Exception(text)
	{ }
};

class UnknownKey : public Exception
{
public:
	UnknownKey(const std::string& text)
	: Exception(text)
	{ }
};


}
}


#endif
