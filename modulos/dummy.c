
#include "dummy.h"

int dummy_trabalho(modulo* self, comunicacao *inputs, comunicacao *outputs){
    return 0;
}

CRIACAO_MODULO(dummy) {
    modulo_initModuloPadrao(self);

    modulo_setQuantidadeEntradas(self, 1);
    modulo_setQuantidadeSaidas(self, 1);
    modulo_setTrabalho(self, dummy_trabalho);

    return 0;
}
