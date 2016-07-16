#include "zero.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int zero_inicializacao(modulo* self) {
    zero *dados = (zero*) modulo_getDados(self);
    dados->fd = open("/dev/zero", O_RDONLY);

    if(dados->fd < 0)
        return dados->fd;

    return 0;
}

int zero_trabalho(modulo* self, comunicacao *inputs, comunicacao *outputs) {
    zero *dados = (zero*) modulo_getDados(self);
    //TODO: tamanho do buffer de acordo com o tamanho do output
    //TODO: ler directamente para o buffer do output
    ssize_t tamanhoLido = read(dados->fd, dados->buffer, MODULO_ZERO_TAMANHO_BUFFER);

    return comunicacao_guardar(outputs, dados->buffer, tamanhoLido);
}

int zero_encerramento(modulo* self) {
    zero *dados = (zero*) modulo_getDados(self);
    return close(dados->fd);
}

int zero_destruicao(modulo* self) {
    zero *dados = (zero*) modulo_getDados(self);
    free(dados);
    return 0;
}

CRIACAO_MODULO(zero) {
    modulo_initModuloPadrao(self);

    zero *dados = (zero*) malloc(sizeof(*dados));
    dados->fd = -1;

    modulo_setDados(self, dados);

    modulo_setQuantidadeEntradas(self, 0);
    modulo_setQuantidadeSaidas(self, 1);

    modulo_setInicializacao(self, zero_inicializacao);
    modulo_setTrabalho(self, zero_trabalho);
    modulo_setEncerramento(self, zero_encerramento);
    modulo_setDestruicao(self, zero_destruicao);

    return 0;
}
