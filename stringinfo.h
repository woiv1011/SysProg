#include "tokenize.h"

//SINGLE CHAR start
bool isSpecial(char c);

bool isInvalid(char c);

bool isDigit(char c);

bool isLetter(char c);

bool isWhitespace(char c);

//+, -, *, :, <, >, =, :=, =:=, !, &&, ;, (, ), {, }, [, ]
bool isSign(char c);
/** returns true if c is a sign that is guaranteed to be its own, single-char token
*/
bool isSingleSignToken(char c);
bool isAmbiguousSign(char c);


//+, -, *, :, <, >, =, :=, =:=, !, &&, ;, (, ), {, }, [, ]


//TODO string compare end
//isEqualString(const char* s1, const char * s2);

/**
*   when the string token is terminated by a new token, whitespace, etc
*   this function determines whether it is an identifier with only letters or a keyword and returns the corresponding token/ tokenType?
*/
tokentype_t identifyString(int length, char *c);

/**
*   when the string token is terminated by a new token, whitespace, etc
*   this function determines whether it is an identifier with only letters or a keyword and returns the corresponding token/ tokenType?
*/
tokentype_t getSingleSignTokenType(char c);

bool isSingleSignToken(char c);