/*Nochmals zur Aufgabe: Der Scanner liest nach der Aufforderung nextToken() solange mittels
getChar() das nächste Zeichen, bis er ein Zeichen oder einen Bezeichner erkannt hat. Ist
dieses ein Bezeichner, wird über die Symboltabelle mittels (insert) eine eindeutige Referenz
(inofKey) auf das eigentliche Informationsobjekt angefordert. Falls der Bezeichner neu war,
wird dieses erzeugt und mit dem Bezeichner verknüpft; ansonsten lediglich dessen Referenz
zurückgeliefert.*/


getNextToken() {
  char currentString[4096]; //maximum token length 4096
  char short currentPosition = 0;

  short currentLength;

  getNextChar();

}

