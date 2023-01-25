

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
  
  kbuf * ret = 0;
  //redondear a una potencia de 2 el elemesize hacia arriba
  double elemsize = pow(2, ceil(log2(elemsize)));
  if (elemsize > (PAGE_SIZE/2))
  {
    /* code */
  }
  
  // 1. Calcular el tamano real que ocupa cada item dentro del buffer.
  //    Para items de 1, 2 o 4 bytes, se deberaa tomar un apuntador de
  //    tipo kitem.
  size_t tamItem = sizeof(kitem);
  
  //2. Calcular la cantidad de paginas (de PAGE_SIZE) que se necesitan
  //   para almacenar la estructura de tipo kbuf y al menos un item.
  
  //3. Solicitar la memoria
  
  //4. Almacenar la estructura al inicio de la memoria asignada
  //   Se debe colocar un apuntador de tipo kbuf al inicio de la
  //   memoria obtenida, e inicializar los atributos de esa estructura
  
  // 5. Retornar el apuntador a la estructura kbuf, 0 nulo (0)
  //    si ocurrio algun error.
  
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
