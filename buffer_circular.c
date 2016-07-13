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

    char *final = self->buffer + ((self->inicio + self->ocupado) % self->tamanho);
    char *finalEscrita = self->buffer + ((self->inicio + self->ocupado + tamanho) % self->tamanho);

    if(final <= finalEscrita) {
        memcpy(final, origem, tamanho);
    } else {
        size_t primeiraEscrita = (self->buffer + self->tamanho) - final;
        memcpy(final, origem, primeiraEscrita);

        size_t segundaEscrita = tamanho - primeiraEscrita;
        memcpy(self->buffer, origem + primeiraEscrita, segundaEscrita);
    }

    ocupar(self, tamanho);
}

char *bufferCircular_escreverPonteiro(bufferCircular *self, size_t *disponivel) {
    if(bufferCircular_cheio(self)) {
        *disponivel = 0;
        return NULL;
    }

    char *inicio = self->buffer + self->inicio;
    char *final = self->buffer + ((self->inicio + self->ocupado) % self->tamanho);

    if(final < inicio) {
        *disponivel = inicio - final;
    } else {
        *disponivel = (self->buffer + self->tamanho) - final;
    }

    return final;
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

    char *inicio = self->buffer + self->inicio;
    char *finalLeitura = self->buffer + ((self->inicio + tamanho) % self->tamanho);

    if(finalLeitura <= inicio) {
        size_t first_read = (self->buffer + self->tamanho) - inicio;
        memcpy(destino, inicio, first_read);

        size_t second_read = tamanho - first_read;
        memcpy(destino + first_read, self->buffer, second_read);
    } else {
        memcpy(destino, inicio, tamanho);
    }

    desocupar(self, tamanho);
}

const char *bufferCircular_lerPonteiro(bufferCircular *self, size_t deslocamento, size_t *disponivel) {
    if(bufferCircular_vazio(self)) {
        *disponivel = 0;
        return NULL;
    }

    char *inicio = self->buffer + self->inicio + deslocamento;
    char *final = self->buffer + ((self->inicio + deslocamento + self->ocupado) % self->tamanho);

    if(final <= inicio) {
        char *end = self->buffer + self->tamanho;
        *disponivel = end - inicio;
    } else {
        *disponivel = final - inicio;
    }

    return inicio;
}

void bufferCircular_lerDesocupar(bufferCircular *self, size_t tamanho) {
    assert(bufferCircular_usado(self) >= tamanho);
    desocupar(self, tamanho);
}

void bufferCircular_transferir(bufferCircular *origem, bufferCircular *destino, size_t tamanho) {
    assert(bufferCircular_usado(origem) <= tamanho);
    assert(bufferCircular_sobando(destino) >= tamanho);

    size_t copiado = 0;
    while(copiado < tamanho) {
        size_t podeLer;
        const char *origem_ptr = bufferCircular_lerPonteiro(origem, copiado, &podeLer);

        size_t copiadoLeitura = 0;

        while(copiadoLeitura < podeLer) {
            size_t podeEscrever;
            char *destino_ptr = bufferCircular_escreverPonteiro(destino, &podeEscrever);

            size_t escrever = (podeLer > podeEscrever) ? podeEscrever : podeLer;
            memcpy(destino_ptr, origem_ptr, escrever);

            copiadoLeitura += escrever;
        }

        copiado += copiadoLeitura;
    }

    ocupar(destino, copiado);
}

void bufferCircular_destruir(bufferCircular *self) {
    if(self != NULL) {
        free(self->buffer);
        free(self);
    }
}
