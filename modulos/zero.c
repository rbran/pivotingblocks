#include "zero.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int zero_inicializacao(modulo* self) {
    zero *dados = (zero*) modulo_getDados(self);
    dados->fd = open("/dev/zero", O_RDONLY);

    if(dados->fd < 0)
        return dados->fd;

    int *fds = (int*)malloc(sizeof(*fds) * 1);
    fds[0] = dados->fd;

    modulo_setFdsEspera(self, fds, 1);

    return 0;
}

int zero_trabalho(modulo* self) {
    zero *dados = (zero*) modulo_getDados(self);
    comunicacao *outputs = modulo_getConexoesSaidas(self);

    //TODO: tamanho do buffer de acordo com o tamanho do output
    //TODO: ler directamente para o buffer do output
    ssize_t tamanhoLido = read(dados->fd, dados->buffer, MODULO_ZERO_TAMANHO_BUFFER);

    return comunicacao_guardar(&outputs[1], dados->buffer, tamanhoLido);
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
    if(argc != 2) return 1;

    modulo_inicializar(self);

    zero *dados = (zero*) malloc(sizeof(*dados));
    dados->fd = -1;

    modulo_setDados(self, dados);

    char **conexoes = (char**) malloc(sizeof(*conexoes) * 1);
    conexoes[0] = argv[1];
    modulo_setNomeConexoes(self, 0, NULL, 1, conexoes);

    modulo_setInicializacao(self, zero_inicializacao);
    modulo_setTrabalho(self, zero_trabalho);
    modulo_setEncerramento(self, zero_encerramento);
    modulo_setDestruicao(self, zero_destruicao);

    return 0;
}
