
// Header
#include "Reader.h"

// Library includes
#include <assert.h>
#include <list>

// Project includes
#include "Exceptions.h"
#include "Token.h"
#include "Tokenizer.h"

// Namespace declarations


namespace Json {


bool Reader::parse(const std::string& msg, Value& value)
{
	bool result = false;

	Tokenizer tokenizer(msg);
	tokenizer.process();

	// first token has to be a '{'
	if ( tokenizer.hasNext() && tokenizer.getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
		tokenizer.next();

		// start the real parsing
		result = parseObject(&tokenizer, value);

		if ( tokenizer.getToken().type() != Token::Type::BRACKET_CURLY_CLOSE ) {
			throw Exceptions::InvalidJsonString(msg);
		}
	}

	return result;
}

bool Reader::parseArray(Tokenizer *t, Value& value)
{
	bool result = false;

	if ( !t ) {
		return result;
	}

	while ( t->hasNext() && t->getToken().type() != Token::Type::BRACKET_CLOSE ) {
		if ( t->getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
			t->next();

			// start reading object
			Value v;
			parseObject(t, v);
			v.isArrayElement(true);

			value[value.size()] = v;
		}
		else if ( t->getToken().type() == Token::Type::BRACKET_OPEN ) {
			t->next();

			// start reading array
			Value v;
			parseArray(t, v);
			v.isArrayElement(true);

			value[value.size()] = v;
		}
		else {
			// start reading element
			Value v(t->getToken().content());
			v.isArrayElement(true);

			value[value.size()] = v;
		}

		t->next();
		if ( t->getToken().type() == Token::Type::COLON ) {
			t->next();
		}
	}

	return result;
}

bool Reader::parseObject(Tokenizer* t, Value& value)
{
	bool result = false;

	if ( !t ) {
		return result;
	}

	while ( t->hasNext() && t->getToken().type() != Token::Type::BRACKET_CURLY_CLOSE ) {
		std::string key = t->getToken().content();

		Value v;

		if ( t->hasNext() ) {
			t->next();
			if ( t->getToken().type() == Token::Type::DOUBLEPOINT ) {
				t->next();
			}

			if ( t->getToken().type() == Token::Type::BRACKET_OPEN ) {
				t->next();

				parseArray(t, v);
			}
			else if ( t->getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
				t->next();

				parseObject(t, v);
			}
			else {
				v = Value(t->getToken().content());
			}

			t->next();
		}

		value.addMember(key, v);

		if ( t->getToken().type() == Token::Type::COLON ) {
			t->next();
		}
	}

	return result;
}


}
