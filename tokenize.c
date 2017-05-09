#include "globals.h"
#include "stringinfo.c"


//return the next token from the char-array / c-string given though the parameters
//token_t contains token length (in characters / bytes) and token type
//wenn man struct = struct macht, werden alle werte korrekt  kopiert wie bei einer einzelnen variable ?

#include "memory.h"


token_t getNextToken() {
//INIT
  currentState = ST_START;
  nextState = 0;
  char temp[512];
  char c = 0;
  int currentLine   = 0; //line at the beginning / 0th char of the token
  int currentColumn = 0;
  char *tempValue;
  short length = 1;
  token_t resultToken;

  c = getCurrentChar();

  if(isInvalidCharacter(c)) {
    //print error and exit
    //oder als whitespace betrachten und überspringen ?
  }
  while(isWhitespace(c)) {
    next();
    c = getCurrentChar();
  }

  currentLine   = getCurrentLine();
  currentColumn = getCurrentColumn();

  if(isSingleSignToken(c)) { //automat nicht notwendig
    //resultToken.type = getSingleSignTokenType(c);
    resultToken = createToken(getSingleSignTokenType(c), length, currentLine, currentColumn, value*);
    return resultToken;
  }

  // : = &
  if(isAmbiguousSign(c)) { 
    // & must become &&
    if(c == '&') { 
      if(getCharByOffset(1) == '&') { //2 mal & -> korrektes AND-Token
        createToken(S_AND, 2, currentLine, currentColumn, "&&");
        return token;
      }
      else {
        //& darf nicht einzeln vorkommen -> Fehler ausgeben, weiter tokenizen
        printf("Single & on line %d, column %d\n", currentLine, currentColumn);
        createToken(ERROR, 0, currentLine, currentColumn, "&_Error"); //TODO errortoken ?
      }
    }

    // : can become :=
    if(c == ':') {
      if(getCharByOffset(1) == '=') {
        createToken(S_EQ_DIV_EQ, 3, currentLine, currentColumn, ":=");
      }
      else {
        createToken(S_EQ_DIV_EQ, 3, currentLine, currentColumn, ":");
      }
    }

    // = can become =:=
    if(c == '=') { 
      if(getCharByOffset(1) == ':' && getCharByOffset(2) == '=') {
        createToken(S_EQ_DIV_EQ, 3, currentLine, currentColumn, "=:=");
        return token;
      }
      else {
        createToken(S_EQ, 1, currentLine, currentColumn, "=");
        //createToken(S_EQ_DIV_EQ, 3, currentLine, currentColumn, "=:="); ???
        // kein kombiniertes Token, sondern einzelne SignTokens
      }
    } 
  }




  if(currentState == ST_START) {
    nextState = ST_IGIT;
  }

}