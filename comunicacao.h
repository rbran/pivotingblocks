#ifndef COMUNICACAO_H
#define COMUNICACAO_H

#include <stdlib.h>

typedef enum comunicacaoEstado_Enum{
    dadosNaoConsumidos,
    dadosConsumidos
} comunicacaoEstado;

typedef struct comunicacao_Struct {
    ComunicacaoEstado estado;
    uint tamanhoTotal;
    uint tamanhoGuardado;
    void *posicao;
    void *dados;
} comunicacao;

int guardar(comunicacao self, uint tamanho, void* buffer);
int retirar(comunicacao self, uint tamanho, void* buffer);
inline uint getEspacoDisponivelRetirar(comunicacao self);
inline uint getEspacoDisponivelGuardar(comunicacao self);
inline comunicacaoEstado getEstado(comunicacao self);
inline int setEstado(comunicacao self, comunicacaoEstado estado);

#endif // COMUNICACAO_H
