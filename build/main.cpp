#include <stdio.h>

//#include "../lib/lib.h"

#include "../modules/all.h"
//#include "../modules/buffer/buffer.h"
//#include "../modules/buffer/buffer.cpp"

int main ( int argc, char *argv[] ) { //argc = argument count, argv = 
  //printf("main start\n");

  if ( argc != 2 ) { //receive single file as argument to be compiled, argc should be 2 for correct execution
    //wrong number of arguments
    printf( "usage: %s filename", argv[0]); // print argv[0] assuming it is the program name
  }
  else {
    Buffer buf(argv[1]);

    /*printf("argc: %d\n", argc);
    for(int i=0; i<argc; i++) {
      printf("argv[%d]: %s\n", i, argv[i]);
    }*/

    while(!buf.isEOF()) {
      printf("%c", buf.next());
    }

    //getchar();
  }

  //printf("main end\n");
  return 0;
}