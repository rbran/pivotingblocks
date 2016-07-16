#include <stdio.h>
#include <string.h>

#include "modulo.h"
#include "comunicacao.h"

#include "modulos/dummy.h"
#include "modulos/zero.h"
#include "modulos/null.h"

typedef struct moduloDeclaracao_struct {
    char* nome;
    modulo_criacao criacao;
} moduloDeclaracao;

typedef struct comunicacaoModulo_struct {
    modulo mod;
    comunicacao* entradas;
    comunicacao* saidas;
} comunicacaoModulo;

const size_t tamanhoPadraoComunicacao = 1024;

const moduloDeclaracao modulosDecl[] = {
    {"dummy", modulo_dummy_criacao},
    {"zero", modulo_zero_criacao},
    {"null", modulo_null_criacao}
};

modulo_criacao getModuloCriacaoPorNome(const char* nome) {
    int i;
    for(i = 0; i < sizeof(modulosDecl); i++) {
        if(strcpy(modulosDecl[i].nome, nome)) {
            return modulosDecl[i].criacao;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int i;

    comunicacaoModulo zeroMod, nullMod;
    memset(&zeroMod, 0, sizeof(zeroMod));
    memset(&nullMod, 0, sizeof(nullMod));

    getModuloCriacaoPorNome("zero")(&zeroMod.mod, 0, NULL);
    getModuloCriacaoPorNome("null")(&nullMod.mod, 0, NULL);

    comunicacao conectorZeroNull;

    comunicacao_inicializar(&conectorZeroNull, tamanhoPadraoComunicacao);

    zeroMod.mod.inicializacao(&zeroMod.mod);
    nullMod.mod.inicializacao(&nullMod.mod);

    fd_set rfds;
    struct timeval tv;
    int retval;


    FD_ZERO(&rfds);

    for(i = 0; i < zeroMod.mod.numeroFds; i++) {
        FD_SET(zeroMod.mod.fds[i], &rfds);
    }

    /* Wait up to five seconds. */
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    retval = select(1, &rfds, NULL, NULL, &tv);

    if (retval == -1) {
        perror("select()");
        return 1;
    } else if (retval) {
        //if(FD_ISSET(zeroMod.fds[0], &rfds)) TRUE
        zeroMod.mod.trabalho(&zeroMod.mod, &zeroMod.entradas, &zeroMod.saidas);
        nullMod.mod.trabalho(&nullMod.mod, &nullMod.entradas, &nullMod.saidas);
    } else {
        printf("No data within five seconds.\n");
        return 1;
    }

    zeroMod.mod.encerramento(&zeroMod.mod);
    nullMod.mod.encerramento(&nullMod.mod);

    zeroMod.mod.destruicao(&zeroMod.mod);
    nullMod.mod.destruicao(&nullMod.mod);

    return 0;
}
