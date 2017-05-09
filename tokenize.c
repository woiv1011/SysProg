#include "macros.h"




//return the next token from the char-array / c-string given though the parameters
//token_t contains token length (in characters / bytes) and token type





token_t getNextToken3() {
  //INIT
  token_t resultToken;
  currentState = ST_START;
  nextState = 0;
  char c = 0;
  int line   = getCurrentLine(); //aufspalten ?
  int column = getCurrentColumn();



  c = getCurrentChar();

  while(isWhitespace(c)) {
    c = getNextChar();
  }

  if(currentState == ST_START) {
    nextState = ST_SIGIT;
  }

}