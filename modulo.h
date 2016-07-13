#ifndef MODULO_H
#define MODULO_H

#include <comunicacao.h>

int criacao(int argc, char *argv[]);
int inicializacao(int *fds, unsigned int *numeroFds);
int trabalho(Comunicacao *inputs, Comunicacao *outputs);
int encerramento();
int destruicao();

#endif // MODULO_H
