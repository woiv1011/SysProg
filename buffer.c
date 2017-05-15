/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: woiv1011
 */
#include "buffer.h"


//STANDARD ACCESS

static int currentPosition; //maximal buffer_size mal 2 
static char next() {
	currentPosition++;

	if (currentPosition > BUFFER_SIZE - 1) { //currentBlockPosition >= 512 (0 bis 511 okay)
		Load NEw BLock
		update position
	}

	return getCurrentChar();
}
/*
static char previous(int a) {
	for (int i = 0; i < a; i++) {
		previous();
	}

	return getCurrent();
}*/

//GETTER / SETTER
static unsigned int getLength() { //??
	return length;
}

static unsigned int getCurrentLine() { //Performance schlecht; erster Block wird immer neu durchgegangen etc
	return currentLine;
}

static unsigned int getCurrentColumn() {
	return currentColumn;
}

//INTERNAL

static char getCurrentChar() {
	return block[currentBlock][currentBlockPosition];
	//return currentChar;
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


static void checkReload() {

}
static void readNewBlockFromFile() {
	FILE *fp;
	char filename[512];

	fp = fopen("/tmp/test.txt", "w+");

	//open for reading
	//read BLOCKSIZE charactersa
	//swap blocks and adjust position etc
	//if not enough chars in file anymore, set EOF

	//fprintf(fp, "This is testing for fprintf...\n");
	//fputs("This is testing for fputs...\n", fp);
	fclose(fp);
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

	// block[blockIndex] = (char*) ptr; //neuen Block zuweisen

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



static void printWithNext() {
	for (unsigned int i = 0; i <= length; i++) {
		printf("%c", next());
	}
	printf("\n\n");
}


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

