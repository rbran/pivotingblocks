#include <stdio.h>

#include "modulo.h"
#include "comunicacao.h"

#include "modulos/dummy.h"

typedef struct moduloDeclaracao_struct {
    char* nome;
    modulo_criacao criacao;
} moduloDeclaracao;

const uint numModulos = 1;

const moduloDeclaracao modulosDecl[] = {
    {"dummy", dummy_criacao}
};

int main(int argc, char *argv[]) {
    modulo modulosInst[numModulos];

    uint i;
    for(i = 0; i < numModulos; i++){
        modulo *instancia = &modulosInst[i];

        modulosDecl[i].criacao(instancia, 0, NULL);
    }
    return 0;
}
