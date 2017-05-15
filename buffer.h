#ifndef BUFFER_H_
#define BUFFER_H_

#include "globals.h"


#include <stdio.h>
#include <stdlib.h>

#include <string.h>

/*
#include <unistd.h> //close file descriptor
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  //open odirect bla
*/


#define BUFFER_SIZE 4096 //muss vielfaches von sizeof void* sein

static FILE *filepointer;

char* block1;
char* block2;

unsigned int currentPosition;
unsigned int currentLine;
unsigned int currentColumn;

unsigned int eof;
unsigned int length;
unsigned int counter;

static inline char getCurrentChar();
static inline char getCharByOffset(unsigned char offset);
static inline char getCharByPosition(unsigned short position);

static char next();
static char nextByOffset(unsigned short offset);
static bool isEOF();
static bool isNotFinished();

static unsigned int getCurrentLine();
static unsigned int getCurrentColumn();

static void printWithNext();

static void readBlockFromFile();

static void initBuffer(const char* filename);
static void deinitBuffer();

#endif /* BUFFER_H_ */
