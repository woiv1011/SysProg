#include <stdio.h>

int main() {
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
  int i = 0;
  for (i=0; i<=255; i++) {
    printf("i: %d char: %c\n", i, i);
  }

  return 0;
}