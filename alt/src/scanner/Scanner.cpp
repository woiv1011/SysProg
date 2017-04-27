/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Scanner.h"

#include <sys/errno.h>
#include <climits>
#include <cstdio>
#include <cstdlib>

#include "../../Automat/includes/automata/MergeAutomat.h"
#include "../../Symboltable/includes/SymbolInformation.h"

Scanner::Scanner(const char* inputfile) {
	this->buffer = new Buffer(inputfile);
	this->symboltable = new Symboltable();
	this->automat = new MergeAutomat();
	this->signTokens = new HashMap<TokenType>(table_size_11);

	initializeSymboltable();
	initializeSignTokens();
}

Scanner::~Scanner() {
	delete this->buffer;
	this->buffer = NULL;
	delete this->symboltable;
	this->symboltable = NULL;
	delete this->automat;
	this->automat = NULL;
	delete this->signTokens;
	this->signTokens = NULL;
}

void Scanner::initializeSymboltable() {
	symboltable->insert("if", TokenType::KeywordIf);
	symboltable->insert("IF", TokenType::KeywordIf);
	symboltable->insert("while", TokenType::KeywordWhile);
	symboltable->insert("WHILE", TokenType::KeywordWhile);

	// TODO insert the other keywords from Parser Part II
	// symboltable->insert("", TokenType::Keyword);
}

bool Scanner::skipFoundText(LanguageType language) {
	switch (language) {
	case LanguageType::identifier:
		return false;
		break;
	case LanguageType::integer:
		return false;
		break;
	case LanguageType::sign:
		return false;
		break;
	case LanguageType::comment:
		return true;
		break;
	case LanguageType::newline:
		return true;
		break;
	case LanguageType::whitespace:
		return true;
		break;
	case LanguageType::digit:
		return false;
		break;
	case LanguageType::letter:
		return false;
		break;
	case LanguageType::undefined:
		return false;
		break;
	default:
		return false;
		break;
	}

	return false;
}

Token* Scanner::createToken(String& name, unsigned long line, unsigned long column, LanguageType language) {
	switch (language) {
	case LanguageType::identifier: {
		SymbolInformation* symbol = symboltable->insert(name, TokenType::Identifier);
		return new Token(name, line, column, symbol->getTokenType());
		break;
	}
	case LanguageType::integer: {
		long value = strtol(name.getData(), NULL, 0);

		// Check for Range Overflow
		// If the value read is out of the range of representable values by a long int, the function returns LONG_MAX or LONG_MIN (defined in <climits>), and errno is set to ERANGE.
		if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) || (errno != 0 && value == 0)) {
			return new Token(name, value, line, column, TokenType::IntegerError);
		}

		return new Token(value, line, column, TokenType::Integer);
		break;
	}
	case LanguageType::sign: {
		TokenType tokenType = parseSignType(name);
		return new Token(name, line, column, tokenType);
		break;
	}
	default:
		if (skipFoundText(language)) {
			return new Token(name, line, column, TokenType::Ignored);
		}
		return new Token(name, line, column, TokenType::Undefined);
		break;
	}

	return new Token(name, line, column, TokenType::Undefined);
}

void Scanner::initializeSignTokens() {
	signTokens->insertValue("+", new TokenType(TokenType::Plus));
	signTokens->insertValue("-", new TokenType(TokenType::Minus));
	signTokens->insertValue(":", new TokenType(TokenType::Colon));
	signTokens->insertValue("*", new TokenType(TokenType::Multiplication));
	signTokens->insertValue("<", new TokenType(TokenType::Lower));
	signTokens->insertValue(">", new TokenType(TokenType::Greater));
	signTokens->insertValue("=", new TokenType(TokenType::Equals));
	signTokens->insertValue(":=", new TokenType(TokenType::Assign));
	signTokens->insertValue("<:>", new TokenType(TokenType::Different));
	signTokens->insertValue("!", new TokenType(TokenType::ExclamationMark));
	signTokens->insertValue("&", new TokenType(TokenType::Ampersand));
	signTokens->insertValue(";", new TokenType(TokenType::Semicolon));
	signTokens->insertValue("(", new TokenType(TokenType::BraceRoundOpen));
	signTokens->insertValue(")", new TokenType(TokenType::BraceRoundClose));
	signTokens->insertValue("{", new TokenType(TokenType::BraceCurlyOpen));
	signTokens->insertValue("}", new TokenType(TokenType::BraceCurlyClose));
	signTokens->insertValue("[", new TokenType(TokenType::BraceSquareOpen));
	signTokens->insertValue("]", new TokenType(TokenType::BraceSquareClose));
}

TokenType Scanner::parseSignType(String& sign) {
	return signTokens->getValue(sign)->operator enum TokenType::Type();
}

Automat* Scanner::getAutomat() const {
	return automat;
}

Buffer* Scanner::getBuffer() const {
	return buffer;
}

Symboltable* Scanner::getSymboltable() const {
	return symboltable;
}

Token* Scanner::nextToken() {
	String text;
	String temp;

	if (buffer->isEOF()) {
		return NULL;
	}

	//cout << "Initialize automat" << endl;
	automat->initialize();

	unsigned long line = 0;
	unsigned long column = 0;

	while (automat->isAcceptingCharacter() and !buffer->isEOF()) {
		temp.clear();
		do {
			char c = buffer->next(); // Buffer read character

			if (text.isEmpty()) {
				line = buffer->getCurrentLine();
				column = buffer->getCurrentColumn();
			}

			automat->processCharacter(c);

			if (c != '\0') { // Avoid appending end of line character.
				temp += c;
			}

			//cout << "Automat processed character" << " " << c << " "
			//		<< "isError" << " " << automat->isErrorState() << " "
			//		<< "isFinal" << " " << automat->isFinalState() << " "
			//		<< "isAccepting" << " " << automat->isAcceptingCharacter() << endl;

		} while ((not automat->isFinalState()) and automat->isAcceptingCharacter()); // The EOF (\0) string terminal produce an error state, which breaks the workflow.

		if (automat->isFinalState() && not automat->isErrorState()) {
			text += temp;
		}
	}

	Token * result = NULL;
	if (text.isEmpty()) {
		// Create an error token no automat was able to recognize an accepted character sequence
//		cout << "ERROR TOKEN" << " " << temp << " " << "Code" << " " << (unsigned int) temp.c_str()[0] << " "
//				<< "not recognized." << " " << automat->getAcceptedLanguage() << endl;
		result = createToken(temp, line, column, LanguageType::undefined);
	} else {
		if (automat->isErrorState()) {
			// Buffer undo reading of temp.length() characters
			buffer->previous(temp.getLength());
		}
		// Create normal token Get type from automat
//		cout << "FOUND TOKEN" << " " << text << " " << "recognized by" << " " << automat->getAcceptedLanguage() << endl;
		result = createToken(text, line, column, automat->getAcceptedLanguage());
	}

	return result;
}
