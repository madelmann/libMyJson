
#ifndef Json_Array_h
#define Json_Array_h


// Library includes

// Project includes
#include "Value.h"

// Forward declarations

// Namespace declarations


namespace Json {


class Array: public Value
{
public:
	Array()
	{
		type(Value::Type::ARRAY);
	}
};


}


#endif
