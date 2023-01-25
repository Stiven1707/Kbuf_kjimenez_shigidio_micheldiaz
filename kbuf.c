

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

#include "kbuf.h"

kbuf * kbuf_create(unsigned int elemsize) {

    // Redondear elemsize a una potencia de 2 hacia arriba
    unsigned int rounded_elemsize = pow(2, ceil(log2(elemsize)));

    // Reservar memoria para la estructura kbuf
    kbuf * ret = (kbuf *) malloc(sizeof(kbuf));

    // Verificar si la asignación de memoria fue exitosa
    if (ret == NULL) {
        return NULL;
    }

    // Inicializar campos de la estructura kbuf
    ret->elemsize = rounded_elemsize;
    ret->size = rounded_elemsize + ITEMSIZE;
    ret->free = 0;
    ret->total = 0;
    ret->free_list = NULL;
    ret->pages = (unsigned short) ceil((double) (sizeof(kbuf) + (ret->size * ret->total)) / PAGE_SIZE);

    // Reservar memoria contigua para los elementos del buffer
    ret->data = (char *) VirtualAlloc(NULL, ret->pages * PAGE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    // Verificar si la asignación de memoria fue exitosa
    if (ret->data == NULL) {
        free(ret);
        return NULL;
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
