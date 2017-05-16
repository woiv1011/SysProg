#include "globals.h"
#include "tokenize.h"
#include "stringinfo.c"

#include "buffer.h"

//return the next token from the char-array / c-string given though the parameters
//token_t contains token length (in characters / bytes) and token type
//wenn man struct = struct macht, werden alle werte korrekt  kopiert wie bei einer einzelnen variable ?

//#include "memory.h"
void initTokenList() {
  startNode = malloc(sizeof(tokennode_t));
  startNode->next = NULL;
  startNode->data.type = 0;
  startNode->data.line = 0;
  startNode->data.column = 0;
  startNode->data.length = 0;
  startNode->data.value = malloc(1);
  startNode->data.value[0] = 0;
}

void appendTokenToList(token_t tok) {
  static int tokenListSize = 0;
  static tokennode_t *currentNode;
  static tokennode_t *newNode;

  newNode = malloc(sizeof(tokennode_t));
  newNode->next = NULL;
  newNode->data = tok;

  if(tokenListSize == 0) {
    startNode = newNode; //startnnde wird ab hier nicht mehr verändert
    currentNode = newNode; //am anfang current = start
  }

  else { //tokenListSize >= 1
    currentNode->next = newNode;
    currentNode = newNode;
  }

  tokenListSize++;
}

void printTokenList() {
  static tokennode_t *currentNode;
  static int index = 0;
  char test[] = "HALLO wie geht es dir heute so, mir geht es gut";
  int i = 0;
  if(index == 0) {
    currentNode = startNode;
  }

  while(1) {
    /*if(currentNode == NULL || currentNode->data.type == EOFTYPE) {
      printf("\nEND of TokenList, EOFTYPE found\n");
      break;
    }*/
    printf("i: %4d ", index);
    printf(" line: %3d", currentNode->data.line);
    printf(" col: %4d", currentNode->data.column);
    printf(" length: %4d", currentNode->data.length);
    //printf(" type: %s", tokenTypeToString(currentNode->data.type));
    //printf(" type: %.5s", test);
    printf(" type: %.5s", tokenTypeToString(currentNode->data.type));
    printf(" type: %4d", currentNode->data.type);
    printf(" typetest: %s", tokenTypeToString(512));
    printf(" value: "); //TODO stattdessen mit %s ? -> benötigt stringende zeichen
    for(i=0; i<currentNode->data.length; i++) {
      printf("%c", currentNode->data.value[i]);
    }
    printf("\n");

    if(currentNode->next == NULL) {
      break;
    }
    else {
      currentNode = currentNode->next;
    }
    /*if(currentNode->data.type = EOFTYPE) {
      printf("\nEND of TokenList, EOFTYPE found\n");
      break;
    }*/
    index++;
  }
  

}

token_t createToken(tokentype_t type, unsigned short length, int line, int column, char *value) {
  token_t result;
  result.type = type;
  result.length = length;
  result.line = line;
  result.column = column;

  if(length == 1) {
    result.value = malloc(2);
    result.value[0] = value[0];
    result.value[1] = '\0';
  }
  else {
    result.value = malloc(length+1);
    strncpy(result.value, value, length);
  }




  return result;
}


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
  

  while(isNotFinished()) { //überspringt alle whitespaces, generiert tokens für invalid chars(error) und signs
    /*if (isEOF()) {
      return NULL;
    }*/
    c = getCurrentChar();
    currentLine   = getCurrentLine();
    currentColumn = getCurrentColumn();
    /*if (c == EOF) { // || c == '\0') {
      printf("EOF getNextToken! on line %d, column %d\n", currentLine, currentColumn);
      return createToken(EOFTYPE, 0, currentLine, currentColumn, "EOFTYPE");
    }*/

    /*if (isSpecial(c)) {
      printf("special char!\n");
      return createToken(EOFTYPE, 0, currentLine, currentColumn, "EOFTYPE");
    }*/

    //TODO  EOF ?

    //skip whitespace chars
    if(isWhitespace(c)) {
      next();
      continue;
    }

    //if char is invalid, print error message and create error token
    if(isInvalid(c)) {
      currentLine   = getCurrentLine();
      currentColumn = getCurrentColumn();
      printf("Invalid character (%c) on line %d, column %d\n", c, currentLine, currentColumn);
      next();
      return createToken(ERROR, 5, currentLine, currentColumn, "ERROR");
      //continue; //TODO einfach überspringen und das nächste korrekte Token zurückgeben ?
    }

    if(isSign(c)) {
      //if char is a sign that is guaranteed to be its own token
      if(isSingleSignToken(c)) {
        next();
        return createToken(getSingleSignTokenType(c), 1, currentLine, currentColumn, &c);
      }

      // 3 cases of ambiguity, tokenlengths for the different cases are known in advance
      // : = &
      if(isAmbiguousSign(c)) {
        // & must become &&
        if(c == '&') { 
          if(getCharByOffset(1) == '&') { //2 mal & -> korrektes AND-Token
            nextByOffset(2);
            return createToken(S_AND, 2, currentLine, currentColumn, "&&");
          }
          else {
            //& darf nicht einzeln vorkommen -> Fehler ausgeben, weiter tokenizen
            printf("Single & on line %d, column %d\n", currentLine, currentColumn);
            next();
            return createToken(ERROR, 5, currentLine, currentColumn, "ERROR"); //TODO errortoken ?
          }
        }

        // : can become :=
        if(c == ':') {
          if(getCharByOffset(1) == '=') {
            nextByOffset(2);
            return createToken(S_DIV_EQ, 3, currentLine, currentColumn, ":=");
          }
          else {
            next();
            return createToken(S_DIV, 3, currentLine, currentColumn, ":");
          }
        }

        // = can become =:=
        if(c == '=') { 
          if(getCharByOffset(1) == ':' && getCharByOffset(2) == '=') {
            nextByOffset(3);
            return createToken(S_EQ_DIV_EQ, 3, currentLine, currentColumn, "=:=");
          }
          else {
            next();
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
      //tokentype = identifyString(length, temp);
      nextByOffset(length);
      return createToken(identifyString(length, temp), length, currentLine, currentColumn, temp);
    }
    if(length == TOKENMAXLENGTH-1) { //if maxvalue of this loop is reached
      printf("TOKENMAXLENGTH reached. \n"); //TODO line column etc ausgeben
      //tokentype = identifyString(length, temp);
      //TODO return ERROR token or string token up to this point //identifier, so lange keywords gibts nicht
      nextByOffset(length);
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
      //tokentype = INTEGER;
      nextByOffset(length);
      return createToken(INTEGER, length, currentLine, currentColumn, temp);
    }
    if(length == TOKENMAXLENGTH-1) { //if maxvalue of this loop is reached
      printf("TOKENMAXLENGTH reached. \n"); //TODO line column etc ausgeben
      //tokentype = identifyString(length, temp);
      //TODO return ERROR token or string token up to this point //identifier, so lange keywords gibts nicht
      nextByOffset(length);
      return createToken(ERROR, 5, currentLine, currentColumn, "ERROR");
      //return createToken(type, length, currentLine, currentColumn, temp);
    }
  }
}


}