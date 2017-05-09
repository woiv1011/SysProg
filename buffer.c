getCurrentIndex() {
  //returns the index of the current char from the beginning of the file
}

getCurrentLine() {

}

getCurrentColumn() {

}

char getNextChar() {
  char temp = 0;
  static int lineCount = 1;
  static int columnCount = 1;

  temp = currentChar;
  position++;

  return temp;
}

goToNext()

next()      //move 1 char to the right
//next(int i) //move i chars to the right, calls next() i times

previous() //move 1 char to the left
//previous(int i) //move i chars to the left, calls previous() i times

getCurrentChar()
getCurrentChar(int i)
oder
getCurrentCharOffset(int i)

//TODO auf Chars 1 und 2 rechts vom currentChar zugreifen können