#ifndef MODULO_H
#define MODULO_H

#include <stdlib.h>

struct modulo_struct;
typedef struct modulo_struct modulo;

typedef int (*modulo_criacao)(modulo* self, int argc, char *argv[]);
typedef int (*modulo_inicia)(modulo* self);
typedef int (*modulo_trabalho)(modulo* self);
typedef int (*modulo_encerramento)(modulo* self);
typedef int (*modulo_destruicao)(modulo* self);

#include "comunicacao.h"

struct modulo_struct {
    uint numEntradas;
    char** nomeEntradas;
    comunicacao **entradas;
    uint numSaidas;
    char** nomeSaidas;
    comunicacao **saidas;
    uint numFds;
    int *fds;
    modulo_inicia inicia;
    modulo_trabalho trabalho;
    modulo_encerramento encerramento;
    modulo_destruicao destruicao;
    void* dados;
};

#define CRIACAO_MODULO(NOME) int modulo_ ## NOME ## _criacao(modulo* self, int argc, char* argv[])

modulo* modulo_criar();
void modulo_inicializar(modulo* self);

uint modulo_getNumeroEntradas(modulo* self);
uint modulo_getNumeroSaidas(modulo* self);

void modulo_setNomeConexoes(modulo* self, uint numEntradas, char **entradas, uint numSaidas, char **saidas);
char** modulo_getNomeEntradas(modulo* self);
char** modulo_getNomeSaidas(modulo* self);

void modulo_setConexoes(modulo* self, uint numEntradas, comunicacao **entradas, uint numSaidas, comunicacao **saidas);
comunicacao** modulo_getConexoesEntradas(modulo* self);
comunicacao** modulo_getConexoesSaidas(modulo* self);

void modulo_setFdsEspera(modulo* self, int *fds, uint numeroFds);
int* modulo_getFdsEspera(modulo* self, uint *numeroFds);

void modulo_setDados(modulo* self, void* dados);
void* modulo_getDados(modulo* self);

void modulo_setInicializacao(modulo* self, modulo_inicia inicializacao);
void modulo_setTrabalho(modulo* self, modulo_trabalho trabalho);
void modulo_setEncerramento(modulo* self, modulo_encerramento encerramento);
void modulo_setDestruicao(modulo* self, modulo_destruicao destruicao);

modulo_inicia modulo_getInicia(modulo* self);
modulo_trabalho modulo_getTrabalho(modulo* self);
modulo_encerramento modulo_getEncerramento(modulo* self);
modulo_destruicao modulo_getDestruicao(modulo* self);

#endif // MODULO_H
