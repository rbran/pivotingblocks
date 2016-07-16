#ifndef ZERO_H
#define ZERO_H

#include <stddef.h>

#include "../modulo.h"
#include "../comunicacao.h"

#define MODULO_ZERO_TAMANHO_BUFFER 1024

typedef struct zero_struct {
    int fd;
    char buffer[MODULO_ZERO_TAMANHO_BUFFER];
} zero;

#endif // ZERO_H
