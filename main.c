
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kbuf.h"

void test_kbuf();


int main(int argc, char * argv[]) {
  
  
  test_kbuf();

  exit(EXIT_SUCCESS);
}


void test_kbuf() {
  kbuf * b;
  //Elementos de 16 bytes
  int elemsize = 64;
  
  b = kbuf_create(elemsize);
  
  if (b == 0) {
    fprintf(stderr, "Unable to create memory buffer\n");
    return;
  }
  
  printf("Requested size: %d\nBuffer size: %d\nStruct size: %d (0x%x)\nElements: %d\nAllocated: 0x%x\nData: 0x%x\nPages: %d\n", 
         elemsize, 
         KBUF_SIZE,
         sizeof(kbuf),
         sizeof(kbuf),
         b->total,
         (unsigned int)b, 
         (unsigned int)b->data,
         b->pages);
  
  
  printf("Allocated element: 0x%x\n", (unsigned int)kbuf_allocate(b));
  printf("Allocated element: 0x%x\n", (unsigned int)kbuf_allocate(b));
  printf("Allocated element: 0x%x\n", (unsigned int)kbuf_allocate(b));
  printf("Allocated element: 0x%x\n", (unsigned int)kbuf_allocate(b));
  
  kbuf_destroy(b);
}

