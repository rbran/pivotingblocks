#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

#ifndef LIST_MALLOC
#define LIST_MALLOC malloc
#endif

#ifndef LIST_FREE
#define LIST_FREE free
#endif

typedef enum {
    LISTA_INICIO
  , LISTA_FINAL
} likedListDirecao;


struct likedListNo_struct;
typedef struct likedListNo_struct likedListNo;

struct likedList_struct;
typedef struct likedList_struct likedList;

struct listIterator_struct;
typedef struct listIterator_struct listIterator;

struct likedListNo_struct {
  struct likedListNo *prev;
  struct likedListNo *next;
  void *val;
};

struct likedList_struct{
  likedListNo* head;
  likedListNo* tail;
  uint len;
  void (*free)(void *val);
  int (*match)(void *a, void *b);
};

struct listIterator{
  likedListNo* next;
  likedListDirecao direction;
};

void linkedList_inicializar(likedList* self);

likedListNo* linkedList_finalColocar(likedList *self, likedListNo*node);

likedListNo* linkedList_inicioColocar(likedList *self, likedListNo*node);

likedListNo* linkedList_encontrar(likedList *self, void *val);

likedListNo* linkedList_posicao(likedList *self, int index);

likedListNo* linkedList_finalTirar(likedList *self);

likedListNo* linkedList_inicioTirar(likedList *self);

void linkedList_remover(likedList *self, likedListNo*node);

void linkedList_destruir(likedList *self);

// list_t iterator prototypes.

listIterator* list_iterator_new(likedList *list, likedListDirecao direction);

listIterator* list_iterator_new_from_node(likedListNo*node, likedListDirecao direction);

likedListNo* list_iterator_next(listIterator *self);

void list_iterator_destroy(listIterator *self);

#endif // LINKED_LIST_H
