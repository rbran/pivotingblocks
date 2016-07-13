#ifndef COMUNICACAO_H
#define COMUNICACAO_H

#include <stdlib.h>

#include "buffer_circular.h"

typedef enum comunicacaoEstado_Enum{
    DADOS_DISPONIVEIS,
    DADOS_N_DISPONIVEIS
} comunicacaoEstado;

typedef struct comunicacao_Struct {
    comunicacaoEstado estado;
    bufferCircular buffer;
} comunicacao;

comunicacao *comunicacao_criar(size_t tamanho);
void comunicacao_inicializar(comunicacao *self, size_t tamanho);
int comunicacao_guardar(comunicacao *self, char* buffer, size_t tamanho);
int comunicacao_retirar(comunicacao *self, char* buffer, size_t tamanho);
size_t comunicacao_getEspacoDisponivelRetirar(comunicacao *self);
size_t comunicacao_getEspacoDisponivelGuardar(comunicacao *self);
comunicacaoEstado comunicacao_getEstado(comunicacao *self);
int comunicacao_setEstado(comunicacao *self, comunicacaoEstado estado);

#endif // COMUNICACAO_H
