
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kbuf.h"

void test_kbuf();
void imprimir_free_list();

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
  
  
  imprimir_free_list(b);
  for (size_t i = 0; i < b->total-1; i++)
  {
    printf("Allocated element %d: 0x%x\n", (i+1),(unsigned int)kbuf_allocate(b));
  }
  imprimir_free_list(b);
  //                  Primer prueba de liberar memoria
	int numIntentosLiberar = 3;
	unsigned int direccion; 
	for(int j=0; j<numIntentosLiberar; j++){
		printf("\nIngrese la direccion de memoria que desea liberar (sin anteponer 0x): ");
		scanf("%x",&direccion);
		kbuf_free(b, (void *)direccion);
		printf("\nCabeza de la lista: 0x%x\n", (unsigned int)b->free_list);
		printf("Number of elements available: %u\n", b->free);
	}
  imprimir_free_list(b);
   for (size_t i = 0; i < 5; i++)
  {
    printf("Allocated element %d: 0x%x\n", (i+1),(unsigned int)kbuf_allocate(b));
  }
  
  kbuf_destroy(b);
}

void imprimir_free_list(kbuf *b){
	unsigned int n = b->free;
	kitem *it = b->free_list;
  printf("free_list\n");
	for(int i=0; i<n; i++){	
		printf("0x%x\n", it);
		it = it->next;
	}
  printf("0x%x\n", it);
}

