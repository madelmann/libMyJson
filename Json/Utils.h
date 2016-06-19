
#ifndef Json_Utils_h
#define Json_Utils_h


// Library includes
#include <sstream>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Json {
namespace Utils {


bool toBool(const std::string& value);
double toDouble(const std::string& value);
float toFloat(const std::string& value);
int toInt(const std::string& value);
unsigned int toUInt(const std::string& value);

template <class T>
inline std::string toString(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}


}
}


#endif
