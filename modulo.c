#include <string.h>

#include "modulo.h"

inline void initModuloPadrao(modulo* self) {
    memset(self, 0, sizeof(*self));
}

inline void setQuantidadeEntradas(modulo* self, uint entradas) {
    self->numEntradas = entradas;
}

uint getQuantidadeEntradas(modulo* self) {
    return self->numEntradas;
}

inline void setQuantidadeSaidas(modulo* self, uint saidas) {
    self->numSaidas = saidas;
}

uint getQuantidadeSaidas(modulo* self) {
    return self->numSaidas;
}

inline void setInicializacao(modulo* self, modulo_inicializacao inicializacao) {
    self->inicializacao = inicializacao;
}

inline void setTrabalho(modulo* self, modulo_trabalho trabalho) {
    self->trabalho = trabalho;
}
inline void setEncerramento(modulo* self, modulo_encerramento encerramento) {
    self->encerramento = encerramento;
}

inline void setDestruicao(modulo* self, modulo_destruicao destruicao) {
    self->destruicao = destruicao;
}

inline void setDados(modulo* self, void* dados) {
    self->dados = dados;
}

inline void* getDados(modulo* self) {
    return self->dados;
}
