
#ifndef Json_Types_h
#define Json_Types_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace Json {


template <class T> class SmartPtr
{
public:
	SmartPtr()
	: mPtr(0)
	{ }
	SmartPtr(T *p)
	: mPtr(p)
	{ }
	~SmartPtr() {
		delete mPtr;
		mPtr = 0;
	}

public:
	T* get() {
		return mPtr;
	}

	void reset(T *p) {
		mPtr = p;
	}

    SmartPtr& operator=( SmartPtr const &other ) {
        (*this).reset(other.get());
		other.reset(0);

        return (*this);
    }

protected:

private:
	T	*mPtr;
};


}


#endif
