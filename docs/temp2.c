token_t getNextToken(char c*, int length) {
  char currentString[4096]; //maximum token length 4096
  char short currentPosition = 0;

  short currentLength;

  
  while(c[0] != EOF) {
    
    //chars einlesen und entscheiden welcher tokentyp es ist, early out abbrechen wenn typ erkannt ist
    getNextChar();
  }



//goto Version, goto is uniquely suited to implementing state machines
//dokumentation mit quote von und link zu stackoverflow
//states alphabetisch sortiert anordnen ?
int tokenLength = 0;
token_t result;
result.length = tokenLength;

start:
    tokenLength += 1;
    c = getNextChar(); //von Buffer; gleich an tempString anhängen ? oder erst nach termination strcpy ?
    if(isLetter(c)) {   
      goto letter;
    }
    if(isDigit(c)) {   
      goto digit;
    }
    if(isSign(c)) {
      goto sign;
    }
    if(isWhitespace(c)) {

    }
    if(isNothing(c)) {
      goto nothing;
    }


digit:


letter:

    if(isLetter(c) || isDigit(c)) {
      goto string;
    }
string:
    if(isLetter(c) || isDigit(c)) {
      goto string;
    }



tokenLength += 1;
c = getNextChar(); //von Buffer; gleich an tempString anhängen ? oder erst nach termination strcpy ?
switch(currentState) {
  case start:   
                break;
}


nothing:
  error:
    printf("Some Error Info.\n");
    return;

    

result.type = tokenType;
result.length = tokenLength;

return result;




}

short getSignTokenType(c,1) {

}

getNextToken2() {
  char c = 0;
  currentState = START;
  nextState = 0;
  token_t currentToken;

  c = getNextChar();

  while(isWhitespace(c)) {
    c = getNextChar();
  }

  switch(currentState) {

    case START:   if(isSign(c)) {
                    if(isSignSingle()) {
                        //einzelnes Zeichen, das ein eigenes Token darstellt +, -, *, :, <, >, =, :=, =:=, !, &&, ;, (, ), {, }, [, ]
                      currentToken.type = getSignTokenType(c,1);
                    }
                  }
                  if(isDigit) {
                    nextState = 
                  }
                  break; /* optional */
    case INTEGER:
      statement(s);
      break; /* optional */
    case STRING:
      statement(s);
      break; /* optional */
  }
}