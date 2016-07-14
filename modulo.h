#ifndef MODULO_H
#define MODULO_H

#include <stdlib.h>

#include "comunicacao.h"

struct modulo_struct;
typedef struct modulo_struct modulo;

typedef int (*modulo_criacao)(modulo* self, int argc, char *argv[]);
typedef int (*modulo_inicializacao)(modulo* self, int *fds, uint *numeroFds);
typedef int (*modulo_trabalho)(modulo* self, comunicacao *inputs, comunicacao *outputs);
typedef int (*modulo_encerramento)(modulo* self);
typedef int (*modulo_destruicao)(modulo* self);

struct modulo_struct {
    uint numEntradas;
    uint numSaidas;
    modulo_inicializacao inicializacao;
    modulo_trabalho trabalho;
    modulo_encerramento encerramento;
    modulo_destruicao destruicao;
    void* dados;
};

#define CRIACAO_MODULO(NOME) int NOME ## _criacao(modulo* self, int argc, char* argv[])

void setQuantidadeComunicacao(modulo* self, uint entradas, uint saidas);
void setInicializacao(modulo* self, modulo_inicializacao inicializacao);
void setTrabalho(modulo* self, modulo_trabalho trabalho);
void setEncerramento(modulo* self, modulo_encerramento encerramento);
void setDestruicao(modulo* self, modulo_destruicao destruicao);
void setDados(modulo* self, void* dados);
void* getDados(modulo* self);

#endif // MODULO_H
