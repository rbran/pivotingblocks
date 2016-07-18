#include <string.h>

#include "modulo.h"

#include <assert.h>

inline modulo* modulo_criar() {
    modulo* self = (modulo*) malloc(sizeof(*self));
    assert(self == NULL);
    modulo_inicializar(self);
    return self;
}

inline void modulo_inicializar(modulo* self) {
    memset(self, 0, sizeof(*self));
}

inline void modulo_setNomeConexoes(modulo* self, uint numEntradas, char **entradas, uint numSaidas, char **saidas) {
    self->numEntradas = numEntradas;
    self->nomeEntradas = entradas;
    self->numSaidas = numSaidas;
    self->nomeSaidas = saidas;
}

inline void modulo_setConexoes(modulo* self, uint numEntradas, comunicacao **entradas, uint numSaidas, comunicacao **saidas) {
    self->numEntradas = numEntradas;
    self->entradas = entradas;
    self->numSaidas = numSaidas;
    self->saidas = saidas;
}

inline comunicacao** modulo_getConexoesEntradas(modulo* self) {
    return self->entradas;
}

inline comunicacao** modulo_getConexoesSaidas(modulo* self) {
    return self->saidas;
}

inline char** modulo_getNomeEntradas(modulo* self) {
    return self->nomeEntradas;
}

inline char** modulo_getNomeSaidas(modulo* self) {
    return self->nomeSaidas;
}

inline uint modulo_getNumeroEntradas(modulo* self) {
    return self->numEntradas;
}

inline uint modulo_getNumeroSaidas(modulo* self) {
    return self->numSaidas;
}

inline void modulo_setInicializacao(modulo* self, modulo_inicia inicializacao) {
    self->inicia = inicializacao;
}

inline void modulo_setTrabalho(modulo* self, modulo_trabalho trabalho) {
    self->trabalho = trabalho;
}
inline void modulo_setEncerramento(modulo* self, modulo_encerramento encerramento) {
    self->encerramento = encerramento;
}

inline void modulo_setDestruicao(modulo* self, modulo_destruicao destruicao) {
    self->destruicao = destruicao;
}

modulo_inicia modulo_getInicia(modulo* self) {
    return self->inicia;
}

modulo_trabalho modulo_getTrabalho(modulo* self) {
    return self->trabalho;
}

modulo_encerramento modulo_getEncerramento(modulo* self) {
    return self->encerramento;
}

modulo_destruicao modulo_getDestruicao(modulo* self) {
    return self->destruicao;
}

inline void modulo_setFdsEspera(modulo* self, int *fds, uint numFds){
    //TODO: optimizar o retorno fds, talvez usar como retorno de função ao invez de guardar na struct
    self->numFds = numFds;
    self->fds = fds;
}

inline int* modulo_getFdsEspera(modulo* self, uint *numFds){
    *numFds = self->numFds;
    return self->fds;
}

inline void modulo_setDados(modulo* self, void* dados) {
    self->dados = dados;
}

inline void* modulo_getDados(modulo* self) {
    return self->dados;
}
