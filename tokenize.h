#ifndef TOKENIZE_H
#define TOKENIZE_H

//TODO move code to tokenize.c

typedef tokentype_t short;

typedef token_t struct {
  tokentype_t  type; //16 bit; oberes/linkes byte für Kategorie, unteres/rechtes byte für Wert innerhalb Kategorie
  short        length; //aus wievielen chars besteht das token, fängt bei 1 an, kein "Stringende-Zeichen" notwendig, max 65536 tokenLength //TODO warnung und fehler ausgeben wenn tokenlength > MAX (beim lesen in getNextToken)
  char        *value; //string bei identifier / int
  int          line; //position des ersten chars des tokens
  int          column;
  //int          position; //notwendig ?
}

typedef tokennode_t struct {
  //long         index;
  tokennode_t *next;
  tokennode_t *previous;
  token_t      data;
}

token_t createToken(tokentype_t type, unsigned short length, int line, int column, char *value) {
  token_t result;
  result.type = type;
  result.length = length;
  result.line = line;
  result.column = column;

  result.value = malloc(len);
  strncpy(result.value, value, len);

  return result;
}

#endif