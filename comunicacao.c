#include <assert.h>

#include "comunicacao.h"

comunicacao *comunicacao_criar(size_t tamanho) {
    comunicacao *self = malloc(sizeof(*self));
    assert(self != NULL);

    comunicacao_inicializar(self, tamanho);

    return self;
}

inline void comunicacao_inicializar(comunicacao *self, size_t tamanho) {
    self->estado = DADOS_N_DISPONIVEIS;
    bufferCircular_inicializar(&self->buffer, tamanho);
}

inline int comunicacao_guardar(comunicacao *self, char* buffer, size_t tamanho) {
    bufferCircular_escrever(&self->buffer, buffer, tamanho);
    return 1;
}

inline int comunicacao_retirar(comunicacao *self, char* buffer, size_t tamanho) {
    bufferCircular_ler(&self->buffer, buffer, tamanho);
    return 1;
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
    return 1;
}
