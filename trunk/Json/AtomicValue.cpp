
// Header
#include "AtomicValue.h"

// Library includes
#include <cassert>

// Project includes
#include "Utils.h"

// Namespace declarations


namespace Json {


AtomicValue::AtomicValue()
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;
	mValue.uint_ = 0;

	type = UNKOWN;
}

AtomicValue::AtomicValue(bool val)
{
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;
	mValue.uint_ = 0;

	type = BOOL;
	mValue.bool_ = val;
}

AtomicValue::AtomicValue(double val)
{
	mValue.bool_ = false;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;
	mValue.uint_ = 0;

	type = DOUBLE;
	mValue.double_ = val;
}

AtomicValue::AtomicValue(float val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.int_ = 0;
	//mValue.string_ = 0;
	mValue.uint_ = 0;

	type = FLOAT;
	mValue.float_ = val;
}

AtomicValue::AtomicValue(int val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	//mValue.string_ = 0;
	mValue.uint_ = 0;

	type = INT;
	mValue.int_ = val;
}

AtomicValue::AtomicValue(const std::string& val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	mValue.uint_ = 0;

	type = STRING;
	//mValue.string_ = val.c_str();
	mStringValue = val;
}

AtomicValue::AtomicValue(size_t val)
{
	mValue.bool_ = false;
	mValue.double_ = 0.0;
	mValue.float_ = 0.f;
	mValue.int_ = 0;
	//mValue.string_ = 0;

	type = INT;
	mValue.uint_ = val;
}

AtomicValue::~AtomicValue()
{
}

void AtomicValue::operator=(bool val)
{
	mStringValue = "";

	type = BOOL;
	mValue.bool_ = val;
}

void AtomicValue::operator=(double val)
{
	mStringValue = "";

	type = DOUBLE;
	mValue.double_ = val;
}

void AtomicValue::operator=(float val)
{
	mStringValue = "";

	type = FLOAT;
	mValue.float_ = val;
}

void AtomicValue::operator=(int val)
{
	mStringValue = "";

	type = INT;
	mValue.int_ = val;
}

void AtomicValue::operator=(const std::string& val)
{
	mValue.double_ = 0.0;

	type = STRING;
	//mValue.string_ = val.c_str();
	mStringValue = val;
}

void AtomicValue::operator=(size_t val)
{
	mStringValue = "";

	type = INT;
	mValue.uint_ = val;
}

bool AtomicValue::toBool() const
{
	switch ( type ) {
		case BOOL: return mValue.bool_;
		case DOUBLE: return (bool)mValue.double_;
		case FLOAT: return (bool)mValue.float_;
		case INT: return (bool)mValue.int_;
		case STRING: return Utils::toBool(mStringValue);
		case UINT: return (bool)mValue.uint_;
		default: break;
	}

	assert(!"invalid data type");
	return false;
}

double AtomicValue::toDouble() const
{
	switch ( type ) {
		case BOOL: return (double)mValue.bool_;
		case DOUBLE: return mValue.double_;
		case FLOAT: return (double)mValue.float_;
		case INT: return (double)mValue.int_;
		case STRING: return Utils::toDouble(mStringValue);
		case UINT: return (double)mValue.uint_;
		default: break;
	}

	assert(!"invalid data type");
	return 0.0;
}

float AtomicValue::toFloat() const
{
	switch ( type ) {
		case BOOL: return (float)mValue.bool_;
		case DOUBLE: return (float)mValue.double_;
		case FLOAT: return mValue.float_;
		case INT: return (float)mValue.int_;
		case STRING: return Utils::toFloat(mStringValue);
		case UINT: return (float)mValue.uint_;
		default: break;
	}

	assert(!"invalid data type");
	return 0.f;
}

int AtomicValue::toInt() const
{
	switch ( type ) {
		case BOOL: return (int)mValue.bool_;
		case DOUBLE: return (int)mValue.double_;
		case FLOAT: return (int)mValue.float_;
		case INT: return mValue.int_;
		case STRING: return Utils::toInt(mStringValue);
		case UINT: return (int)mValue.uint_;
		default: break;
	}

	assert(!"invalid data type");
	return 0;
}

std::string AtomicValue::toStdString() const
{
	switch ( type ) {
		case BOOL: return Utils::toString(mValue.bool_);
		case DOUBLE: return Utils::toString(mValue.double_);
		case FLOAT: return Utils::toString(mValue.float_);
		case INT: return Utils::toString(mValue.int_);
		case STRING: return mStringValue;
		case UINT: return Utils::toString(mValue.uint_);
		default: break;
	}

	assert(!"invalid data type");
	return "";
}

size_t AtomicValue::toUInt() const
{
	switch ( type ) {
		case BOOL: return (size_t)mValue.bool_;
		case DOUBLE: return (size_t)mValue.double_;
		case FLOAT: return (size_t)mValue.float_;
		case INT: return (size_t)mValue.int_;
		case STRING: return Utils::toUInt(mStringValue);
		case UINT: return mValue.uint_;
		default: break;
	}

	assert(!"invalid data type");
	return 0;
}


}
