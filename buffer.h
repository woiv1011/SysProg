/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#ifndef BUFFER_H_
#define BUFFER_H_

#include "globals.h"



//CUSTOM
//#include <iostream>
#include <stdio.h>
#include <stdlib.h> //posix memalign
#include <unistd.h> //close file descriptor


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  //open odirect bla

#include <string.h>
//#include <cstdio> //fclose fopen etc; anscheinend nicht in iostream

//copied from fnctl.h
#ifndef O_DIRECT
#define O_DIRECT	00040000	/* direct disk access hint */
#endif

//notwendig ???
//using namespace std;

// O_DIRECT: The alignment of the user buffer and the file offset must all be multiples of the logical block size of the file system. Usually the logical block size are 512 Bytes.
// posix_memalign: The address of the allocated memory will be a multiple of alignment, which must be a power of two and a multiple of sizeof(void *).
#define BUFFER_SIZE 4096 //muss vielfaches von sizeof void* sein

struct position {
	unsigned int line;
	unsigned int column;
};

//class Buffer {
//private:
	static char* block[2];
	//unsigned short line[BUFFER_SIZE + BUFFER_SIZE];
	//unsigned short column[BUFFER_SIZE + BUFFER_SIZE];
	//position pos[2][BUFFER_SIZE];
	static unsigned int length;
	static unsigned int line[2][BUFFER_SIZE];
	static unsigned int column[2][BUFFER_SIZE];
	static int currentBlock;
	static int currentBlockPosition;
	static int inputFileDescriptor;
	static unsigned int lineOffset;
	static unsigned int columnOffset;
	static int eof; //end of file reached=1
	static int counter;
	static int isNew;

	static char getCurrent();
	static void checkReload();
	static void readBlockFromFile(unsigned int blockIndex);
	static void resetBlockPosition();
	static void calculatePosition();
	static unsigned int currentLine;
	static unsigned int currentColumn;

  //public:
	static void initBuffer(const char* filename);
	static void deinitBuffer();

	//STANDARD ACCESS
	static char next();
	//static char previous();
	//static char previous(int a);
	static bool isEOF();
	static bool isValid();

	//für Token-Textausgabe
	static unsigned int getCurrentLine();
	static unsigned int getCurrentColumn();

	//TESTING (INTERN)
	static unsigned int getLength();
	static void print();
	static void printWithNext();
	static void testStuff();
	static void printPosition();
//};

#endif /* BUFFER_H_ */
