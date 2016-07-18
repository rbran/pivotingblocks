#include "null.h"

#include "../modulo.h"

int null_trabalho(modulo* self){
    comunicacao *inputs = modulo_getConexoesEntradas(self);
    //TODO: Esvaziar o conector sem precisar de criar um buffer
    uint tamanho = comunicacao_getEspacoDisponivelRetirar(inputs);    
    if(tamanho == 0)
        return 0;

    char buffer[tamanho];
    return comunicacao_retirar(inputs, buffer, tamanho);
}

CRIACAO_MODULO(null) {
    if(argc != 2) return 1;

    modulo_inicializar(self);

    char **conexoes = (char**) malloc(sizeof(*conexoes) * 1);
    conexoes[0] = argv[1];
    modulo_setNomeConexoes(self, 1, conexoes, 0, NULL);
    modulo_setTrabalho(self, null_trabalho);

    return 0;
}
