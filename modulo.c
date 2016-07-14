#include "modulo.h"

inline void setQuantidadeComunicacao(modulo* self, uint entradas, uint saidas) {
    self->numEntradas = entradas;
    self->numSaidas = saidas;
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
