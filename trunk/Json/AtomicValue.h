
#ifndef Json_AtomicValue_h
#define Json_AtomicValue_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Json {


class AtomicValue
{
public:
	enum {
		UNKOWN,
		BOOL,
		DOUBLE,
		FLOAT,
		INT,
		STRING,
		UINT
	} type;

public:	// Construction
	AtomicValue();
	AtomicValue(bool val);
	AtomicValue(double val);
	AtomicValue(float val);
	AtomicValue(int val);
	AtomicValue(const std::string& val);
	AtomicValue(size_t val);

	~AtomicValue();

public:	// Assignment
	void operator=(bool val);
	void operator=(double val);
	void operator=(float val);
	void operator=(int val);
	void operator=(const std::string& val);
	void operator=(size_t val);

public:	// Conversion
	bool toBool() const;
	double toDouble() const;
	float toFloat() const;
	int toInt() const;
	std::string toStdString() const;
	size_t toUInt() const;

private:
	union ValueHolder {
		bool bool_;
		double double_;
		float float_;
		int int_;
		//const char* string_;
		size_t uint_;
	};

private:
	std::string mStringValue;
	ValueHolder mValue;
};


}


#endif
