
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
	bool parse(const std::string& msg, Value& root);

protected:

private:
	bool parseArray(Tokenizer* t, Value& root);
	bool parseObject(Tokenizer* t, Value& root);
};


}


#endif
