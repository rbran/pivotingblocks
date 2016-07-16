#include <stdio.h>

#include "modulo.h"
#include "comunicacao.h"

#include "modulos/dummy.h"
#include "modulos/zero.h"

typedef struct moduloDeclaracao_struct {
    char* nome;
    modulo_criacao criacao;
} moduloDeclaracao;

const uint numModulos = 1;

const uint numConexoes = 2;
const size_t tamanhoPadraoComunicacao = 1024;

const moduloDeclaracao modulosDecl[] = {
    {"dummy", modulo_dummy_criacao},
    {"zero", modulo_zero_criacao}
};

int main(int argc, char *argv[]) {
    modulo modulosInst[numModulos];
    comunicacao conexoes[numConexoes];

    uint totalEntradas, totalSaidas;

    totalSaidas = totalEntradas = 0;

    uint i;
    for(i = 0; i < numModulos; i++) {
        modulo *instancia = &modulosInst[i];

        modulosDecl[i].criacao(instancia, 0, NULL);
    }

    for(i = 0; i < numModulos; i++) {
        modulo *instancia = &modulosInst[i];

        instancia->inicializacao(instancia);
    }

    for(i = 0; i < numModulos; i++) {
        modulo *instancia = &modulosInst[i];
        totalEntradas += modulo_getQuantidadeEntradas(instancia);
        totalSaidas += modulo_getQuantidadeSaidas(instancia);
    }

    for(i = 0; i < numModulos; i++) {
        comunicacao_inicializar(&conexoes[i], tamanhoPadraoComunicacao);
    }

    for(i = 0; i < numModulos; i++) {
        modulo *instancia = &modulosInst[i];

        instancia->trabalho(instancia, NULL, NULL);
    }

    for(i = 0; i < numModulos; i++) {
        modulo *instancia = &modulosInst[i];

        instancia->encerramento(instancia);
    }

    for(i = 0; i < numModulos; i++) {
        modulo *instancia = &modulosInst[i];

        instancia->destruicao(instancia);
    }

    return 0;
}
