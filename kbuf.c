

/**
 * @file kbuf.c
 * @author Kevin Stiven Jimenez Perafan (kjimenez@univirtual.edu.co)
 * @brief 
 * @version 0.1
 * @date 2023-01-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "kbuf.h"

kbuf * kbuf_create(unsigned int elemsize) {  
  // Redondear elemsize a una potencia de 2 hacia arriba
  unsigned int rounded_elemsize = pow(2, ceil(log2(elemsize)));
  int pages;
  // Reservar memoria para la estructura kbuf
  kbuf * ret = 0;
  kitem * item = 0;
  // 1. Calcular el tamano real que ocupa cada item dentro del buffer.
  //    Para items de 1, 2 o 4 bytes, se deberaa tomar un apuntador de
  //    tipo kitem.
  if (rounded_elemsize > (sizeof(kitem)))
  {
    rounded_elemsize = sizeof(kitem);
  }
  //2. Calcular la cantidad de paginas (de PAGE_SIZE) de se necesitan
  //   para almacenar la estructura de tipo kbuf y al menos un item.
  pages = 1;
  if (rounded_elemsize >= (PAGE_SIZE/2))
  {
    rounded_elemsize = pow(2, ceil(log2(PAGE_SIZE)));
    pages = pages + (rounded_elemsize/PAGE_SIZE);
  }
  //3. Solicitar la memoria
  ret = (kbuf *)malloc(pages*PAGE_SIZE);
  ret->elemsize = elemsize;
  ret->size = rounded_elemsize;
  //4. Almacenar la estructura al inicio de la memoria asignada (linea 42)
  //   Se debe colocar un apuntador de tipo kbuf al inicio de la
  //   memoria obtenida, e inicializar los atributos de esa estructura
  
  // Inicializar campos de la estructura kbuf
  ret->total = KBUF_SIZE/ret->size;// TODO: verificar
  unsigned int ocupados_kbuf = sizeof(kbuf)/ret->size;
	if(sizeof(kbuf) % ret->size != 0){
		ocupados_kbuf++;
	}
  ret->free = ret->total - ocupados_kbuf;
  printf("\nElements in one page: %u", ret->free);
	
  ret->data = (char *) ret;
  printf("\nAllocated page: 0x%x", (unsigned int)ret->data);
  unsigned int addr;
  addr = ((unsigned int)ret->data)+(ocupados_kbuf*ret->size);
  if (ret->size >= (PAGE_SIZE/2))
  {
    addr+=4;
  }
  printf("\nFirst item at: 0x%x \n", addr);
	item = (kitem *)addr;
	ret->free_list = item;
  //ITERAR: cada item(hasta el penultimo) apunta a la direccion del siguiente item.
	//El ultimo item tiene como siguiente NULL.
  unsigned int n = ret->free;
	for(int i=0; i<(n-1); i++){
		item->next = (void*)(((unsigned int)item)+ret->size);
		//printf("\nDireccion item[%d]: 0x%x\n", i+1, (unsigned int)it);
		item = item->next;
	}
  item->next = 0;
  // 5. Retornar el apuntador a la estructura kbuf, 0 nulo (0)
  //    si ocurrio algun error.

  // Verificar si la asignación de memoria fue exitosa
  if (ret->data == NULL) {
      free(ret);
      return 0;
  }
  // Retornar el apuntador a la estructura kbuf
  return ret;
}

void * kbuf_allocate(kbuf * b) {
  
  kitem * it = 0;
  // Caso base: si el buffer no tiene items libres, retornar nulo
  //1. Tomar el primer item de la lista de libres
  
  //2. El siguiente item libre se convierte en la cabeza de la lista
  //   de items libres
  
  //3. Descontar el item de la cantidad de items disponibles dentro del buffer
  
  //4. Retornar el apuntador al item obtenido 
  return it;
}

void kbuf_free(kbuf * b, void * ptr) {
 
  //1. Verificar si el item esta dentro de este buffer, con su direccion
  //2. Colocar el item liberado como cabeza de la lista de items libres
  //3. Incrementar  la cantidad de items libres dentro del buffer

}

void kbuf_destroy(kbuf * b) {
  // Liberar la memoria asociada al buffer
}


int kbuf_full(kbuf * b) {
  //Retornar 1 si el buffer esta lleno, 0 en caso contrario
  return 0;
}

int kbuf_empty(kbuf * b) {
  //Retornar 1 si el buffer esta vacio (tiene todos sus items libres)
  return 0;
}


int kbuf_contains(kbuf * b, void * ptr) {
  // Retorna 1 si el item esta contenido dentro del buffer
  return 0;
}
