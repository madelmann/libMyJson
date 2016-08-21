
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
	bool result = false;

	if ( !t ) {
		return result;
	}

	while ( t->hasNext() && t->getToken().type() != Token::Type::BRACKET_CLOSE ) {
		Value value;

		if ( t->getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
			t->next();

			// start reading object
			parseObject(t, value);
		}
		else if ( t->getToken().type() == Token::Type::BRACKET_OPEN ) {
			t->next();

			// start reading array
			parseArray(t, value);
		}
		else {
			// start reading element
			value = Value(t->getToken().content());
		}

		value.isArrayElement(true);
		root.addElement(value);

		t->next();
		if ( t->getToken().type() == Token::Type::COLON ) {
			t->next();
		}
	}

	return result;
}

bool Reader::parseObject(Tokenizer* t, Value& root)
{
	bool result = false;

	if ( !t ) {
		return result;
	}

	while ( t->hasNext() && t->getToken().type() != Token::Type::BRACKET_CURLY_CLOSE ) {
		std::string key = t->getToken().content();

		Value value;

		if ( t->hasNext() ) {
			t->next();
			if ( t->getToken().type() == Token::Type::DOUBLEPOINT ) {
				t->next();
			}

			if ( t->getToken().type() == Token::Type::BRACKET_OPEN ) {
				t->next();

				parseArray(t, value);
			}
			else if ( t->getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
				t->next();

				parseObject(t, value);
			}
			else {
				value = Value(t->getToken().content());
			}

			t->next();
		}

		root.addMember(key, value);

		if ( t->getToken().type() == Token::Type::COLON ) {
			t->next();
		}
	}

	return result;
}


}
