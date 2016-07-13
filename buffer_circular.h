#ifndef BUFFER_CIRCULAR_H
#define BUFFER_CIRCULAR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t tamanho;

    size_t inicio;
    size_t ocupado;
    char *buffer;
} bufferCircular;

bufferCircular *bufferCircular_novo(size_t tamanho);

static inline bool bufferCircular_vazio(bufferCircular *self) {
    return self->ocupado == 0;
}

static inline bool bufferCircular_cheio(bufferCircular *self) {
    return self->ocupado == self->tamanho;
}

static inline size_t bufferCircular_tamanho(bufferCircular *self) {
    return self->tamanho;
}

static inline size_t bufferCircular_usado(bufferCircular *self) {
    return self->ocupado;
}

static inline size_t bufferCircular_sobando(bufferCircular *self) {
    return self->tamanho - self->ocupado;
}

static inline void bufferCircular_esvaziar(bufferCircular *self) {
    self->inicio = self->ocupado = 0;
}

void bufferCircular_escrever(bufferCircular *self, const char *origem, size_t bytes);
char *bufferCircular_escreverPonteiro(bufferCircular *self, size_t *writable);
void bufferCircular_escreverOcupar(bufferCircular *self, size_t bytes);

void bufferCircular_ler(bufferCircular *self, char *destino, size_t bytes);
const char *bufferCircular_lerPonteiro(bufferCircular *self, size_t offset, size_t *readable);
void bufferCircular_lerDesocupar(bufferCircular *self, size_t quantidade);

void bufferCircular_transferir(bufferCircular *origem, bufferCircular *destino, size_t quantidade);

void bufferCircular_destruir(bufferCircular *self);

#endif // BUFFER_CIRCULAR_H
