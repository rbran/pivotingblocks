#include <string.h>

#include "modulo.h"

inline void modulo_initModuloPadrao(modulo* self) {
    memset(self, 0, sizeof(*self));
}

inline void modulo_setQuantidadeEntradas(modulo* self, uint entradas) {
    self->numEntradas = entradas;
}

uint modulo_getQuantidadeEntradas(modulo* self) {
    return self->numEntradas;
}

inline void modulo_setQuantidadeSaidas(modulo* self, uint saidas) {
    self->numSaidas = saidas;
}

uint modulo_getQuantidadeSaidas(modulo* self) {
    return self->numSaidas;
}

inline void modulo_setInicializacao(modulo* self, modulo_inicializacao inicializacao) {
    self->inicializacao = inicializacao;
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

inline void modulo_setDados(modulo* self, void* dados) {
    self->dados = dados;
}

inline void* modulo_getDados(modulo* self) {
    return self->dados;
}
