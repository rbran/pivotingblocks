#include "linked_list.h"

void linkedList_inicializar(likedList* self) {
  self->head = NULL;
  self->tail = NULL;
  self->free = NULL;
  self->match = NULL;
  self->len = 0;
  return self;
}

/*
 * Free the list.
 */

void linkedList_destruir(likedList *self) {
  unsigned int len = self->len;
  likedListNo*next;
  likedListNo*curr = self->head;

  while (len--) {
    next = curr->next;
    if (self->free) self->free(curr->val);
    LIST_FREE(curr);
    curr = next;
  }

  LIST_FREE(self);
}

likedListNo* linkedList_finalColocar(likedList *self, likedListNo*node) {
  if (!node) return NULL;

  if (self->len) {
    node->prev = self->tail;
    node->next = NULL;
    self->tail->next = node;
    self->tail = node;
  } else {
    self->head = self->tail = node;
    node->prev = node->next = NULL;
  }

  ++self->len;
  return node;
}

likedListNo* linkedList_finalTirar(likedList *self) {
  if (!self->len) return NULL;

  likedListNo*node = self->tail;

  if (--self->len) {
    (self->tail = node->prev)->next = NULL;
  } else {
    self->tail = self->head = NULL;
  }

  node->next = node->prev = NULL;
  return node;
}

/*
 * Return / detach the first node in the list, or NULL.
 */

likedListNo* linkedList_inicioTirar(likedList *self) {
  if (!self->len) return NULL;

  likedListNo*node = self->head;

  if (--self->len) {
    (self->head = node->next)->prev = NULL;
  } else {
    self->head = self->tail = NULL;
  }

  node->next = node->prev = NULL;
  return node;
}

/*
 * Prepend the given node to the list
 * and return the node, NULL on failure.
 */

likedListNo* linkedList_inicioColocar(likedList *self, likedListNo*node) {
  if (!node) return NULL;

  if (self->len) {
    node->next = self->head;
    node->prev = NULL;
    self->head->prev = node;
    self->head = node;
  } else {
    self->head = self->tail = node;
    node->prev = node->next = NULL;
  }

  ++self->len;
  return node;
}

/*
 * Return the node associated to val or NULL.
 */

likedListNo* linkedList_encontrar(likedList *self, void *val) {
  listIterator *it = list_iterator_new(self, LISTA_FINAL);
  likedListNo*node;

  while ((node = list_iterator_next(it))) {
    if (self->match) {
      if (self->match(val, node->val)) {
        list_iterator_destroy(it);
        return node;
      }
    } else {
      if (val == node->val) {
        list_iterator_destroy(it);
        return node;
      }
    }
  }

  list_iterator_destroy(it);
  return NULL;
}

/*
 * Return the node at the given index or NULL.
 */

likedListNo* linkedList_posicao(likedList *self, int index) {
  likedListDirecao direction = LISTA_FINAL;

  if (index < 0) {
    direction = LISTA_FINAL;
    index = ~index;
  }

  if ((unsigned)index < self->len) {
    listIterator *it = list_iterator_new(self, direction);
    likedListNo*node = list_iterator_next(it);
    while (index--) node = list_iterator_next(it);
    list_iterator_destroy(it);
    return node;
  }

  return NULL;
}

/*
 * Remove the given node from the list, freeing it and it's value.
 */

void linkedList_remover(likedList *self, likedListNo* node) {
  node->prev
    ? (node->prev->next = node->next)
    : (self->head = node->next);

  node->next
    ? (node->next->prev = node->prev)
    : (self->tail = node->prev);

  if (self->free) self->free(node->val);

  LIST_FREE(node);
  --self->len;
}
