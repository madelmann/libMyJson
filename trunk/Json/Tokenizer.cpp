
// Header
#include "Tokenizer.h"

// Library includes

// Project includes
//#include "Exceptions.h"

// Namespace declarations


namespace Json {


const std::string CONTROLCHARS	= "#,;:=()[]{}+-*/&'\" ";
const std::string DELIMITERS	= "#,;:=()[]{}+-*/&'\"\t\n\r ";
const std::string WHITESPACES	= "\t\n\r ";


Tokenizer::Tokenizer(const std::string& content)
: mContent(content)
{
}

void Tokenizer::addToken(const Token& token)
{
	if ( token.content().empty() && token.type() == Token::Type::UNKNOWN ) {
		// ignore this non-existing token
		return;
	}

	// add only valid tokens to our token list
	mTokens.push_back(token);
}

Token Tokenizer::createToken(const std::string& con, const Token::Position& pos)
{
	std::string content = con;

	Token::Type::E type = Token::Type::IDENTIFER;

	if ( content == "," ) { type = Token::Type::COMMA; }
	else if ( content == "." ) { type = Token::Type::DOT; }
	else if ( content == ":" ) { type = Token::Type::COLON; }
	else if ( content == ";" ) { type = Token::Type::SEMICOLON; }
	else if ( content == "'" ) { type = Token::Type::QUOTATION_SINGLE; }
	else if ( content == "\"" ) { type = Token::Type::QUOTATION_DOUBLE; }
	else if ( content == "[" ) { type = Token::Type::BRACKET_OPEN; }
	else if ( content == "]" ) { type = Token::Type::BRACKET_CLOSE; }
	else if ( content == "{" ) { type = Token::Type::BRACKET_CURLY_OPEN; }
	else if ( content == "}" ) { type = Token::Type::BRACKET_CURLY_CLOSE; }
	else if ( content == ">" ) { type = Token::Type::COMPARE_GREATER; }
	else if ( content == "<" ) { type = Token::Type::COMPARE_LESS; }
	else if ( content == "=" ) { type = Token::Type::EQUAL; }
	else if ( content == "(" ) { type = Token::Type::PARENTHESIS_OPEN; }
	else if ( content == ")" ) { type = Token::Type::PARENTHESIS_CLOSE; }
	else if ( content == "+" ) { type = Token::Type::MATH_ADD; }
	else if ( content == "/" ) { type = Token::Type::MATH_DIV; }
	else if ( content == "*" ) { type = Token::Type::MATH_MULTI; }
	else if ( content == "-" ) { type = Token::Type::MATH_SUBTRACT; }
	else if ( content == "&" ) { type = Token::Type::STRING_ADD; }
	else if ( isNull(content) ) { type = Token::Type::NIL; }
	else if ( isBoolean(content) ) { type = Token::Type::BOOLEAN; }
	else if ( isDigit(content) ) { type = Token::Type::CONSTANT; }
	else if ( isLiteral(content) ) {
		// remove leading and trailing (", ') quotation marks (", ')
		type = Token::Type::LITERAL;
		content = con.substr(1, con.length() - 2);
	}
	else if ( isWhiteSpace(content) ) { type = Token::Type::WHITESPACE; }

	return Token(type, content, pos);
}

const std::string Tokenizer::getString() const
{
	return mContent;
}

const Token& Tokenizer::getToken() const
{
	return *mActiveToken;
}

bool Tokenizer::hasNext() const
{
	if ( mActiveToken != mTokens.end() ) {
		return true;
	}

	return false;
}

bool Tokenizer::isBoolean(const std::string& token) const
{
	return (token == "false" || token == "true");
}

bool Tokenizer::isDigit(const std::string& token) const
{
	if ( token.empty() ) {
		return false;
	}

	int numOfDots = 0;

	for ( unsigned int c = 0; c < token.size(); c++ ) {
		switch ( token[c] ) {
			case '.':
				numOfDots++;
				if ( numOfDots > 1 ) {
					return false;
				}
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
			case 'E':
			case 'e':
				break;
			default:
				return false;
		}
	}

	return true;
}

bool Tokenizer::isLiteral(const std::string& token) const
{
	if ( token.size() > 1 ) {
		// double quotated literals
		if ( (token.at(0) == '"' && token.at(token.size() - 1) == '"')) {
			return true;
		}
		// single quotated literals
		if ( (token.at(0) == '\'' && token.at(token.size() - 1) == '\'') ) {
			return true;
		}
	}

	return false;
}

bool Tokenizer::isNull(const std::string& token) const
{
	return token == "null";
}

bool Tokenizer::isType(const std::string& token) const
{
	for ( StringList::const_iterator it = mTypes.begin(); it != mTypes.end(); ++it ) {
		if ( (*it) == token ) {
			return true;
		}
	}

	return false;
}

bool Tokenizer::isWhiteSpace(const std::string& token) const
{
	return (WHITESPACES.find_first_of(token) != std::string::npos);
}

void Tokenizer::next()
{
	mActiveToken++;
}

void Tokenizer::process()
{
	size_t offset = 0;
	std::string token;

	bool isMultiLineComment = false;
	bool isSingleLineComment = false;
	bool isString = false;

	char lastChar = 0;
	Token::Position pos(1, 1);

	while ( offset < mContent.size() ) {
		char thisChar = mContent[offset++];
		size_t i = DELIMITERS.find_first_of(thisChar);

		// single line comments '//'
		if ( !isMultiLineComment && !isSingleLineComment && !isString && lastChar == '/' && thisChar == '/' ) {
			isSingleLineComment = true;
			// remove last inserted token
			mTokens.pop_back();
		}
		// multiline comments '/*'
		else if ( !isMultiLineComment && !isSingleLineComment && !isString && lastChar == '/' && thisChar == '*' ) {
			isMultiLineComment = true;
			// remove last inserted token
			mTokens.pop_back();
		}
		// don't parse comments
		else if ( !isMultiLineComment && !isSingleLineComment ) {
			// are we reading a string?
			if ( (thisChar == '\"' /* || thisChar == '\''*/) && lastChar != '\\' ) {
				isString = !isString;
			}

			if ( !isString && i != std::string::npos ) {
				if ( !token.empty() ) {
					if ( thisChar == '"' /*|| thisChar == '\''*/ ) {
						token += thisChar;
						thisChar = 0;
					}
					addToken(createToken(token, pos));
				}

				token.clear();
				token = thisChar;

				if ( !token.empty() && token.at(0) != 0 ) {
					addToken(createToken(token, pos));
				}

				token.clear();
			}
			else {
				// only add char if it is no '\'
				if ( thisChar != '\\' ) {
					token += thisChar;
				}
			}
		}

		// multiline comments '*/'
		if ( isMultiLineComment && lastChar == '*' && thisChar == '/' ) {
			isMultiLineComment = false;
		}

		// counting lines and columns
		pos.column++;
		if ( thisChar == '\n' ) {
			isSingleLineComment = false;
			pos.line++;
			pos.column = 1;
		}

		// keep track of our last char (i.e. for escape sequences)
		lastChar = thisChar;
	}

	// add end of file token (Token::Type::ENDOFFILE)
	addToken(Token(Token::Type::ENDOFFILE));

	removeWhiteSpaces();		// remove all whitespaces
	replace();

	mActiveToken = mTokens.begin();
}

void Tokenizer::removeWhiteSpaces()
{
	TokenList tmp;

	for ( TokenList::iterator it = mTokens.begin(); it != mTokens.end(); ++it ) {
		if ( (*it).type() != Token::Type::WHITESPACE ) {
			tmp.push_back((*it));
		}
	}

	mTokens = tmp;
}

void Tokenizer::replace()
{
	TokenList tmp;
	Token::Type::E lastType = Token::Type::UNKNOWN;
	TokenIterator token = mTokens.begin();

	// try to combine all compare tokens
	while ( token != mTokens.end() ) {
		bool changed = false;
		Token::Type::E activeType = token->type();

		if ( activeType == Token::Type::EQUAL ) {
			if ( lastType == Token::Type::EQUAL ) {
				// ==
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add COMPARE_EQUAL instead
				tmp.push_back(Token(Token::Type::COMPARE_EQUAL, "=="));
			}
			else if ( lastType == Token::Type::GREATER ) {
				// >=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add COMPARE_GREATER_EQUAL instead
				tmp.push_back(Token(Token::Type::COMPARE_GREATER_EQUAL, ">="));
			}
			else if ( lastType == Token::Type::LESS ) {
				// <=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add COMPARE_LESS_EQUAL instead
				tmp.push_back(Token(Token::Type::COMPARE_LESS_EQUAL, "<="));
			}
			else if ( lastType == Token::Type::MATH_ADD ) {
				// +=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add ASSIGN_ADD instead
				tmp.push_back(Token(Token::Type::ASSIGN_ADD, "+="));
			}
			else if ( lastType == Token::Type::MATH_DIV ) {
				// /=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add ASSIGN_DIVIDE instead
				tmp.push_back(Token(Token::Type::ASSIGN_DIVIDE, "/="));
			}
			else if ( lastType == Token::Type::MATH_MULTI ) {
				// *=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add ASSIGN_MULTI instead
				tmp.push_back(Token(Token::Type::ASSIGN_MULTI, "*="));
			}
			else if ( lastType == Token::Type::MATH_SUBTRACT ) {
				// -=
				changed = true;
				// remove last added token ...
				tmp.pop_back();
				// ... and add ASSIGN_SUBTRACT instead
				tmp.push_back(Token(Token::Type::ASSIGN_SUBTRACT, "-="));
			}
		}

		lastType = token->type();
		if ( !changed ) {
			tmp.push_back((*token));
		}

		token++;
	}

	mTokens = tmp;
	tmp.clear();

	for ( TokenIterator it = mTokens.begin(); it != mTokens.end(); ++it ) {
		if ( (*it).type() == Token::Type::EQUAL ) {
			tmp.push_back(Token(Token::Type::ASSIGN, (*it).content(), (*it).position()));
		}
		else {
			tmp.push_back((*it));
		}
	}

	mTokens = tmp;
}

const TokenList& Tokenizer::tokens() const
{
	return mTokens;
}


}
