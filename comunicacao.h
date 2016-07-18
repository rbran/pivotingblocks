#ifndef COMUNICACAO_H
#define COMUNICACAO_H

typedef enum comunicacaoEstado_Enum comunicacaoEstado;
typedef struct comunicacao_Struct comunicacao;

#include "utils/buffer_circular.h"
#include "modulo.h"

#include <stdlib.h>

enum comunicacaoEstado_Enum{
    DADOS_DISPONIVEIS,
    DADOS_N_DISPONIVEIS
};

struct comunicacao_Struct {
    char *nome;
    comunicacaoEstado estado;
    bufferCircular buffer;
    modulo *entrada;
    modulo *saida;
};

comunicacao* comunicacao_criar(size_t tamanho);
void comunicacao_inicializar(comunicacao *self, size_t tamanho);

int comunicacao_guardar(comunicacao *self, char* buffer, size_t tamanho);
int comunicacao_retirar(comunicacao *self, char* buffer, size_t tamanho);

size_t comunicacao_getEspacoDisponivelRetirar(comunicacao *self);
size_t comunicacao_getEspacoDisponivelGuardar(comunicacao *self);

comunicacaoEstado comunicacao_getEstado(comunicacao *self);
int comunicacao_setEstado(comunicacao *self, comunicacaoEstado estado);

char* comunicacao_getNome(comunicacao *self);
void comunicacao_setNome(comunicacao *self, char *nome);

modulo* comunicacao_getEntrada(comunicacao *self);
void comunicacao_setEntrada(comunicacao *self, modulo *entrada);

modulo* comunicacao_getSaida(comunicacao *self);
void comunicacao_setSaida(comunicacao *self, modulo *saida);


#endif // COMUNICACAO_H
