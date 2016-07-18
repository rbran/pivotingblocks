
#include "dummy.h"

int dummy_trabalho(modulo* self){
    return 0;
}

const static char dummyConexoes[1][6] = {"dummy"};

CRIACAO_MODULO(dummy) {
    if(argc != 1) return 1;

    modulo_inicializar(self);

    modulo_setNomeConexoes(self, 1, dummyConexoes, 1, dummyConexoes);
    modulo_setTrabalho(self, dummy_trabalho);

    return 0;
}
