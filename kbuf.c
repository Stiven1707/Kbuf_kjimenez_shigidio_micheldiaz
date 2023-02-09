

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

kbuf *kbuf_create(unsigned int elemsize)
{
	// 0. Redondear elemsize a una potencia de 2 hacia arriba
	unsigned int rounded_elemsize  = pow(2, ceil(log(elemsize) / log(2)));
	kbuf *ret = NULL;
	kitem *it;
	char *ptr;
	ptr = (char *)malloc(KBUF_SIZE);
	ret = (kbuf *)ptr;
	ret->elemsize = elemsize;


	// 1. Calcular el tamano real que ocupa cada item dentro del buffer.
	//    Para items de 1, 2 o 4 bytes, se deberaa tomar un apuntador de
	//    tipo kitem.
	if (rounded_elemsize  > ITEMSIZE)
		ret->size = rounded_elemsize;
	else
		ret->size = ITEMSIZE;
	//2. Calcular la cantidad de paginas (de PAGE_SIZE) que se necesitan
  	//   para almacenar la estructura de tipo kbuf y al menos un item.
	/*
	//2.1 Debido a que el buffer se almacena al inicio de la pagina
	//	  se debe restar esta cantidad antes de calcular la cantidad
	//    de items
	//2.2 Para tamano mayor o igual a 4k(PAGE_SIZE), se necesita una pagina adicional
	//    para almacenar la estructura del buffer (paginas += 1)
	*/
	ret->pages = 1;
	if (ret->size >= PAGE_SIZE)
	{
		ret->pages += (ret->size / PAGE_SIZE);
	}
	else
	{
		if (elemsize < ITEMSIZE)
		{
			ret->total = KBUF_SIZE / ITEMSIZE;
		}
		else
		{
			ret->total = KBUF_SIZE / ret->size;
		}
	}
	unsigned int occupiedKbuf = sizeof(kbuf) / ret->size;
	if (sizeof(kbuf) % ret->size != 0)
	{
		occupiedKbuf++;
	}

	ret->free = ret->total - occupiedKbuf;
	printf("\nElements in one page: %u", ret->free);

	//3. Solicitar la memoria

	// APUNTAR al inicio de la memoria reservada
	ret->data = ptr;

	// APUNTAR a la direccion que le corresponde al primer item.
	unsigned int addr;
	addr = ((unsigned int)ptr) + (occupiedKbuf * ret->size); // sizeof(kbuf);
	if (ret->size <= ITEMSIZE)
	{
		addr += ITEMSIZE;
	}
	printf("\nFirst item at: 0x%x \n", addr);
	it = (kitem *)addr;
	ret->free_list = it;

	// Iterar: cada item(antes del ultimo) apunta a la direccion del siguiente item. El ultimo item tiene como siguiente 0.
	unsigned int n = ret->free;
	for(int i=0; i<(n-1); i++){
		it->next = (void*)(((unsigned int)it)+ret->size);
		it = it->next;
	}
  	it->next = 0;
	return ret;
}

void *kbuf_allocate(kbuf *b)
{

	kitem *it = NULL;
	// 1. Si la cantidad de items disponibles es 0, retornar NULL.
	if ((void *)b->free == NULL)
	{
		return it;
	}
	// 2. Tomar el apuntador a la cabeza de los item libres.
	it = b->free_list;
	// 3. La nueva cabeza es el nodo siguiente al apuntador obtenido en el paso anterior.
	b->free_list = b->free_list->next;
	b->free--;
	// 4. Retornar el apuntador obtenido.
	return it;
}

void kbuf_free(kbuf *b, void *ptr)
{

	// 1. Comprobar que ptr se encuentre dentro de la region de items del buffer
	int existe = kbuf_contains(b, ptr);
	if (existe == 0)
	{
		return; // Sale de la funcion
	}
	if(kbuf_find(b, ptr)){
		printf("La direccion (0x%x) ya habia sido libera anteriormente.\n", ptr);
		return;
	}
	// 2. Ajustar la direccion a un limite de item de ser necesario
	kitem *it = ptr;
	// 3. Apuntar el item a la direccion ajustada en el paso anterior
	// 3.1 Guardar en it->next la cabeza actual de la lista de items libres
	it->next = b->free_list;
	// 3.2 it se convierte en la nueva cabeza
	b->free_list = it;
	b->free++;
	printf("\nEl item ha sido liberado\n");
}

void kbuf_destroy(kbuf *b)
{
	// Liberar la memoria asociada al buffer
	free(b);
}

int kbuf_full(kbuf *b)
{
	// Retornar 1 si el buffer esta lleno, 0 en caso contrario
	if (b->free > 0)
	{
		printf("\nEl buffer esta lleno\n");
		return 0;
	}
	printf("\nEl buffer NO esta lleno\n");
	return 1;
}

int kbuf_empty(kbuf *b)
{
	// Retornar 1 si el buffer esta vacio (tiene todos sus items libres)
	unsigned int occupiedKbuf = sizeof(kbuf) / b->size;

	if (sizeof(kbuf) % b->size != 0)
	{
		occupiedKbuf++;
	}

	if (b->free == (b->total - occupiedKbuf))
	{
		printf("\nEl buffer esta vacio\n");
		return 1;
	}
	printf("\nEl buffer NO esta vacio\n");
	return 0;
}

int kbuf_contains(kbuf *b, void *ptr)
{
	// Retorna 1 si el item esta contenido dentro del buffer
	unsigned int first_element, last_element = 0;
	unsigned int occupiedKbuf = sizeof(kbuf) / b->size;
	if (sizeof(kbuf) % b->size != 0)
	{
		occupiedKbuf++;
	}

	first_element = ((unsigned int)b->data) + (occupiedKbuf * b->size);

	// unsigned int n = b->free;
	unsigned int n = b->total;

	last_element = first_element;
	for (int i = 0; i < n - 2; i++)
	{
		last_element += b->size;
	}
	printf("\nLa direccion final 0x%x\n", (unsigned int)last_element);

	if ((unsigned int)ptr >= first_element && (unsigned int)ptr <= last_element)
	{
		printf("\nLa direccion 0x%x se encuentra dentro del buffer.\n", (unsigned int)ptr);
		return 1;
	}
	else
	{
		printf("\nLa direccion 0x%x no se encuentra en el buffer.\n", (unsigned int)ptr);
	}
	return 0;
}

int kbuf_find(kbuf *b, void *ptr)
{
	// Retorna 1 si el item esta contenido dentro del buffer

	kitem *it = ptr;

	unsigned int n = b->free;
	it = b->free_list;
	for(int i=0; i<n; i++){	
		if(ptr==it)
			return 1;
		it = it->next;
	}
	
	return 0;
}

