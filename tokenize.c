#include "globals.h"
#include "stringinfo.c"


//return the next token from the char-array / c-string given though the parameters
//token_t contains token length (in characters / bytes) and token type
//wenn man struct = struct macht, werden alle werte korrekt  kopiert wie bei einer einzelnen variable ?

#include "memory.h"

//creates and returns the single next token
token_t getNextToken() {
//INIT
  //currentState = ST_START;
  //nextState = 0;
  char temp[TOKENMAXLENGTH]; //direkt auf max length setzen ?
  char c = 0;
  int currentLine   = 0; //line at the beginning / 0th char of the token
  int currentColumn = 0;
  char *tempValue;
  short length = 1;
  //token_t resultToken;
  char active = 0;

  while(true) { //überspringt alle whitespaces, generiert tokens für invalid chars(error) und signs
    c = getCurrentChar();
    currentLine   = getCurrentLine();
    currentColumn = getCurrentColumn();

    //TODO  EOF ?

    //skip whitespace chars
    if(isWhitespace(c)) {
      continue;
    }

    //if char is invalid, print error message and create error token
    if(isInvalid(c)) {
      currentLine   = getCurrentLine();
      currentColumn = getCurrentColumn();
      printf("Invalid character (%c) on line %d, column %d\n", c, currentLine, currentColumn);
      return createToken(ERROR, 5, currentLine, currentColumn, "ERROR");
      //continue; //TODO einfach überspringen und das nächste korrekte Token zurückgeben ?
    }

    if(isSign(c)) {
      //if char is a sign that is guaranteed to be its own token
      if(isSingleSignToken(c)) {
        return createToken(getSingleSignTokenType(c), length, currentLine, currentColumn, value*);
      }

      // 3 cases of ambiguity, tokenlengths for the different cases are known in advance
      // : = &
      if(isAmbiguousSign(c)) {
        // & must become &&
        if(c == '&') { 
          if(getCharByOffset(1) == '&') { //2 mal & -> korrektes AND-Token
            return createToken(S_AND, 2, currentLine, currentColumn, "&&");
          }
          else {
            //& darf nicht einzeln vorkommen -> Fehler ausgeben, weiter tokenizen
            printf("Single & on line %d, column %d\n", currentLine, currentColumn);
            return createToken(ERROR, 5, currentLine, currentColumn, "ERROR"); //TODO errortoken ?
          }
        }

        // : can become :=
        if(c == ':') {
          if(getCharByOffset(1) == '=') {
            return createToken(S_DIV_EQ, 3, currentLine, currentColumn, ":=");
          }
          else {
            return createToken(S_DIV, 3, currentLine, currentColumn, ":");
          }
        }

        // = can become =:=
        if(c == '=') { 
          if(getCharByOffset(1) == ':' && getCharByOffset(2) == '=') {
            return createToken(S_EQ_DIV_EQ, 3, currentLine, currentColumn, "=:=");
          }
          else {
            return createToken(S_EQ, 1, currentLine, currentColumn, "=");
          }
        }
      }
    }

    //if char is a letter, start string token 
    if(isLetter(c)) {
      break;
    }

    //if char is a digit, start integer token
    if(isDigit(c)) {
      break;
    }

    next();
  } //end for

//string token, at the end determin whether keyword or identifier
if(isLetter(c)) {
  temp[0] = c; //first char is c
  for(length=1; length<TOKENMAXLENGTH;) {
    //next(); //TODO stattdessen getCharByOffset benutzen ?
    //c = getCurrentChar(); //c = next char
    c = getCharByOffset(length); //n chars weiter
    if(isLetter(c) || isDigit(c)) { //first char can be followed by either letters or digits
      temp[length] = c;
      length++;
    }
    else { //neither letter nor digit -> string token is terminated
      //TODO determine whether keyword or identifier
      tokentype = identifyString(length, temp);
      return createToken(type, length, currentLine, currentColumn, temp);
    }
    if(length == TOKENMAXLENGTH-1) { //if maxvalue of this loop is reached
      printf("TOKENMAXLENGTH reached. \n"); //TODO line column etc ausgeben
      //tokentype = identifyString(length, temp);
      //TODO return ERROR token or string token up to this point //identifier, so lange keywords gibts nicht
      return createToken(ERROR, 5, currentLine, currentColumn, "ERROR");
      //return createToken(type, length, currentLine, currentColumn, temp);
    }
  }
}

//integer token
if(isDigit(c)) {
  temp[0] = c; //first char is c
  for(length=1; length<TOKENMAXLENGTH;) {
    //next(); //TODO stattdessen getCharByOffset benutzen ?
    //c = getCurrentChar(); //c = next char
    c = getCharByOffset(length); //n chars weiter
    if(isDigit(c)) { //first char can be followed by either letters or digits
      temp[length] = c;
      length++;
    }
    else { //neither letter nor digit -> string token is terminated
      //TODO determine whether keyword or identifier
      //tokentype = identifyString(length, temp);
      tokentype = INTEGER;
      return createToken(type, length, currentLine, currentColumn, temp);
    }
    if(length == TOKENMAXLENGTH-1) { //if maxvalue of this loop is reached
      printf("TOKENMAXLENGTH reached. \n"); //TODO line column etc ausgeben
      //tokentype = identifyString(length, temp);
      //TODO return ERROR token or string token up to this point //identifier, so lange keywords gibts nicht
      return createToken(ERROR, 5, currentLine, currentColumn, "ERROR");
      //return createToken(type, length, currentLine, currentColumn, temp);
    }
  }
}


}