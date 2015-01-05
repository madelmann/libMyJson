
#ifndef JsonNG_Writer_h
#define JsonNG_Writer_h


// Library includes
#include <string>

// Project includes
#include "Value.h"

// Forward declarations

// Namespace declaration


namespace Json {


class Writer
{
public:
	Writer();
	virtual ~Writer() { }

public:
	virtual std::string toString(const Value& root, unsigned int indents = 0);

protected:
	std::string mWhiteSpaceEnd;
	std::string mWhiteSpaceIndent;
	std::string mWhiteSpaceStart;

private:
	std::string indent(unsigned int num);
};


class StyledWriter : public Writer
{
public:
	StyledWriter();
};


}


#endif
