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


  //1. parse command line parameters / main parameters (mainly filename)

  //2. read chars from the given file into/through the buffer
  //3. separate char array into a linked list (?) of tokens

  //bezeichner sammeln und abspeichern mit Informationen (Typ,	Name,	Anzahl	der	Argumente	usw. in der Symboltabelle)
  //initialisierung der Symboltabelle und Verbindungsherstellung zu Tokens ist Aufgabe des Scanners
  /*Dabei	ist	es	entscheidend,	dass	vorhandene	
Informationen	schnell	extrahiert	und	neue	
Informationen	schnell	abgespeichert	werden	
können.*/
/*In	der	Symboltabelle	wird	immer	dann	gesucht,	wenn	im	Quelltext	ein	Lexem,	
das	für	einen	Bezeichner	steht,	gefunden	wurde.	
• Änderungen	treten	in	der	Tabelle	auf,	wenn	ein	neuer	Bezeichner	oder	neue	
Informationen	über	einen	existierenden	Bezeichner	gefunden	werden.*/

  //4. (???) check the order of that list for correctness
  /*int i = 0;
  for (i=0; i<=255; i++) {
    printf("i: %d char: %c\n", i, i);
  }*/

//1. Tokenize: read chars from buffer into statemachine and output tokens, generate tokenlist
//2. check order of tokens with regular grammar
//3. build syntax tree
//4. generate code