
// Header
#include "Reader.h"

// Library includes

// Project includes
#include "Exceptions.h"
#include "Token.h"
#include "Tokenizer.h"

// Namespace declarations


namespace Json {


bool Reader::parse(const std::string& msg, Value& root)
{
	bool result = false;

	Tokenizer tokenizer(msg);
	tokenizer.process();

	// first token has to be a '{'
	if ( tokenizer.hasNext() && tokenizer.getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
		tokenizer.next();

		// start the real parsing
		result = parseObject(&tokenizer, root);

		if ( tokenizer.getToken().type() != Token::Type::BRACKET_CURLY_CLOSE ) {
			throw Exceptions::InvalidJsonString(msg);
		}
	}

	return result;
}

bool Reader::parseArray(Tokenizer *t, Value& root)
{
	if ( !t ) {
		return false;
	}

	bool result = true;

	while ( result && t->hasNext() && t->getToken().type() != Token::Type::BRACKET_CLOSE ) {
		Value value;

		if ( t->getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
			t->next();

			// start reading object
			result = parseObject(t, value) && result;
		}
		else if ( t->getToken().type() == Token::Type::BRACKET_OPEN ) {
			t->next();

			// start reading array
			result = parseArray(t, value) && result;
		}
		else {
			// start reading element
			value = Value(t->getToken().content());

			result = true && result;
		}

		value.isArrayElement(true);
		root.addElement(value);

		result = true && result;

		t->next();
		if ( t->getToken().type() == Token::Type::COLON ) {
			t->next();
		}
	}

	return result;
}

bool Reader::parseObject(Tokenizer* t, Value& root)
{
	if ( !t ) {
		return false;
	}

	bool result = true;

	while ( result && t->hasNext() && t->getToken().type() != Token::Type::BRACKET_CURLY_CLOSE ) {
		std::string key = t->getToken().content();

		Value value;

		if ( t->hasNext() ) {
			t->next();
			if ( t->getToken().type() == Token::Type::DOUBLEPOINT ) {
				t->next();
			}

			if ( t->getToken().type() == Token::Type::BRACKET_OPEN ) {
				t->next();

				result = parseArray(t, value) && result;
			}
			else if ( t->getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
				t->next();

				result = parseObject(t, value) && result;
			}
			else {
				value = Value(t->getToken().content());

				result = true && result;
			}

			t->next();
		}

		root.addMember(key, value);

		result = true && result;

		if ( t->getToken().type() == Token::Type::COLON ) {
			t->next();
		}
	}

	return result;
}


}
