
// Header
#include "Value.h"

// Library includes

// Project includes
#include "Exceptions.h"
#include "Utils.h"

// Namespace declarations


namespace Json {


Value::Value()
: mIsArrayElement(false),
  mType(Type::NIL)
{
}

Value::Value(bool value)
: mIsArrayElement(false),
  mType(Type::BOOL)
{
	if ( value ) {
		mValue = "true";
	}
	else {
		mValue = "false";
	}
}

Value::Value(double value)
: mIsArrayElement(false),
  mType(Type::DOUBLE)
{
	mValue = Utils::toString(value);
}

Value::Value(float value)
: mIsArrayElement(false),
  mType(Type::FLOAT)
{
	mValue = Utils::toString(value);
}

Value::Value(int value)
: mIsArrayElement(false),
  mType(Type::INT)
{
	mValue = Utils::toString(value);
}

Value::Value(const char* value)
: mIsArrayElement(false),
  mType(Type::STRING)
{
	mValue = value;
}

Value::Value(const std::string& value)
: mIsArrayElement(false),
  mType(Type::STRING)
{
	mValue = value;
}

Value::Value(size_t value)
: mIsArrayElement(false),
  mType(Type::UINT)
{
	mValue = Utils::toString(value);
}

void Value::addMember(const std::string& key, const Value& member)
{
#ifdef JSON_VALUE_SET
	if ( mMembers.find(key) != mMembers.end() ) {
		throw Exceptions::DuplicateKey(key);
	}
#elif defined JSON_VALUE_VECTOR
	if ( find(key) != mMembers.end() ) {
		throw Exceptions::DuplicateKey(key);
	}
#endif

	if ( mType == Type::NIL ) {
		mType = Type::OBJECT;
	}

	Value v = member;
	v.key(key);

#ifdef JSON_VALUE_SET
	mMembers.insert(v);
#elif defined JSON_VALUE_VECTOR
	mMembers.push_back(v);
#endif
}

bool Value::asBool() const
{
	if ( mValue != "false" ) {
		return true;
	}

	return false;
}

double Value::asDouble() const
{
	std::stringstream ss(mValue);
	double v;
	ss >> v;

	return v;
}

float Value::asFloat() const
{
	std::stringstream ss(mValue);
	float v;
	ss >> v;

	return v;
}

int Value::asInt() const
{
	std::stringstream ss(mValue);
	int v;
	ss >> v;

	return v;
}

const std::string& Value::asString() const
{
	return mValue;
}

unsigned int Value::asUInt() const
{
	std::stringstream ss(mValue);
	unsigned int v;
	ss >> v;

	return v;
}

Value::Members::iterator Value::find(const std::string& key)
{
	for ( Members::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->key() == key ) {
			return it;
		}
	}

	return mMembers.end();
}

Value::Members::const_iterator Value::find(const std::string& key) const
{
	for ( Members::const_iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->key() == key ) {
			return it;
		}
	}

	return mMembers.end();
}

bool Value::isArray() const
{
	return (mType == Type::ARRAY);
}

bool Value::isArrayElement() const
{
	return mIsArrayElement;
}

void Value::isArrayElement(bool value)
{
	mIsArrayElement = value;
}

bool Value::isBool() const
{
	return (mType == Type::BOOL);
}

bool Value::isDouble() const
{
	return (mType == Type::DOUBLE);
}

bool Value::isFloat() const
{
	return (mType == Type::FLOAT);
}

bool Value::isInt() const
{
	return (mType == Type::INT);
}

bool Value::isMember(const std::string& member) const
{
	return ( find(member) != mMembers.end() );
}

bool Value::isObject() const
{
	return (mType == Type::OBJECT);
}

bool Value::isString() const
{
	return (mType == Type::STRING);
}

bool Value::isUInt() const
{
	return (mType == Type::UINT);
}

const std::string& Value::key() const
{
	return mKey;
}

void Value::key(const std::string& value)
{
	mKey = value;
}

const Value::Members& Value::members() const
{
	return mMembers;
}

bool Value::removeMember(const std::string& member)
{
	for ( Members::iterator it = mMembers.begin(); it != mMembers.end(); ++it ) {
		if ( it->key() == member ) {
			mMembers.erase(it);
			return true;
		}
	}

	return false;
}

std::string Value::printArray(const Value& v) const
{
	if ( v.size() ) {
		Members members = v.members();
		Members::const_iterator it = members.begin();

		std::string result;
		while ( it != members.end() ) {
			result += it->toStyledString();
			it++;

			if ( it != members.end() ) {
				result += ",";
			}
		}

		return "[" + result + "]";
	}

	return "[]";
}

std::string Value::printKey(const Value& v) const
{
	return "\"" + v.key() + "\"";
}

std::string Value::printObject(const Value& v) const
{
	std::string result;

	Members::const_iterator it = v.members().begin();
	while ( it != v.members().end() ) {
		result += printKey((*it));
		result += ":";
		result += printValue((*it));

		it++;
		if ( it != v.members().end() ) {
			result += ",";
		}
	}

	return "{" + result + "}";
}

