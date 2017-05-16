#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdio.h>
#include <stdlib.h> //malloc ?
#include <string.h> //strncpy ?


#include "globals.h"

#include "buffer.h"
//TODO move code to tokenize.c


typedef unsigned short tokentype_t;

typedef struct {
  tokentype_t  type; //16 bit; oberes/linkes byte für Kategorie, unteres/rechtes byte für Wert innerhalb Kategorie
  short        length; //aus wievielen chars besteht das token, fängt bei 1 an, kein "Stringende-Zeichen" notwendig, max 65536 tokenLength //TODO warnung und fehler ausgeben wenn tokenlength > MAX (beim lesen in getNextToken)
  char        *value; //string bei identifier / int
  int          line; //position des ersten chars des tokens
  int          column;
  //int          position; //notwendig ?
} token_t;


//TODO funktioniert das so ?
typedef struct tokenNode tokennode_t;
struct tokenNode{
  tokennode_t *next;
  token_t      data;
};

static tokennode_t *startNode;

void appendTokenToList(token_t tok);

void printTokenList();

token_t createToken(tokentype_t type, unsigned short length, int line, int column, char *value);

token_t getNextToken();
///


//return the next token from the char-array / c-string given though the parameters
//token_t contains token length (in characters / bytes) and token type
//wenn man struct = struct macht, werden alle werte korrekt  kopiert wie bei einer einzelnen variable ?

//#include "memory.h"

//creates and returns the single next token


#endif