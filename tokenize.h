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
  tokennode_t *next;
  token_t      data;
}

static tokennode_t *startNode;

appendTokenToList(token_t tok) {
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

tokennode_t getCurrentNode() {

}

void printTokenList() {
  static tokennode_t *currentNode;
  static int index = 0;
  int i = 0;
  if(index == 0) {
    currentNode = startNode;
  }

  while(1) {
    printf("i: %8d ", index);
    printf(" line: %3d", currentNode->data.line);
    printf(" col: %3d", currentNode->data.column);
    printf(" length: %5d", currentNode->data.length);
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
  }
  

}

token_t createToken(tokentype_t type, unsigned short length, int line, int column, char *value) {
  token_t result;
  result.type = type;
  result.length = length;
  result.line = line;
  result.column = column;

  result.value = malloc(len+1);
  strncpy(result.value, value, len);

  return result;
}

#endif