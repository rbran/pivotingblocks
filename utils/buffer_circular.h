#ifndef BUFFER_CIRCULAR_H
#define BUFFER_CIRCULAR_H

#include <stddef.h>

typedef struct {
    size_t tamanho;

    size_t inicio;
    size_t ocupado;
    char *buffer;
} bufferCircular;

bufferCircular *bufferCircular_criar(size_t tamanho);
void bufferCircular_inicializar(bufferCircular *self, size_t tamanho);

int bufferCircular_vazio(bufferCircular *self);
int bufferCircular_cheio(bufferCircular *self);
size_t bufferCircular_tamanho(bufferCircular *self);
size_t bufferCircular_usado(bufferCircular *self);
size_t bufferCircular_sobando(bufferCircular *self);
void bufferCircular_esvaziar(bufferCircular *self);

void bufferCircular_escrever(bufferCircular *self, const char *origem, size_t tamanho);
char *bufferCircular_escreverPonteiro(bufferCircular *self, size_t *tamanho);
void bufferCircular_escreverOcupar(bufferCircular *self, size_t tamanho);

void bufferCircular_ler(bufferCircular *self, char *destino, size_t tamanho);
const char *bufferCircular_lerPonteiro(bufferCircular *self, size_t deslocamento, size_t *disponivel);
void bufferCircular_lerDesocupar(bufferCircular *self, size_t tamanho);

void bufferCircular_transferir(bufferCircular *origem, bufferCircular *destino, size_t tamanho);

void bufferCircular_destruir(bufferCircular *self);

#endif // BUFFER_CIRCULAR_H
