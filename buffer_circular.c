#include "buffer_circular.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

bufferCircular *bufferCircular_novo(size_t tamanho) {
    bufferCircular *self = malloc(sizeof(*self));
    assert(self != NULL);

    self->buffer = malloc(tamanho);
    assert(self->buffer != NULL);

    self->tamanho = tamanho;
    self->inicio = self->ocupado = 0;

    return self;
}

static inline void ocupar(bufferCircular *self, size_t tamanho) {
    self->ocupado += tamanho;
}

void bufferCircular_escrever(bufferCircular *self, const char *origem, size_t tamanho) {
    assert(tamanho <= bufferCircular_sobando(self));

    char *tail = self->buffer + ((self->inicio + self->ocupado) % self->tamanho);
    char *write_end = self->buffer + ((self->inicio + self->ocupado + tamanho) % self->tamanho);

    if(tail <= write_end) {
        memcpy(tail, origem, tamanho);
    }
    else
    {
        char *end = self->buffer + self->tamanho;

        size_t first_write = end - tail;
        memcpy(tail, origem, first_write);

        size_t second_write = tamanho - first_write;
        memcpy(self->buffer, origem + first_write, second_write);
    }

    ocupar(self, tamanho);
}

char *bufferCircular_escreverPonteiro(bufferCircular *self, size_t *disponivel) {
    if(bufferCircular_cheio(self)) {
        *disponivel = 0;
        return NULL;
    }

    char *head = self->buffer + self->inicio;
    char *tail = self->buffer + ((self->inicio + self->ocupado) % self->tamanho);

    if(tail < head) {
        *disponivel = head - tail;
    }
    else
    {
        char *end = self->buffer + self->tamanho;
        *disponivel = end - tail;
    }

    return tail;
}

void bufferCircular_escreverOcupar(bufferCircular *self, size_t tamanho) {
    assert(tamanho <= bufferCircular_sobando(self));
    ocupar(self, tamanho);
}

static inline void desocupar(bufferCircular *self, size_t tamanho) {
    self->inicio = (self->inicio + tamanho) % self->tamanho;
    self->ocupado -= tamanho;
}

void bufferCircular_ler(bufferCircular *self, char *destino, size_t tamanho) {
    assert(tamanho <= bufferCircular_usado(self));

    char *head = self->buffer + self->inicio;
    char *end_read = self->buffer + ((self->inicio + tamanho) % self->tamanho);

    if(end_read <= head) {
        char *end = self->buffer + self->tamanho;

        size_t first_read = end - head;
        memcpy(destino, head, first_read);

        size_t second_read = tamanho - first_read;
        memcpy(destino + first_read, self->buffer, second_read);
    }
    else
    {
        memcpy(destino, head, tamanho);
    }

    desocupar(self, tamanho);
}

const char *bufferCircular_lerPonteiro(bufferCircular *self, size_t deslocamento, size_t *disponivel) {
    if(bufferCircular_vazio(self)) {
        *disponivel = 0;
        return NULL;
    }

    char *head = self->buffer + self->inicio + deslocamento;
    char *tail = self->buffer + ((self->inicio + deslocamento + self->ocupado) % self->tamanho);

    if(tail <= head) {
        char *end = self->buffer + self->tamanho;
        *disponivel = end - head;
    }
    else
    {
        *disponivel = tail - head;
    }

    return head;
}

void bufferCircular_lerDesocupar(bufferCircular *self, size_t tamanho) {
    assert(bufferCircular_usado(self) >= tamanho);
    desocupar(self, tamanho);
}

void bufferCircular_transferir(bufferCircular *origem, bufferCircular *destino, size_t tamanho) {
    assert(bufferCircular_usado(origem) <= tamanho);
    assert(bufferCircular_sobando(destino) >= tamanho);

    size_t copied = 0;
    while(copied < tamanho) {
        size_t can_read;
        const char *from_ptr = bufferCircular_lerPonteiro(origem, copied, &can_read);

        size_t copied_this_read = 0;

        while(copied_this_read < can_read) {
            size_t can_write;
            char *to_ptr = bufferCircular_escreverPonteiro(destino, &can_write);

            size_t write = (can_read > can_write) ? can_write : can_read;
            memcpy(to_ptr, from_ptr, write);

            copied_this_read += write;
        }

        copied += copied_this_read;
    }

    ocupar(destino, copied);
}

void bufferCircular_destruir(bufferCircular *self) {
    if(self != NULL) {
        free(self->buffer);
        free(self);
    }
}
