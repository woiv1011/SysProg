#include "globals.h"
#include "stringinfo.c"


//return the next token from the char-array / c-string given though the parameters
//token_t contains token length (in characters / bytes) and token type


token_t getNextToken3() {
  //INIT
  token_t resultToken;
  currentState = ST_START;
  nextState = 0;
  char c = getCurrentChar();
  int line   = getCurrentLine(); //aufspalten ?
  int column = getCurrentColumn();


  if(isSingleSignToken(c)) { //automat nicht notwendig
    resultToken.type = getSingleSignTokenType(c);
    resultToken.length = 1;
    return resultToken;
  }



  while(isWhitespace(c)) {
    c = getNextChar();
  }

  if(currentState == ST_START) {
    nextState = ST_IGIT;
  }

}