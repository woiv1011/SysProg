/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "buffer.h"

//TODO line und column count optimieren
//TODO printToFIle
static void resetBlockPosition() {
	currentBlock = 0;
	currentBlockPosition = 0;
	isNew = 1;
}

//STANDARD ACCESS
static char next() {
	if (isNew) {
		isNew = 0;
	} else {
		currentBlockPosition++;
	}

	if (currentBlockPosition > BUFFER_SIZE - 1) { //currentBlockPosition >= 512 (0 bis 511 okay)
		currentBlock++;
		checkReload();
		currentBlockPosition = currentBlockPosition - BUFFER_SIZE;
	}

	return getCurrent();
}


static char previous() {
	if (isNew) {
		isNew = 0;
	} else {
		currentBlockPosition--;
	}

	if (currentBlockPosition <= -1) { //currentBlockPosition >= 512 (0 bis 511 okay)
		currentBlock = 0;
		currentBlockPosition = (BUFFER_SIZE - 1);
	}

	return getCurrent();
}
/*
static char previous(int a) {
	for (int i = 0; i < a; i++) {
		previous();
	}

	return getCurrent();
}*/

//GETTER / SETTER
static unsigned int getLength() {
	return length;
}

static unsigned int getCurrentLine() { //Performance schlecht; erster Block wird immer neu durchgegangen etc
	return line[currentBlock][currentBlockPosition];
}

static unsigned int getCurrentColumn() {
	return column[currentBlock][currentBlockPosition];
}

//INTERNAL
static char getCurrent() {
	return block[currentBlock][currentBlockPosition];
}

static char getCurrentChar() {
	next(); //init Buffer etc
	return previous();
	//return getCurrent();
}

//TODO optimize performance ?
static char getCharByOffset(unsigned char offset) {
	int i = 0;
	char tempChar = 0;
	int tempBlock;
	int tempBlockPosition;
	/*for(i=0; i<offset; i++) {
		next();
	}
	temp = getCurrentChar();
	for(i=0; i<offset; i++) {
		previous();
	}*/

	/*if(offset > 0) {
		temp = next(offset);
	}
	else {
		temp = previous(offset * (-1));
	}

	return temp;*/
	tempBlock = currentBlock;
	tempBlockPosition = currentBlockPosition;
	tempChar = next(offset);
	currentBlock = tempBlock;
	currentBlockPosition = tempBlockPosition;
	return tempChar;
}

static void calculatePosition() {
	unsigned int tempBlock = currentBlock; //Ursprungsposition zwischenspeichern um am Ende zur�ckzukehren
	unsigned int tempBlockPosition = currentBlockPosition;

	unsigned int lineCounter = lineOffset;
	unsigned int columnCounter = columnOffset;

	for (int i = 0; i < 2; i++) { //Block 0 1
		for (int j = 0; j < BUFFER_SIZE; j++) { //inside Block
			if (block[i][j] == '\n') { //if
				line[i][j] = lineCounter;
				column[i][j] = columnCounter;
				columnCounter = 1;
				lineCounter++;
			} else {
				line[i][j] = lineCounter;
				column[i][j] = columnCounter;
				columnCounter++;
			}
		}
	}

	// Fixed wrong line calculation when the last character of block 0 is \n
	lineOffset = line[1][0];
	columnOffset = column[1][0];

	///////////////////////
	currentBlock = tempBlock; //Position wiederherstellen
	currentBlockPosition = tempBlockPosition;
}

static void checkReload() {
	if (currentBlock > 1) { // wenn zu klein, nachladen

		// Swap blocks instead of reloading
		char * tmp = block[0];
		block[0] = block[1];
		block[1] = tmp;

		currentBlock = 1;
		//currentBlockPosition = 0;
		readBlockFromFile(1);
	}

	/*
	 startColumn = pos[0][BUFFER_SIZE-1].column;
	 startLine = pos[0][BUFFER_SIZE-1].line;*/

	/*for(int i=0; i<BUFFER_SIZE; i++) {
	 pos[1][i] = pos[1][i] =
	 }*/
	//block 1 mit line und cloumncount belegen
}

