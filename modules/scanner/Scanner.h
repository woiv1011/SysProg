/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "../../Automat/includes/automata/Automat.h"
#include "../../Automat/includes/automata/LanguageType.h"
#include "../../Buffer/includes/Buffer.h"
#include "../../DataStructures/HashMap/includes/HashMap.h"
#include "../../DataStructures/String/includes/String.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "./Token.h"
#include "./TokenType.h"

class Scanner {
private:
	Buffer* buffer;
	Symboltable* symboltable;
	Automat* automat;

	HashMap<TokenType> * signTokens;

	void initializeSymboltable();
	void initializeSignTokens();
	TokenType parseSignType(String& sign);

	// Returns true if the text should not be used to create a token.
	bool skipFoundText(LanguageType language);

	Token* createToken(String& name, unsigned long line, unsigned long column, LanguageType language);

public:
	Scanner(const char * inputfile);
	virtual ~Scanner();

	Automat* getAutomat() const;
	Buffer* getBuffer() const;
	Symboltable* getSymboltable() const;

	Token* nextToken();
};

#endif /* SCANNER_H_ */
