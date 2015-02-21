
// Header
#include "Parser.h"

// Library includes
#include <assert.h>
#include <list>

// Project includes
#include "Exceptions.h"
#include "Token.h"
#include "Tokenizer.h"

// Namespace declarations


namespace Json {


Value Parser::parse(const std::string& msg)
{
	Tokenizer tokenizer(msg);
	tokenizer.process();

	Value value;

	// first token has to be a '{'
	if ( tokenizer.hasNext() && tokenizer.getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
		tokenizer.next();

		// start the real parsing
		value = parseObject(&tokenizer);

		if ( tokenizer.getToken().type() != Token::Type::BRACKET_CURLY_CLOSE ) {
			throw Exceptions::InvalidJsonString(msg);
		}
	}

	return value;
}

Value Parser::parseArray(Tokenizer *t)
{
	Value result;

	if ( !t ) {
		return result;
	}

	while ( t->hasNext() && t->getToken().type() != Token::Type::BRACKET_CLOSE ) {
		if ( t->getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
			t->next();

			// start reading object
			Value v = parseObject(t);
			v.isArrayElement(true);

			result[result.size()] = v;
		}
		else if ( t->getToken().type() == Token::Type::BRACKET_OPEN ) {
			t->next();

			// start reading array
			Value v = parseArray(t);
			v.isArrayElement(true);

			result[result.size()] = v;
		}
		else {
			// start reading element
			Value v(t->getToken().content());
			v.isArrayElement(true);

			result[result.size()] = v;
		}

		t->next();
		if ( t->getToken().type() == Token::Type::COLON ) {
			t->next();
		}
	}

	return result;
}

Value Parser::parseObject(Tokenizer *t)
{
	Value result;

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

				v = parseArray(t);
			}
			else if ( t->getToken().type() == Token::Type::BRACKET_CURLY_OPEN ) {
				t->next();

				v = parseObject(t);
			}
			else {
				v = Value(t->getToken().content());
			}

			t->next();
		}

		result.addMember(key, v);

		if ( t->getToken().type() == Token::Type::COLON ) {
			t->next();
		}
	}

	return result;
}


}
