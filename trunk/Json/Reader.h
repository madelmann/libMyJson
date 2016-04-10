
#ifndef Json_Reader_h
#define Json_Reader_h


// Library includes

// Project includes
#include "Value.h"

// Forward declarations

// Namespace declarations


namespace Json {

// Forward declarations
class Tokenizer;

class Reader
{
public:
	bool parse(const std::string& msg, Value& value);

protected:

private:
	bool parseArray(Tokenizer* t, Value& value);
	bool parseObject(Tokenizer* t, Value& value);
};


}


#endif
