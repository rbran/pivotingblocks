
#include "dummy.h"

int dummy_trabalho(modulo* self, comunicacao *inputs, comunicacao *outputs){
    return 0;
}

CRIACAO_MODULO(dummy) {
    initModuloPadrao(self);

    setQuantidadeEntradas(self, 1);
    setQuantidadeSaidas(self, 1);
    setTrabalho(self, dummy_trabalho);

    return 0;
}
