
#ifndef Json_Object_h
#define Json_Object_h


// Library includes

// Project includes
#include "Value.h"

// Forward declarations

// Namespace declarations


namespace Json {


class Object: public Value
{
public:
	Object()
	{
		type(Value::Type::OBJECT);
	}

	Object(const std::string& key, Value member)
	{
		type(Value::Type::OBJECT);

		Value::key(key);
		addElement(member);
	}
};


}


#endif
