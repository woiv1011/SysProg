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
    case ERROR: return "ERROR";
    case INTEGER: return "INTEGER";
    case IDENTIFIER: return "IDENTIFIER";

    case KW_WRITE: return "KW_WRITE";
    case KW_READ: return "KW_READ";
    case KW_INT: return "KW_INT";
    case KW_IF: return "KW_IF";
    case KW_ELSE: return "KW_ELSE";
    case KW_WHILE: return "KW_WHILE";

    case S_ADD: return "S_ADD";
    case S_SUB: return "S_SUB";               
    case S_MUL: return "S_MUL";
    case S_DIV: return "S_DIV";
    case S_EQ: return "S_EQ";                      
    case S_DIV_EQ: return "S_DIV_EQ";
    case S_EQ_DIV_EQ: return "S_EQ_DIV_EQ";

    case B_SQUARE_O: return "B_SQUARE_O";
    case B_SQUARE_C: return "B_SQUARE_C";               
    case B_CURLY_O: return "B_CURLY_O";
    case B_CURLY_C: return "B_CURLY_C";

    case B_ROUND_O: return "B_ROUND_O";                      
    case B_ROUND_C: return "B_ROUND_C";
    case B_ANGLE_O: return "B_ANGLE_O";
    case B_ANGLE_C: return "B_ANGLE_C";

    case EOFTYPE: return "EOFTYPE";

    //default:  //TODO print warning ? ist result 0 erlaubt, ohne schaden möglich ?
              //return NOTHING;
  }
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
  if (length == 2 && (strcmp(temp, "if") || strcmp(temp, "IF"))) {
    return KW_IF;
  }
  if (length == 4 && (strcmp(temp, "else") || strcmp(temp, "ELSE"))) {
    return KW_ELSE;
  }
  if (length == 5 && (strcmp(temp, "while") || strcmp(temp, "WHILE"))) {
    return KW_WHILE;
  }
  if (length == 3 && (strcmp(temp, "int"))) {
    return KW_INT;
  }
  if (length == 4 && (strcmp(temp, "read"))) {
    return KW_READ;
  }
  if (length == 5 && (strcmp(temp, "write"))) {
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

