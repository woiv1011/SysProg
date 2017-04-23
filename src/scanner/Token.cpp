/*
 * Token.cpp
 *
 *  Created on: 12.12.2015
 *      Author: Joe
 */

#include "../includes/Token.h"

#include <iomanip>

Token::Token() {
	this->name = "";
	this->value = 0;
	this->line = 0;
	this->column = 0;
	this->type = TokenType::Undefined;
	this->valid = true;
}

Token::Token(String& name, unsigned long line, unsigned long column, TokenType type) {
	this->name = name;
	this->value = 0;
	this->line = line;
	this->column = column;
	this->type = type;
	this->valid = true;
}

Token::Token(int value, unsigned long line, unsigned long column, TokenType type) {
	this->name = "";
	this->value = value;
	this->line = line;
	this->column = column;
	this->type = type;
	this->valid = true;
}

Token::Token(String& name, int value, unsigned long line, unsigned long column, TokenType type) {
	this->name = name;
	this->value = value;
	this->line = line;
	this->column = column;
	this->type = type;
	this->valid = true;
}

Token::~Token() {

}

const String& Token::getName() const {
	return name;
}

int Token::getValue() const {
	return value;
}

unsigned long Token::getLine() const {
	return line;
}

unsigned long Token::getColumn() const {
	return column;
}

TokenType Token::getType() const {
	return type;
}

bool Token::isValid() const {
	return valid;
}

ostream& operator<<(ostream& out, Token& value) {
//	Token Unknown          Line: 3    Column: 1    Symbol: ?
//	Token Identifier       Line: 1    Column: 1    Lexem: X
//	Token Integer          Line: 1    Column: 5    Value: 4

	out << "Token" << " " << setw(16) << left << value.type
			<< "    " << "Line:   " << setw(5) << right << value.line
			<< "    " << "Column: " << setw(7) << right << value.column;

	switch (value.type) {
	case TokenType::Undefined:
		out << "    " << "Symbol: " << value.name;
		break;
	case TokenType::Identifier:
		out << "    " << "Lexem: " << value.name;
		break;
	case TokenType::Integer:
		out << "    " << "Value: " << value.value;
		break;
	case TokenType::IntegerError:
		out << "    " << "Number: " << value.name;
		out << "    " << "Value: " << value.value;
		break;
	default:
		break;
	}

	return out;
}

ostream& operator<<(ostream& out, Token* value) {
	out << (*value);
	return out;
}
