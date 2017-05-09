
#define SIZE_THRESHOLD 4096



char* getMemory(length) {
  static char *memBlock;
  static int  remainingBytes = 0;

  if(remainingBytes <= SIZE_THRESHOLD) {
    memBlock = 
  }

   if(remaining < length) {
    //allocate new memory
    //was passiert mit dem alten ?
  }

  if(length > SIZE_THRESHOLD) { //wenn großer block verlangt, neu allokieren
    return malloc(length);
  }

 

}

//TODO linked list of memory blocks that have to be freed at the end of the program