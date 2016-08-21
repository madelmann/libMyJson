
// Header
#include "Writer.h"

// Library includes

// Project includes
#include "Exceptions.h"

// Namespace declarations


namespace Json {


Writer::Writer()
: mWhiteSpaceEnd(" "),
  mWhiteSpaceIndent(""),
  mWhiteSpaceStart(" ")
{
}

Writer::~Writer()
{
}

std::string Writer::indent(unsigned int num)
{
	std::string result;

	for ( unsigned int i = 0; i < num; i++ ) {
		result += mWhiteSpaceIndent;
	}

	return result;
}

std::string Writer::toString(const Value& root, unsigned int indents)
{
	std::string result;

	Value::Members members = root.members();

	if ( members.empty() ) {
		switch ( root.type() ) {
			case Value::Type::NIL:
			case Value::Type::ATOMIC:
			case Value::Type::BOOL:
			case Value::Type::DOUBLE:
			case Value::Type::FLOAT:
			case Value::Type::INT:
			case Value::Type::UINT:
			case Value::Type::UNDEFINED:
				result += root.asString();
				break;
			case Value::Type::STRING:
				result += "\"" + root.asString() + "\"";
				break;
			case Value::Type::ARRAY: {
				result += "[" + mWhiteSpaceStart;
				result += toString(root, indents + 1);
				result += mWhiteSpaceStart + indent(indents + 1) + "]";
			} break;
			case Value::Type::OBJECT: {
				result += "{" + mWhiteSpaceStart;
				result += toString(root, indents + 1);
				result += mWhiteSpaceStart + indent(indents + 1) + "}";
			} break;
			default:
				throw Exceptions::Exception("invalid node type found");
		}
	}
	else {
		if ( root.isObject() ) {
			result += "{";
		}
		else {
			result += "[";
		}
		result += mWhiteSpaceStart;

		for ( Value::Members::const_iterator it = members.begin(); it != members.end(); ) {
			result += indent(indents + 1);

			if ( root.isObject() ) {
				result += "\"";
				result += (*it).key();
				result += "\": ";
			}

			result += toString((*it), indents + 1);
			if ( ++it != members.end() ) {
				result += ",";
			}
			result += mWhiteSpaceEnd;
		}

		result += indent(indents);
		if ( root.isObject() ) {
			result += "}";
		}
		else {
			result += "]";
		}
	}

	return result;
}


StyledWriter::StyledWriter()
{
	mWhiteSpaceEnd = "\n";
	mWhiteSpaceIndent = "    ";
	mWhiteSpaceStart = "\n";
}


}
