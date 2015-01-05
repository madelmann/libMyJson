
#ifndef Json_Parser_h
#define Json_Parser_h


// Library includes

// Project includes
#include "Value.h"

// Forward declarations

// Namespace declarations


namespace Json {

// Forward declarations
class Tokenizer;

class Parser
{
public:
	static Value parse(const std::string& msg);

protected:

private:
	static Value parseArray(Tokenizer *t);
	static Value parseObject(Tokenizer *t);
};


}


#endif
