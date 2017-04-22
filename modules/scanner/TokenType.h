/*
 * TokenType.h
 *
 *  Created on: 12.12.2015
 *      Author: Joe
 */

#ifndef TOKENTYPE_H_
#define TOKENTYPE_H_

#include <iostream>

using namespace std;

struct TokenType {
public:
	enum Type {
		Undefined, Ignored, IntegerError,
		Integer,
		Identifier,
		Plus, Minus, Colon, Multiplication, Lower, Greater, Equals, Assign, Different, ExclamationMark, Ampersand, Semicolon,
		BraceRoundOpen, BraceRoundClose, BraceCurlyOpen, BraceCurlyClose, BraceSquareOpen, BraceSquareClose,
		KeywordIf, KeywordElse, KeywordWhile, KeywordRead, KeywordWrite, KeywordInt
	};

private:
	Type t_;

public:
	TokenType() :
			t_(Undefined) {
	}
	TokenType(Type t) :
			t_(t) {
	}
	operator Type() const {
		return t_;
	}

public:
	friend ostream& operator<<(ostream& out, const TokenType& value) {
		const char* s = "";

#define PROCESS_VAL(p, q) case(p): { s = q; break; }

		switch (value) {

		PROCESS_VAL(TokenType::Undefined, "Unknown")

		PROCESS_VAL(TokenType::Ignored, "Ignored")

		PROCESS_VAL(TokenType::Integer, "Integer")

		PROCESS_VAL(TokenType::IntegerError, "Integer out of range")

		PROCESS_VAL(TokenType::Identifier, "Identifier")

		PROCESS_VAL(TokenType::Plus, "Plus")

		PROCESS_VAL(TokenType::Minus, "Minus")

		PROCESS_VAL(TokenType::Colon, "Colon")

		PROCESS_VAL(TokenType::Multiplication, "Multiplication")

		PROCESS_VAL(TokenType::Lower, "Lower")

		PROCESS_VAL(TokenType::Greater, "Greater")

		PROCESS_VAL(TokenType::Equals, "Equals")

		PROCESS_VAL(TokenType::Assign, "Assign")

		PROCESS_VAL(TokenType::Different, "Different")

		PROCESS_VAL(TokenType::ExclamationMark, "ExclamationMark")

		PROCESS_VAL(TokenType::Ampersand, "Ampersand")

		PROCESS_VAL(TokenType::Semicolon, "Semicolon")

		PROCESS_VAL(TokenType::BraceRoundOpen, "BraceRoundOpen")

		PROCESS_VAL(TokenType::BraceRoundClose, "BraceRoundClose")

		PROCESS_VAL(TokenType::BraceCurlyOpen, "BraceCurlyOpen")

		PROCESS_VAL(TokenType::BraceCurlyClose, "BraceCurlyClose")

		PROCESS_VAL(TokenType::BraceSquareOpen, "BraceSquareOpen")

		PROCESS_VAL(TokenType::BraceSquareClose, "BraceSquareClose")

		PROCESS_VAL(TokenType::KeywordIf, "KeywordIf")

		PROCESS_VAL(TokenType::KeywordElse, "KeywordElse")

		PROCESS_VAL(TokenType::KeywordWhile, "KeywordWhile")

		PROCESS_VAL(TokenType::KeywordRead, "KeywordRead")

		PROCESS_VAL(TokenType::KeywordWrite, "KeywordWrite")

		PROCESS_VAL(TokenType::KeywordInt, "KeywordInt")

		}

#undef PROCESS_VAL

		return out << s;
	}

};

#endif /* TOKENTYPE_H_ */
