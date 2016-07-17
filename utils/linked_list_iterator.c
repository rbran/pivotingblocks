#include "linked_list.h"

listIterator* list_iterator_new(likedList *list, likedListDirecao direction) {
  likedListNo *node = direction == LISTA_INICIO
    ? list->head
    : list->tail;
  return list_iterator_new_from_node(node, direction);
}

listIterator* list_iterator_new_from_node(likedListNo *node, likedListDirecao direction) {
  listIterator *self;
  if (!(self = LIST_MALLOC(sizeof(listIterator))))
    return NULL;
  self->next = node;
  self->direction = direction;
  return self;
}

likedListNo* list_iterator_next(listIterator *self) {
  likedListNo *curr = self->next;
  if (curr) {
    self->next = self->direction == LISTA_INICIO
      ? curr->next
      : curr->prev;
  }
  return curr;
}

void list_iterator_destroy(listIterator *self) {
  LIST_FREE(self);
  self = NULL;
}
