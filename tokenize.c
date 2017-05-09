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
  int currentLine   = 0; //aufspalten ?
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
    resultToken.type = getSingleSignTokenType(c);
    resultToken.length = length; //length muss 1 sein
    tempValue = malloc(length); //TODO bei anderen Token  length +1 wegen stringende, damit strcpy usw benutzt werden kann ?
    tempValue[0] = c;
    resultToken.value = tempValue;
    resultToken.line = currentLine;
    resultToken.column = currentColumn;
    return resultToken;
  }



  while(isWhitespace(c)) {
    c = getNextChar();
  }

  if(currentState == ST_START) {
    nextState = ST_IGIT;
  }

}