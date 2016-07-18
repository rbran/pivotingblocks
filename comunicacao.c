#include "comunicacao.h"

#include <assert.h>
#include <string.h>


inline comunicacao* comunicacao_criar(size_t tamanho) {
    comunicacao* self = (comunicacao*) malloc(sizeof(*self));
    assert(self == NULL);
    comunicacao_inicializar(self, tamanho);
    return self;
}

inline void comunicacao_inicializar(comunicacao *self, size_t tamanho) {
    memset(self, 0, sizeof(*self));
    comunicacao_setEstado(self, DADOS_N_DISPONIVEIS);
    bufferCircular_inicializar(&self->buffer, tamanho);
}

inline int comunicacao_guardar(comunicacao *self, char* buffer, size_t tamanho) {
    if(tamanho > 0) {
        bufferCircular_escrever(&self->buffer, buffer, tamanho);
        comunicacao_setEstado(self, DADOS_DISPONIVEIS);
        return 0;
    } else {
        return 1;
    }
}

inline int comunicacao_retirar(comunicacao *self, char* buffer, size_t tamanho) {
    if(tamanho > 0) {
        bufferCircular_ler(&self->buffer, buffer, tamanho);
        if(comunicacao_getEspacoDisponivelRetirar(self) == 0) comunicacao_setEstado(self, DADOS_N_DISPONIVEIS);
        return 0;
    } else {
        return 1;
    }
}

inline size_t comunicacao_getEspacoDisponivelRetirar(comunicacao *self) {
    return bufferCircular_usado(&self->buffer);
}

inline size_t comunicacao_getEspacoDisponivelGuardar(comunicacao *self) {
    return bufferCircular_sobando(&self->buffer);
}

inline comunicacaoEstado comunicacao_getEstado(comunicacao *self) {
    return self->estado;
}

inline int comunicacao_setEstado(comunicacao *self, comunicacaoEstado estado) {
    //Fazer uma verificação caso for relevante
    self->estado = estado;
    return 0;
}

inline char* comunicacao_getNome(comunicacao *self) {
    return self->nome;
}

inline void comunicacao_setNome(comunicacao *self, char *nome) {
    self->nome = nome;
}

inline modulo* comunicacao_getEntrada(comunicacao *self) {
    return self->entrada;
}

inline void comunicacao_setEntrada(comunicacao *self, modulo *entrada) {
    self->entrada = entrada;
}

inline modulo* comunicacao_getSaida(comunicacao *self) {
    return self->saida;
}

inline void comunicacao_setSaida(comunicacao *self, modulo *saida) {
    self->saida = saida;
}
