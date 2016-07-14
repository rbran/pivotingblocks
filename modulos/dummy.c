
#include "dummy.h"

int dummy_trabalho(modulo* self, comunicacao *inputs, comunicacao *outputs){
    return 0;
}

CRIACAO_MODULO(dummy) {
    setQuantidadeComunicacao(self, 1, 1);
    setInicializacao(self, NULL);
    setTrabalho(self, dummy_trabalho);
    setEncerramento(self, NULL);
    setDestruicao(self, NULL);
    setDados(self, NULL);

    return 0;
}
