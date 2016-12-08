
// Header
#include "Value.h"

// Library includes
#include <algorithm>

// Project includes
#include "Exceptions.h"
#include "Utils.h"

// Namespace declarations


namespace Json {


Value::Value()
: mIsArrayElement(false),
  mType(Type::NIL),
  mValue("null")
{
}

Value::Value(bool value)
: mIsArrayElement(false),
  mType(Type::BOOL),
  mValue(value)
{
}

Value::Value(double value)
: mIsArrayElement(false),
  mType(Type::DOUBLE),
  mValue(value)
{
}

Value::Value(float value)
: mIsArrayElement(false),
  mType(Type::FLOAT),
  mValue(value)
{
}

Value::Value(int value)
: mIsArrayElement(false),
  mType(Type::INT),
  mValue(value)
{
}

Value::Value(const char* value)
: mIsArrayElement(false),
  mType(Type::STRING),
  mValue(std::string(value))
{
}

Value::Value(const std::string& value)
: mIsArrayElement(false),
  mType(Type::STRING),
  mValue(value)
{
}

Value::Value(size_t value)
: mIsArrayElement(false),
  mType(Type::UINT),
  mValue(value)
{
}

void Value::addElement(const Value& member)
{
	if ( mType == Type::NIL ) {
		mType = Type::ARRAY;
	}
	if ( mType != Type::ARRAY ) {
		throw Exceptions::Exception("cannot retype value to JSON array");
	}

	Value v = member;
	v.key(Utils::toString(mMembers.size()));

	insert(v);
}

void Value::addMember(const std::string& key, const Value& member)
{
	if ( find(key) != mMembers.end() ) {
		throw Exceptions::DuplicateKey(key);
	}

	if ( mType == Type::NIL ) {
		mType = Type::OBJECT;
	}
	if ( mType != Type::OBJECT ) {
		throw Exceptions::Exception("cannot retype value to JSON object");
	}

	Value v = member;
	v.key(key);

	insert(v);
}

bool Value::asBool() const
{
	return mValue.toBool();
}

double Value::asDouble() const
{
	return mValue.toDouble();
}

float Value::asFloat() const
{
	return mValue.toFloat();
}

int Value::asInt() const
{
	return mValue.toInt();
}

std::string Value::asString() const
{
	switch ( mType ) {
		case Type::ARRAY:
		case Type::OBJECT:
			return "";
		default:
			break;
	}

	return mValue.toStdString();
}

unsigned int Value::asUInt() const
{
	return mValue.toUInt();
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

Value::Members::iterator Value::insert(const Value& value)
{
#ifdef JSON_VALUE_MAP
	return mMembers.insert(std::make_pair(value.key(), value));
#elif defined JSON_VALUE_SET
	mMembers.insert(value);
	return mMembers.end();
#elif defined JSON_VALUE_VECTOR
	mMembers.push_back(value);
	return find(value.key());
#elif defined JSON_VALUE_UNORDERED_SET
	mMembers.insert(value);
	return mMembers.end();
#endif
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

bool Value::removeElement(unsigned int idx)
{
	return removeMember(Utils::toString(idx));
}

bool Value::removeMember(const std::string& member)
{
	Members::iterator it = find(member);

	if ( it != mMembers.end() ) {
		mMembers.erase(it);
		return true;
	}

	return false;
}

std::string Value::printArray(const Value& v) const
{
	if ( v.size() ) {
		Members::const_iterator it = v.members().begin();

		std::string result;
		while ( it != v.members().end() ) {
#ifdef JSON_VALUE_MAP
			result += it->second->toStyledString();
#else
			result += it->toStyledString();
#endif
			it++;

			if ( it != v.members().end() ) {
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
		case Value::Type::ATOMIC:
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

std::string Value::toString() const
{
	return toStyledString();
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

	Value value;
	value.key(key);

	Members::iterator it = find(key);
	if ( it != mMembers.end() ) {
		(*it).isArrayElement(true);
		return (*it);
	}

	it = insert(value);
	return (*it);
}

Value& Value::operator[] (const char* key)
{
	if ( mType == Type::NIL ) {
		mType = Type::OBJECT;
	}

	Value value;
	value.key(key);

	Members::iterator it = find(key);
	if ( it != mMembers.end() ) {
		return (*it);
	}

	it = insert(value);
	return (*it);
}

Value& Value::operator[] (const std::string& key)
{
	if ( mType == Type::NIL ) {
		mType = Type::OBJECT;
	}

	Value value;
	value.key(key);

	Members::iterator it = find(key);
	if ( it != mMembers.end() ) {
		return (*it);
	}

	it = insert(value);
	return (*it);
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

bool Value::operator== (const Value& other) const
{
	return (this->key() == other.key());
}

bool Value::operator< (const Value& other) const
{
	return (this->key() < other.key());
}

bool Value::operator() (const Value& first, const Value& second) const
{
	return (first.key() != second.key());
}

Value Value::operator[] (size_t idx) const
{
	Members::const_iterator it = find(Utils::toString(idx));
	if ( it != mMembers.end() ) {
		return (*it);
	}

	throw Exceptions::InvalidArrayIndex(Utils::toString(idx));
}

Value Value::operator[] (const char* key) const
{
	Members::const_iterator it = find(key);
	if ( it != mMembers.end() ) {
		return (*it);
	}

	throw Exceptions::InvalidKey("key");
}

Value Value::operator[] (const std::string& key) const
{
	Members::const_iterator it = find(key);
	if ( it != mMembers.end() ) {
		return (*it);
	}

	throw Exceptions::InvalidKey("key");
}


}