std::string Value::printValue(const Value& v) const
{
	switch ( v.type() ) {
		case Value::Type::NIL:
			return "null";
		case Value::Type::BOOL:
		case Value::Type::DOUBLE:
		case Value::Type::FLOAT:
		case Value::Type::INT:
		case Value::Type::UINT:
		case Value::Type::UNDEFINED:
			return v.asString();
		case Value::Type::STRING:
			return "\"" + v.asString() + "\"";
		case Value::Type::ARRAY:
			return printArray(v);
		case Value::Type::OBJECT:
			return printObject(v);
	}

	return "";
}

size_t Value::size() const
{
	return mMembers.size();
}

std::string Value::toStyledString() const
{
	if ( isArrayElement() && !isObject() ) {
		return printValue(*this);
	}

	std::string result;
	if ( isObject() ) {
		result += "{";
	}

	Members::const_iterator it = mMembers.begin();
	while ( it != mMembers.end() ) {
		if ( !it->isArrayElement() ) {
			result += printKey((*it));
			result += ":";
		}

		result += printValue((*it));
		it++;

		if ( it != mMembers.end() ) {
			result += ",";
		}
	}

	if ( isObject() ) {
		result += "}";
	}

	if ( result.empty() ) {
		result = printValue(*this);
	}

	return result;
}

Value::Type::E Value::type() const
{
	return mType;
}

void Value::type(Value::Type::E type)
{
	mType = type;
}

Value& Value::operator[] (size_t idx)
{
	if ( mType == Type::NIL ) {
		mType = Type::ARRAY;
	}

	std::string key = Utils::toString(idx);

	Value v;
	v.key(key);

#ifdef JSON_VALUE_SET
	Members::iterator it = mMembers.find(v);
	if ( it != mMembers.end() ) {
		(*it).isArrayElement(true);
		return (*it);
	}
#elif defined JSON_VALUE_VECTOR
	Members::iterator it = find(key);
	if ( it != mMembers.end() ) {
		(*it).isArrayElement(true);
		return (*it);
	}
#endif

#ifdef JSON_VALUE_SET
	std::pair<Members::iterator, bool> p = mMembers.insert(v);
	if ( !p.second ) {
		throw Exceptions::JSONException("could not insert object");
	}

	return *p.first;
#elif defined JSON_VALUE_VECTOR
	mMembers.push_back(v);
	return mMembers.back();
#endif
}

Value& Value::operator[] (const char* key)
{
	if ( mType == Type::NIL ) {
		mType = Type::OBJECT;
	}

	Value v;
	v.key(key);

#ifdef JSON_VALUE_SET
	Members::iterator it = mMembers.find(v);
	if ( it != mMembers.end() ) {
		return (*it);
	}
#elif defined JSON_VALUE_VECTOR
	Members::iterator it = find(key);
	if ( it != mMembers.end() ) {
		return (*it);
	}
#endif

#ifdef JSON_VALUE_SET
	std::pair<Members::iterator, bool> p = mMembers.insert(v);
	if ( !p.second ) {
		throw Exceptions::JSONException("could not insert object");
	}

	return *p.first;
#elif defined JSON_VALUE_VECTOR
	mMembers.push_back(v);
	return mMembers.back();
#endif
}

Value& Value::operator[] (const std::string& key)
{
	if ( mType == Type::NIL ) {
		mType = Type::OBJECT;
	}

	Value v;
	v.key(key);

#ifdef JSON_VALUE_SET
	Members::iterator it = mMembers.find(v);
	if ( it != mMembers.end() ) {
		return (*it);
	}
#elif defined JSON_VALUE_VECTOR
	Members::iterator it = find(key);
	if ( it != mMembers.end() ) {
		return (*it);
	}
#endif

#ifdef JSON_VALUE_SET
	std::pair<Members::iterator, bool> p = mMembers.insert(v);
	if ( !p.second ) {
		throw Exceptions::JSONException("could not insert object");
	}

	return *p.first;
#elif defined JSON_VALUE_VECTOR
	mMembers.push_back(v);
	return mMembers.back();
#endif
}

Value& Value::operator= (const Value& other)
{
	this->mIsArrayElement = other.mIsArrayElement;
	//this->mKey = other.mKey;
	this->mMembers = other.mMembers;
	this->mType = other.mType;
	this->mValue = other.mValue;

	return *this;
}

Value Value::operator[] (size_t idx) const
{
#ifdef JSON_VALUE_SET
	Members::const_iterator it = mMembers.find(toString(idx));
	if ( it != mMembers.end() ) {
		return (*it);
	}
#elif defined JSON_VALUE_VECTOR
	Members::const_iterator it = find(Utils::toString(idx));
	if ( it != mMembers.end() ) {
		return (*it);
	}
#endif

	throw Exceptions::InvalidArrayIndex(Utils::toString(idx));
}

Value Value::operator[] (const char* key) const
{
#ifdef JSON_VALUE_SET
	Members::const_iterator it = mMembers.find(key);
	if ( it != mMembers.end() ) {
		return (*it);
	}
#elif defined JSON_VALUE_VECTOR
	Members::const_iterator it = find(key);
	if ( it != mMembers.end() ) {
		return (*it);
	}
#endif

	return Value();
}

Value Value::operator[] (const std::string& key) const
{
#ifdef JSON_VALUE_SET
	Members::const_iterator it = mMembers.find(key);
	if ( it != mMembers.end() ) {
		return (*it);
	}
#elif defined JSON_VALUE_VECTOR
	Members::const_iterator it = find(key);
	if ( it != mMembers.end() ) {
		return (*it);
	}
#endif

	return Value();
}


}
