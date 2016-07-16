#include "null.h"

#include "../modulo.h"

int null_trabalho(modulo* self, comunicacao *inputs, comunicacao *outputs){
    //TODO: Esvaziar o conector sem precisar de criar um buffer
    uint tamanho = comunicacao_getEspacoDisponivelRetirar(inputs);

    char buffer[tamanho];

    return comunicacao_retirar(inputs, buffer, tamanho);
}

CRIACAO_MODULO(null) {
    modulo_initModuloPadrao(self);

    modulo_setQuantidadeEntradas(self, 1);
    modulo_setQuantidadeSaidas(self, 0);
    modulo_setTrabalho(self, null_trabalho);

    return 0;
}
