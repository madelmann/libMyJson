
#ifndef Json_Value_h
#define Json_Value_h


//#define JSON_VALUE_MAP
//#define JSON_VALUE_SET
#define JSON_VALUE_VECTOR
//#define JSON_VALUE_UNORDERED_SET

// Library includes
#include <string>
#ifdef JSON_VALUE_MAP
#	include <map>
#elif defined JSON_VALUE_SET
#	include <set>
#elif defined JSON_VALUE_VECTOR
#	include <vector>
#elif defined JSON_VALUE_UNORDERED_SET
#	include <unordered_set>
#endif

// Project includes
#include "AtomicValue.h"

// Forward declarations

// Namespace declarations


namespace Json {


class Value
{
public:
#ifdef JSON_VALUE_MAP
	typedef std::map<std::string, Value> Members;
#elif defined JSON_VALUE_SET
	typedef std::set<Value> Members;
#elif defined JSON_VALUE_VECTOR
	typedef std::vector<Value> Members;
#elif defined JSON_VALUE_UNORDERED_SET
	typedef std::unordered_set<Value> Members;
#endif

	class Type
	{
	public:
		enum E {
			NIL,
			ARRAY,
			ATOMIC,
			BOOL,
			DOUBLE,
			FLOAT,
			INT,
			OBJECT,
			STRING,
			UINT,
			UNDEFINED
		};
	};

public:
	Value();
	Value(bool value);
	Value(double value);
	Value(float value);
	Value(int value);
	Value(const char* value);
	Value(const std::string& value);
	Value(size_t value);

	virtual ~Value() { }

public:
	bool asBool() const;
	double asDouble() const;
	float asFloat() const;
	int asInt() const;
	std::string asString() const;
	unsigned int asUInt() const;

	bool isArray() const;
	bool isBool() const;
	bool isDouble() const;
	bool isFloat() const;
	bool isInt() const;
	bool isNull() const;
	bool isObject() const;
	bool isString() const;
	bool isUInt() const;

	bool isArrayElement() const;
	void isArrayElement(bool value);

	void addElement(const Value& member);
	void addMember(const std::string& key, const Value& member);
	bool isMember(const std::string& member) const;
	const Members& members() const;
	bool removeElement(unsigned int idx);
	bool removeMember(const std::string& member);

	Members::iterator insert(const Value& value);

	size_t size() const;

	const std::string& key() const;
	void key(const std::string& value);

	Type::E type() const;
	void type(Type::E type);

public:
	std::string toString() const;
	std::string toStyledString() const;

public:
	Value& operator= (const Value& other);
	bool operator== (const Value& other) const;
	bool operator< (const Value& other) const;
	bool operator() (const Value& first, const Value& second) const;

	Value& operator[] (size_t idx);
	Value& operator[] (const char* key);
	Value& operator[] (const std::string& key);

	Value operator[] (size_t idx) const;
	Value operator[] (const char* key) const;
	Value operator[] (const std::string& key) const;

protected:

private:
	Members::iterator find(const std::string& key);
	Members::const_iterator find(const std::string& key) const;

	bool isEscapingRequired() const;

	std::string printArray(const Value& v) const;
	std::string printObject(const Value& v) const;

	std::string printKey(const Value& v) const;
	std::string printValue(const Value& v) const;

	std::string toQuotedString(const std::string& value) const;

private:
	bool		mIsArrayElement;
	std::string	mKey;
	Members		mMembers;
	Type::E		mType;
	AtomicValue	mValue;
};


}


#endif
