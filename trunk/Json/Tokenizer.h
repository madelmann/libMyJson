
#ifndef Json_Tokenizer_h
#define Json_Tokenizer_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace Json {


typedef std::list<std::string> StringList;

class Tokenizer
{
public:
	Tokenizer(const std::string& content);

public:	// expose old interface
    const std::string getString() const;
    const Token& getToken() const;

    bool hasNext() const;
	void next();

public:
	const TokenList& tokens() const;

	void process();

protected:

private:	// Tokenizer
	Token createToken(const std::string& con, const Token::Position& pos);

	void addToken(const Token& token);
	void removeWhiteSpaces();
	void replace();

	bool isBoolean(const std::string& token) const;
	bool isDigit(const std::string& token) const;
	bool isLiteral(const std::string& token) const;
	bool isType(const std::string& token) const;
	bool isWhiteSpace(const std::string& token) const;

private:	// Preprocessor
	bool isDefined(const std::string& token) const;

private:
	TokenIterator	mActiveToken;
	std::string	mContent;
	TokenList	mTokens;
	StringList	mTypes;
};


}


#endif