static void readBlockFromFile(unsigned int blockIndex) { //reads a BUFFER_SIZE -bytes sized block from the file and insert inserts it into block blockIndex
	void * ptr; //Ziel-Speicherbereich
	void ** ptrptr = &ptr; //pointerpointer auf Zielspeicherbereich f�r posix_memalign

	int sizeRead = 0; //Anzahl der erfolgreich gelesenen Zeichen
	int err = 0; //Fehlernumer; bis jetzt nicht verwendet

	//int tempBlock; //Zwischenspeicher f�r Position wegen Offset-Adjust
	//int tempBlockPosition;

	// Use the last block for storing data, instead of creating a new one. The blocks were swapped before.
//	err = posix_memalign(ptrptr, BUFFER_SIZE, BUFFER_SIZE);
	ptr = block[blockIndex];
//	memset(ptr, 0, BUFFER_SIZE);
	sizeRead = read(inputFileDescriptor, ptr, BUFFER_SIZE);

	//TODO adjustOffset

	//offset adjust Funktioniert nur wenn Block 1 neu geladen wird
	/*if(isNew == 0) {
	 tempBlock = currentBlock; //Position zwischenspeichern
	 tempBlockPosition = currentBlockPosition;

	 currentBlock = 0; //Offset = Position des letzten Chars im zu ersetzenden / l�schenden Block
	 currentBlockPosition = BUFFER_SIZE - 1;
	 lineOffset = getCurrentLine();
	 columnOffset = getCurrentColumn();

	 cout	<< endl
	 << "LineOffset: "
	 << lineOffset
	 << "ColumnOffset: "
	 << columnOffset
	 << endl;


	 currentBlock = tempBlock; //Position wiederhestellen
	 currentBlockPosition = tempBlockPosition;
	 }*/

	// block[blockIndex] = (char*) ptr; //neuen Block zuweisen

	if (!isNew) {
		calculatePosition();
	}

	if (sizeRead > 0) {
		length += sizeRead;
	}

	if (sizeRead < BUFFER_SIZE) {
		eof = 1;

		// Clear the unused memory
		memset(block[blockIndex] + sizeRead, 0, BUFFER_SIZE - sizeRead);
	}

	if (sizeRead == -1 || err != 0) {
		//Fehler
		//cout << endl << "Fehler!" << endl;
		printf("\nFehler in readBlockFromFile!\n");
	}

	/*cout << endl //Testausgabe
	 << endl
	 << "readBlock: " ////
	 << blockIndex
	 << " SizeRead:"
	 << sizeRead
	 << " Length:"
	 << length
	 << endl
	 << endl;*/
}

//TESTING
/*void Buffer::print() {
	cout << endl;

	for (int i = 0; i <= 1; i++) {
		cout << "block: "
				<< i
				<< " strlen:"
				<< strnlen(block[i], BUFFER_SIZE)
				<< endl
				<< block[i]
				<< endl
				<< endl;
	}

	cout << "eof: "
			<< eof
			<< endl;
}*/

static void printWithNext() {
	for (unsigned int i = 0; i <= length; i++) {
		printf("%c", next());
	}
	printf("\n\n");
}

/*
void Buffer::testStuff() {
	cout << endl << "TestSTUFF: " << endl;

	next(); // Initialize that the first character is the current one.

	for (unsigned int i = 0; i <= length; i++) {

		cout << "c: "
				<< getCurrent()
				<< "\tline: "
				<< getCurrentLine()
				<< "\tcol: "
				<< getCurrentColumn()
				<< (isEOF() ? "\tEnd of file" : "\tMore chars")
				<< endl;
		next();
	}

	cout << endl << endl;

}

void Buffer::printPosition() {
	for (int i = 0; i <= currentBlock; i++) { //Block 0 1
		for (int j = 0; j <= currentBlockPosition; j++) { //inside Block
			cout << "Char: "
					<< block[i][j]
					<< "\tLine: "
					<< line[i][j]
					<< "\tCol: "
					<< column[i][j]
					<< endl;
		}
	}
}*/

static bool isValid() {
	return !(inputFileDescriptor < 0);
}

//CONSTRUCTOR / DESTRUCTOR
static void initBuffer(const char* filename) {
	length = 0;
	counter = 0;
	eof = 0;

	currentBlock = 0;
	currentBlockPosition = 0;

	block[0] = NULL;
	block[1] = NULL;

// Reserve memory at buffer initialization.
	int err = 0; //Fehlernumer; bis jetzt nicht verwendet
	void * ptr; //Ziel-Speicherbereich
	void ** ptrptr = &ptr; //pointerpointer auf Zielspeicherbereich f�r posix_memalign

	err = posix_memalign(ptrptr, BUFFER_SIZE, BUFFER_SIZE);
	block[0] = (char*) ptr; //neuen Block zuweisen
	err = posix_memalign(ptrptr, BUFFER_SIZE, BUFFER_SIZE);
	block[1] = (char*) ptr; //neuen Block zuweisen

	currentLine = 1;
	currentColumn = 1;
	lineOffset = 1;
	columnOffset = 1;
	isNew = 1;

	//inputFileDescriptor = open(filename, O_RDONLY | O_DIRECT);
	inputFileDescriptor = open(filename, O_RDONLY);

	// check if the file is valid for reading
	if (inputFileDescriptor < 0) {
		eof = 1;
		return;
	}

	readBlockFromFile(0); //f�lle beide Blocks
	readBlockFromFile(1);

//	isNew = 0;
//	if(length >= BUFFER_SIZE) {
//		calculatePosition(); //crash vielleicht wenn keine zwei vollen Bl�cke geladen werden k�nnen
//	}

	//printWithNext();
	calculatePosition();
	resetBlockPosition();

	//printWithNext();
	//testStuff();

	//printPosition();
}

static void deinitBuffer() {
	close(inputFileDescriptor);
	free(block[0]);
	free(block[1]);
}

static bool isEOF() {
	return ((eof == 1) && (getCurrent() == '\0'));
	//return ((eof == 1) || (getCurrent() == '\0'));
}

