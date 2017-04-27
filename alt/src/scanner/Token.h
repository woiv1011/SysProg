/*
 * Token.h
 *
 *  Created on: 12.12.2015
 *      Author: Joe
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>

#include "../../DataStructures/String/includes/String.h"
#include "TokenType.h"

using namespace std;

class Token {
private:
	String name;
	long value;
	unsigned long line;
	unsigned long column;
	TokenType type;
	bool valid;

public:
	Token();
	Token(String& name, unsigned long line, unsigned long column, TokenType type);
	Token(int value, unsigned long line, unsigned long column, TokenType type);
	Token(String& name, int value, unsigned long line, unsigned long column, TokenType type);
	virtual ~Token();

	const String& getName() const;
	int getValue() const;
	unsigned long getLine() const;
	unsigned long getColumn() const;
	TokenType getType() const;
	bool isValid() const;

public:
	friend ostream& operator<<(ostream& out, Token& value);
	friend ostream& operator<<(ostream& out, Token* value);
};

#endif /* TOKEN_H_ */
