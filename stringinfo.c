//SINGLE CHAR start
bool isNothing(char c) {
  //if (c >= 128) {
  //  return false;
  //}
  return (!isWhitespace() && !isSign() && !isDigit() && !isLetter()); //muss alle optionen beinhalten, digit, letter, sign, whitespace
}

bool isDigit(char c) {
  return ((c>='0' && c<= '9'));
}

bool isLetter(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isWhitespace(char c) {
  return (c ==' ' || c =='\n' || c =='\t');
  //return (c == 32 || c ==XX || c== YY); //falls oberes nicht funktioniert
}

bool isSign(char c) {
  //TODO als Intervall abfragen möglich ?, macht compiler evtl automatisch
  return (c == '+' || c == '-' || c == '*' || c == ':' || c == '=' || c == '!' || c == '&' || c == ';' ||
          c == '(' || c == ')' || c == '{' || c == '}' || c == '<' || c == '>' || c == '[' || c == ']');
}

/** c is a sign that is guaranteed to be its own, single-char token
*/
bool isSingleSignToken(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '!' || c == ';' ||
          c == '(' || c == ')' || c == '{' || c == '}' || c == '<' || c == '>' || c == '[' || c == ']');
}

//+, -, *, :, <, >, =, :=, =:=, !, &&, ;, (, ), {, }, [, ]


bool isSignString() {
  //
}


//+, -, *, :, <, >, =, :=, =:=, !, &&, ;, (, ), {, }, [, ]


//TODO string compare end
isEqualString(const char* s1, const char * s2) {
  int temp = 0;
  temp = strcmp(s1, s2);
  return (temp == 1); 
}

/**
*   when the string token is terminated by a new token, whitespace, etc
*   this function determines whether it is an identifier with only letters or a keyword and returns the corresponding token/ tokenType?
*/
tokentype_t identifyString(int length, char *c) {
  //"fOr", "FoR", etc nicht erlaubt, upper lowercase muss gleichbleiben
  //mixed upper-/lowercase is not allowed -> no fOr, FOr, whilE, etc
  //TODO warning bzw compilerfehler ausgeben wenn gemischt upper-lower oder write/read uppercase ?
  //TODO strcmp rückgabewert und, gibt strcmp die Anzahl der ungleichheiten bzw fehler zurück ?
  tokentype_t result = 0; //tokentype_t = short

  //TODO replace with strNcmp
  if (length == 2 && (strcmp(string, "if") || strcmp(string, "IF"))) {
    result = KEYWORD & KW_IF;
  }
  if (length == 4 && (strcmp(string, "else") || strcmp(string, "ELSE"))) {
    result = KEYWORD & KW_IF;
  }
  if (length == 5 && (strcmp(string, "while") || strcmp(string, "WHILE"))) {

  }
  if (length == 3 && (strcmp(string, "int")) {

  }
  if (length == 4 && (strcmp(string, "read")) {

  }
  if (length == 5 && (strcmp(string, "write")) {

  }

  else {
    tokenType = identifier
  }
  

}

/**
*   when the string token is terminated by a new token, whitespace, etc
*   this function determines whether it is an identifier with only letters or a keyword and returns the corresponding token/ tokenType?
*/
tokentype_t getSingleSignTokenType(char c) {
  tokentype_t result = 0; //tokentype_t = short
  switch(c) {
    case '+': result = S_ADD;
              break;
    case '-': result = S_SUB;
              break;
    case '*': result = S_MUL;
              break;

    case '!': result = S_NOT;
              break;
    case ';': result = S_SEMICOLON;
              break;

    case '(': result = B_ROUND_O;
              break;
    case ')': result = B_ROUND_C;
              break;
    case '{': result = B_CURLY_O;
              break;                           
    case '}': result = B_CURLY_C;
              break;    
    case '<': result = B_ANGLE_O;
              break;    
    case '>': result = B_ANGLE_C;
              break;                                    
    case '[': result = B_SQUARE_O;
              break;         
    case ']': result = B_SQUARE_C;
              break;
    default:  //TODO print warning ? ist result 0 erlaubt, ohne schaden möglich ?
  }
  
  return result;
}

bool isSingleSignToken(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '!' || c == ';' ||
          c == '(' || c == ')' || 
          c == '{' || c == '}' || 
          c == '<' || c == '>' || 
          c == '[' || c == ']');
}