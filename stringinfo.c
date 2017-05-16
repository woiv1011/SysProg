#include "stringinfo.h"
#include "globals.h"

//SINGLE CHAR start
bool isSpecial(char c) {
  return (c == '\0' || c == EOF);
}

bool isInvalid(char c) {
  //if (c >= 128) {
  //  return false;
  //}
  return (!isWhitespace(c) && !isSign(c) && !isDigit(c) && !isLetter(c) && !isSpecial(c)); //muss alle optionen beinhalten, digit, letter, sign, whitespace
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

//+, -, *, :, <, >, =, :=, =:=, !, &&, ;, (, ), {, }, [, ]
bool isSign(char c) {
  //TODO als Intervall abfragen möglich ?, macht compiler evtl automatisch
  return (c == '+' || c == '-' || c == '*' || c == ':' || c == '=' || c == '!' || c == '&' || c == ';' ||
          c == '(' || c == ')' || c == '{' || c == '}' || c == '<' || c == '>' || c == '[' || c == ']');
}


/*bool isSingleSignToken(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '!' || c == ';' ||
          c == '(' || c == ')' || c == '{' || c == '}' || c == '<' || c == '>' || c == '[' || c == ']');
}*/

/** returns true if c is a sign that is guaranteed to be its own, single-char token
*/
bool isSingleSignToken(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '!' || c == ';' ||
          c == '(' || c == ')' || 
          c == '{' || c == '}' || 
          c == '<' || c == '>' || 
          c == '[' || c == ']');
}

bool isAmbiguousSign(char c) {
  return (c == ':' || c == '&' || c == '='); //: kann zu := werden; & muss zu && werden; = kann zu =:= werden
}

char* tokenTypeToString(tokentype_t toktype) {
  char *temp;
  temp = malloc(15);
  switch(toktype) {
    case ERROR: temp =  "ERROR"; break;
    case INTEGER: temp =  "INTEGER"; break;
    case IDENTIFIER: temp =  "IDENTIFIER"; break;

    case KW_WRITE: temp =  "KW_WRITE"; break;
    case KW_READ: temp =  "KW_READ"; break;
    case KW_INT: temp =  "KW_INT"; break;
    case KW_IF: temp =  "KW_IF"; break;
    case KW_ELSE: temp =  "KW_ELSE"; break;
    case KW_WHILE: temp =  "KW_WHILE"; break;

    case S_ADD: temp =  "S_ADD"; break;
    case S_SUB: temp =  "S_SUB"; break;               
    case S_MUL: temp =  "S_MUL"; break;
    case S_DIV: temp =  "S_DIV"; break;
    case S_EQ: temp =  "S_EQ"; break;                      
    case S_DIV_EQ: temp =  "S_DIV_EQ"; break;
    case S_EQ_DIV_EQ: temp =  "S_EQ_DIV_EQ"; break;
    case S_NOT: temp =  "S_NOT"; break;                      
    case S_AND: temp =  "S_AND"; break;
    case S_SEMICOLON: temp =  "S_SEMICOLON"; break;

    case B_SQUARE_O: temp =  "B_SQUARE_O"; break;
    case B_SQUARE_C: temp =  "B_SQUARE_C"; break;               
    case B_CURLY_O: temp =  "B_CURLY_O"; break;
    case B_CURLY_C: temp =  "B_CURLY_C"; break;

    case B_ROUND_O: temp =  "B_ROUND_O"; break;                      
    case B_ROUND_C: temp =  "B_ROUND_C"; break;
    case B_ANGLE_O: temp =  "B_ANGLE_O"; break;
    case B_ANGLE_C: temp =  "B_ANGLE_C"; break;

    case EOFTYPE: temp =  "EOFTYPE"; break;

    //default:  //TODO print warning ? ist result 0 erlaubt, ohne schaden möglich ?
              //temp =  NOTHING;
  }
  return temp;
}

//+, -, *, :, <, >, =, :=, =:=, !, &&, ;, (, ), {, }, [, ]


//TODO string compare end
/*isEqualString(const char* s1, const char * s2) {
  int temp = 0;
  temp = strcmp(s1, s2);
  return (temp == 1); 
}*/

/**
*   when the string token is terminated by a new token, whitespace, etc
*   this function determines whether it is an identifier with only letters or a keyword and returns the corresponding token/ tokenType?
*/
tokentype_t identifyString(int length, char *c) {
  //"fOr", "FoR", etc nicht erlaubt, upper lowercase muss gleichbleiben
  //mixed upper-/lowercase is not allowed -> no fOr, FOr, whilE, etc
  //TODO warning bzw compilerfehler ausgeben wenn gemischt upper-lower oder write/read uppercase ?
  //TODO strcmp rückgabewert und, gibt strcmp die Anzahl der ungleichheiten bzw fehler zurück ?
  //tokentype_t result = 0; //tokentype_t = short
  char *temp = malloc(length+1); //convert parameters into proper c string
  strncpy(temp, c, length);
  temp[length] = '\0';

  //TODO replace with strNcmp
  if (length == 2 && ((strncmp(temp, "if", 2) == 0) || (strncmp(temp, "IF", 2) == 0))) {
    return KW_IF;
  }
  if (length == 4 && ((strncmp(temp, "else", 4) == 0) || (strncmp(temp, "ELSE", 4) == 0))) {
    return KW_ELSE;
  }
  if (length == 5 && ((strncmp(temp, "while", 5) == 0) || (strncmp(temp, "WHILE", 5) == 0))) {
    return KW_WHILE;
  }
  if (length == 3 && (strncmp(temp, "int", 3) == 0)) {
    return KW_INT;
  }
  if (length == 4 && (strncmp(temp, "read", 4) == 0)) {
    return KW_READ;
  }
  if (length == 5 && (strncmp(temp, "write", 5) == 0)) {
    return KW_WRITE;
  }

  return IDENTIFIER;
}

/**
*   when the string token is terminated by a new token, whitespace, etc
*   this function determines whether it is an identifier with only letters or a keyword and returns the corresponding token/ tokenType?
*/
tokentype_t getSingleSignTokenType(char c) {
  switch(c) {
    case '+': return S_ADD;
    case '-': return S_SUB;
    case '*': return S_MUL;
    case '!': return S_NOT;
    case ';': return S_SEMICOLON;
    case '(': return B_ROUND_O;
    case ')': return B_ROUND_C;
    case '{': return B_CURLY_O;               
    case '}': return B_CURLY_C;
    case '<': return B_ANGLE_O;
    case '>': return B_ANGLE_C;                      
    case '[': return B_SQUARE_O;
    case ']': return B_SQUARE_C;
    //default:  //TODO print warning ? ist result 0 erlaubt, ohne schaden möglich ?
              //return NOTHING;
  }
  //return ERROR;
}

