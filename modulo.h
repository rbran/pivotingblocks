#ifndef MODULO_H
#define MODULO_H

#include <stdlib.h>

#include "comunicacao.h"

struct modulo_struct;
typedef struct modulo_struct modulo;

typedef int (*modulo_criacao)(modulo* self, int argc, char *argv[]);
typedef int (*modulo_inicializacao)(modulo* self);
typedef int (*modulo_trabalho)(modulo* self, comunicacao *inputs, comunicacao *outputs);
typedef int (*modulo_encerramento)(modulo* self);
typedef int (*modulo_destruicao)(modulo* self);

struct modulo_struct {
    uint numEntradas;
    uint numSaidas;
    int *fds;
    uint numeroFds;
    modulo_inicializacao inicializacao;
    modulo_trabalho trabalho;
    modulo_encerramento encerramento;
    modulo_destruicao destruicao;
    void* dados;
};

#define CRIACAO_MODULO(NOME) int modulo_ ## NOME ## _criacao(modulo* self, int argc, char* argv[])

void modulo_initModuloPadrao(modulo* self);
void modulo_setQuantidadeEntradas(modulo* self, uint entradas);
uint modulo_getQuantidadeEntradas(modulo* self);
void modulo_setQuantidadeSaidas(modulo* self, uint saidas);
uint modulo_getQuantidadeSaidas(modulo* self);
void modulo_setFdsEspera(modulo* self, int *fds, uint *numeroFds);
void modulo_setInicializacao(modulo* self, modulo_inicializacao inicializacao);
void modulo_setTrabalho(modulo* self, modulo_trabalho trabalho);
void modulo_setEncerramento(modulo* self, modulo_encerramento encerramento);
void modulo_setDestruicao(modulo* self, modulo_destruicao destruicao);
void modulo_setDados(modulo* self, void* dados);
void* modulo_getDados(modulo* self);

#endif // MODULO_H
