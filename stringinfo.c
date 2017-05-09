//SINGLE CHAR start
bool isNothing(char c) {
  //if (c >= 128) {
  //  return false;
  //}
  return (!isDigit() && !isLetter() && !isSign()); //muss alle optionen beinhalten, digit, letter, sign, whitespace
}

bool isDigit(char c) {
  return ((c>='0' && c<= '9'));
}

bool isLetter(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isWhitespace(char c) {
  if (c ==' ' || c =='\n' || c =='\t') {
  //if (c == 32 || c ==XX || c== YY) {
    return true;
  }
  else  {
    return false;
  }
}

bool isSignChar(char c) {
  //TODO als Intervall abfragen möglich ?, macht compiler evtl automatisch
  return (c == '+' || c == '-' || c == '*' || c == ':' || c == '=' || c == '!' || c == '&' || c == ';' ||
          c == '(' || c == ')' || c == '{' || c == '}' || c == '<' || c == '>' || c == '[' || c == ']');
}

/** c is a sign that is guaranteed to be its own, single-char token
*/
bool isSignSingle(char c) {
  if (c == '+' || c == '-' || c == '*' || c == '<' || c == '>' || c == '9') {
    return true;
  }
  else {
    return false;
  }
}

+, -, *, :, <, >, =, :=, =:=, !, &&, ;, (, ), {, }, [, ]



bool isSign(char c) {
  if (c == '+' || c == '-' || c == '*' || c == ':' || c == '<' || c == '>' || c == '9') {
    return true;
  }
  else {
    return false;
  }
}

bool isSignSingle(char c) {
  if (c == '+' || c == '-' || c == '*' || c == '<' || c == '>' || c == '9') {
    return true;
  }
  else {
    return false;
  }
}

bool isSignString() {
  //
}


+, -, *, :, <, >, =, :=, =:=, !, &&, ;, (, ), {, }, [, ]



bool isKeywordIF(char c*, int length) {
 //TODO erst rauskopieren in eigenten String damit es \0 gibt und strcmp nicht endlos weiterläuft
  strcmp(c)



  if ((c[0] == 'i' || c[0] == 'I') &&
      (c[1] == 'f' || c[0] == 'F') &&
      (isWhitespace(c[2])        )
     ) {
    return true;
  }
  else {
    return false;
  }

  //TODO stattdessen mit strcmp oder so
}

tokenType identifyKeyword() {
  
}




//TODO string compare end
isEqualString(const char* s1, const char * s2) {
  int temp = 0;
  temp = strcmp(s1, s2);
  return (temp == 1); 
}

tokenType identifyString(int length, char *c) {
  //"fOr", "FoR", etc nicht erlaubt, upper lowercase muss gleichbleiben
  //mixed upper-/lowercase is not allowed -> no fOr, FOr, whilE, etc
  //TODO warning bzw compilerfehler ausgeben wenn gemischt upper-lower oder write/read uppercase ?
  //TODO strcmp rückgabewert und, gibt strcmp die Anzahl der ungleichheiten bzw fehler zurück ?
  if (length == 2 && (strcmp(string, "if") || strcmp(string, "IF"))) {

  }
  if (length == 4 && (strcmp(string, "else") || strcmp(string, "ELSE"))) {

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