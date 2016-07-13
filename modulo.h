#ifndef MODULO_H
#define MODULO_H

#include "comunicacao.h"

#include <stdlib.h>

int criacao(int argc, char *argv[]);
int inicializacao(int *fds, uint *numeroFds);
int trabalho(comunicacao *inputs, comunicacao *outputs);
int encerramento();
int destruicao();

#endif // MODULO_H
