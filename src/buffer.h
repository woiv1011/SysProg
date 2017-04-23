/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#ifndef BUFFER_H_
#define BUFFER_H_

//CUSTOM
#include <iostream>
#include <string.h>
#include <cstdio> //fclose fopen etc; anscheinend nicht in iostream
#include <fcntl.h> //open odirect bla
#include <unistd.h> //close file descriptor
#include <stdlib.h> //posix memalign

//notwendig ???
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

// O_DIRECT: The alignment of the user buffer and the file offset must all be multiples of the logical block size of the file system. Usually the logical block size are 512 Bytes.
// posix_memalign: The address of the allocated memory will be a multiple of alignment, which must be a power of two and a multiple of sizeof(void *).
#define BUFFER_SIZE 4096 //muss vielfaches von sizeof void* sein

struct position {
	unsigned int line;
	unsigned int column;
};

class Buffer {
private:
	char* block[2];
	//unsigned short line[BUFFER_SIZE + BUFFER_SIZE];
	//unsigned short column[BUFFER_SIZE + BUFFER_SIZE];
	//position pos[2][BUFFER_SIZE];
	unsigned int length;
	unsigned int line[2][BUFFER_SIZE];
	unsigned int column[2][BUFFER_SIZE];
	int currentBlock;
	int currentBlockPosition;
	int inputFileDescriptor;
	unsigned int lineOffset;
	unsigned int columnOffset;
	int eof; //end of file reached=1
	int counter;
	int isNew;

	char getCurrent();
	void checkReload();
	void readBlockFromFile(unsigned int blockIndex);
	void resetBlockPosition();
	void calculatePosition();
	unsigned int currentLine;
	unsigned int currentColumn;

public:
	Buffer(const char* filename);
	virtual ~Buffer();

	//STANDARD ACCESS
	char next();
	char previous();
	char previous(int a);
	bool isEOF();
	bool isValid();

	//für Token-Textausgabe
	unsigned int getCurrentLine();
	unsigned int getCurrentColumn();

	//TESTING (INTERN)
	unsigned int getLength();
	void print();
	void printWithNext();
	void testStuff();
	void printPosition();
};

#endif /* BUFFER_H_ */
