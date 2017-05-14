#include <stdio.h>
//maximale token-länge = short_MAX bzw. 65 535
#include "globals.h"

#include "bufferTemp.c"


int main() {
  char filename[512] = "/home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/error-test-1.input.txt";
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/error-test-1.input.txt
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/error-test-2.input.txt
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/simple-test-1.input.txt
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/simple-test-1.output.txt
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/simple-test-2.input.txt
//  /home/ravi/Desktop/Systemnahes-Programmieren/Test/parser/simple-test-2.output.txt

  //INIT BUFFER
  initBuffer(filename);

//1. Tokenize; schleife bis EOF, getNextToken in Token-Linked List einfügen
while(!isEofReached()) {
    
    //chars einlesen und entscheiden welcher tokentyp es ist, early out abbrechen wenn typ erkannt ist
    //TokenList.append(getNextToken()); //TODO c++ stil abändern
    appendTokenToList(getNextToken());
}


  return 0;
}
