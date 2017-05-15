#include "buffer.h"





//TODO update position when loading new block


static bool isNotFinished() {
	return (counter < length);
}



static void printWithNext() {
	for (unsigned int i = 0; isNotFinished(); i++) {
	//for (unsigned int i = 0; i<=10000; i++) {
		printf("%c", next());
	}
	printf("\n\n");
}


//STANDARD ACCESS


static char next() {
	char temp = getCurrentChar();
	counter++;

	//check whether previous char was a newline to adjust line and column count
	if(temp == '\n') {
		currentLine++;
		currentColumn = 1;
	}
	else {
		currentColumn++;
	}

	if (currentPosition > (BUFFER_SIZE - 260)) { // unsigned char (256) offset möglich in getCharByOffset()
		readBlockFromFile();
	}

	currentPosition++;
	return getCurrentChar();
}

static char nextByOffset(unsigned short offset) {
	int i = 0;
	for (i = 0; i<offset; i++) {
		next();
	}
}

static unsigned int getCurrentLine() {
	return currentLine;
}

static unsigned int getCurrentColumn() {
	return currentColumn;
}

//INTERNAL
static bool isEOF() {
	//return ((eof == 1) && (getCurrentChar() == '\0'));
	//return ((eof == 1) || (getCurrent() == '\0'));
	//return feof(filepointer);
	return eof;
	//return (getCurrentChar() == EOF);
}

static inline char getCurrentChar() {
	return getCharByPosition(currentPosition);
	//return currentChar;
}


static inline char getCharByOffset(unsigned char offset) {
	return getCharByPosition(currentPosition + offset);
}


static inline char getCharByPosition(unsigned short position) {
	if(position > BUFFER_SIZE) {
		return block2[position - BUFFER_SIZE];
	}
	else {
		return block1[position];
	}
}

//////////////////////

//reads a block of memory with size BUFFER_SIZE (bytes) from the file and swaps the memory blocks
static void readBlockFromFile() {
	size_t sizeRead = 0; //Anzahl der erfolgreich gelesenen Zeichen

	block1 = block2;
	block2 = memset(block2, 0, BUFFER_SIZE); //overwrite block with zeros
  sizeRead = fread(block2, 1, BUFFER_SIZE, filepointer);

	length += sizeRead;

	//position = position - BUFFER_SIZE;
	currentPosition -= BUFFER_SIZE;

	if ( ferror(filepointer) != 0 ) {
		fputs("Error reading file", stderr);
	}

	if ((sizeRead < BUFFER_SIZE)) {
		eof = 1;
		//fputs("Buffer EOF reached", stderr);
		//printf("Buffer EOF reached\n");
	}
}

//CONSTRUCTOR / DESTRUCTOR
static void initBuffer(const char* filename) {
	size_t sizeRead = 0; //Anzahl der erfolgreich gelesenen Zeichen
	length = 0;
	counter = 0;

	//allocate memory for both blocks
	block1 = malloc(BUFFER_SIZE);
	block2 = malloc(BUFFER_SIZE);

	filepointer = fopen(filename, "r"); //fp = fopen("foo.txt", "r");

	if (filepointer == NULL || ferror(filepointer)) {
		//fputs("Error openinf file", stderr);
		printf("Error opening file\n");
		return;
	}
	//else {
		block1 = memset(block1, 0, BUFFER_SIZE); //overwrite block with zeros
		sizeRead = fread(block1, 1, BUFFER_SIZE, filepointer);

	if ((sizeRead < BUFFER_SIZE)) {
		eof = 1;
		//printf("Buffer EOF reached\n");
		//fputs("Buffer EOF reached", stderr);
	}

	length += sizeRead;

		currentPosition = 0;
		currentColumn = 1;
		currentLine = 1;
		eof = 0;
	//}


}


static void deinitBuffer() {
	//close(inputFileDescriptor);
	fclose(filepointer);
	free(block1);
	free(block2);
}



