
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
