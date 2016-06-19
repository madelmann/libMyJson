
// Header
#include "Utils.h"

// Library includes

// Project includes

// Namespace declarations


namespace Json {
namespace Utils {


bool toBool(const std::string& value)
{
	std::stringstream ss(value);
	bool v;
	ss >> v;

	return v;
}

double toDouble(const std::string& value)
{
	std::stringstream ss(value);
	double v;
	ss >> v;

	return v;
}

float toFloat(const std::string& value)
{
	std::stringstream ss(value);
	float v;
	ss >> v;

	return v;
}

int toInt(const std::string& value)
{
	std::stringstream ss(value);
	int v;
	ss >> v;

	return v;
}

unsigned int toUInt(const std::string& value)
{
	std::stringstream ss(value);
	unsigned int v;
	ss >> v;

	return v;
}


}
}
