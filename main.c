#include <stdio.h>
//maximale token-länge = short_MAX bzw. 65 535
#include "globals.h"
#include "tokenize.h"
#include "tokenize.c"

#include "buffer.c"


int main() {
  //char filename[512] = "/home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/error-test-1.input.txt";
  char filename[512] = "/home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/error-test-2.input.txt";
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/error-test-1.input.txt
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/error-test-2.input.txt
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/simple-test-1.input.txt
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/simple-test-1.output.txt
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/simple-test-2.input.txt
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/simple-test-2.output.txt
  int i = 0;

  //INIT BUFFER
  initBuffer(filename);
  initTokenList();

  printWithNext();
  deinitBuffer();

  initBuffer(filename);

  //1. Tokenize; schleife bis EOF, getNextToken in Token-Linked List einfügen
  while(isNotFinished()) {
    
    //chars einlesen und entscheiden welcher tokentyp es ist, early out abbrechen wenn typ erkannt ist
    //TokenList.append(getNextToken()); //TODO c++ stil abändern
    token_t tempToken = getNextToken();

    appendTokenToList(tempToken);
    /*for(i=0; i<tempToken.length; i++) {
      next();
    }*/

    /*if(tempToken.type == EOFTYPE) {
      break;
    }*/
  }

  printTokenList();

  return 0;
}
