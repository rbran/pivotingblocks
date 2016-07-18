#include "modulo.h"
#include "comunicacao.h"

#include "modulos/dummy.h"
#include "modulos/zero.h"
#include "modulos/null.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct moduloDeclaracao_struct {
    char* nome;
    modulo_criacao criacao;
} moduloDeclaracao;

typedef struct fdModulo_struct {
    int fd;
    modulo *origem;
}fdModulo;

//TODO: receber tamanho do buffer na comunicação por parametro
const size_t tamanhoPadraoComunicacao = 1024;

const moduloDeclaracao modulosDecl[] = {
    {"dummy", modulo_dummy_criacao},
    {"zero", modulo_zero_criacao},
    {"null", modulo_null_criacao}
};

modulo_criacao getModuloCriacaoPorNome(const char* nome) {
    uint i;
    for(i = 0; i < sizeof(modulosDecl); i++) {
        if(strcmp(modulosDecl[i].nome, nome) ==  0) {
            return modulosDecl[i].criacao;
        }
    }
    return NULL;
}

comunicacao* getConexaoPorNome(const char* nome, uint tamanhoLista, comunicacao lista[]) {
    uint i;
    for(i = 0; i < tamanhoLista; i++) {
        if(strcmp(lista[i].nome, nome) ==  0) {
            return &lista[i];
        }
    }
    return NULL;
}

void printHelp() {
    //TODO fazer uma help
    printf("Uso do PivotingBlocks:\n");
}

int inicializaModulos(int argc, char *argv[], modulo *modulos, uint *totalEntradas, uint *totalSaidas) {
    //inicializa os módulos
    int argumentoModuloDeclarado = 0;
    int argcModulo = 0;
    int argvInicioModulo = 0;
    char *nomeUltimoModulo = NULL;
    memset(modulos, 0, sizeof(modulos) * sizeof(*modulos));
    int numModulosCarregados = 0;
    int i;
    for(i = 0; i < argc; i++) {
        if(argumentoModuloDeclarado == 0 && (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)) {
            printHelp();
            return 0;
        } else if(strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--modulo") == 0) {
            if(argumentoModuloDeclarado != 0) {
                //finaliza o ultimo módulo
                modulo* inicializar = &modulos[numModulosCarregados++];
                getModuloCriacaoPorNome(nomeUltimoModulo)(inicializar, argcModulo, &argv[argvInicioModulo]);
                if(totalEntradas) *totalEntradas += modulo_getNumeroEntradas(inicializar);
                if(totalSaidas) *totalSaidas += modulo_getNumeroSaidas(inicializar);
            } else {
                //primeiro módulo que será declarado
                argumentoModuloDeclarado = 1;
            }

            //primero argumento será o nome do módulo, como o argv[0]
            argvInicioModulo = i;
            argcModulo = 1;
            if(++i >= argc) {
                //verfica se existe um nome após esse argumento
                printHelp();
                //TODO: justificar o erro
                return 1;
            }
            //TODO: verificar se não é outro argumento (inicia com '-', '--', etc..
            nomeUltimoModulo = argv[i];
            continue; //proximo argumento
        } else if(argumentoModuloDeclarado != 0) {
            //apenas um argumento pertencente ao último módulo declarado
            argcModulo++;
        } else {
            //argumento desconhecido e não pertencente a um módulo
            printHelp();
            //TODO: justificar o erro
            return 1;
        }
    }
    //carrega o último módulo (que não foi fechado por um novo -m)
    modulo* inicializar = &modulos[numModulosCarregados++];
    getModuloCriacaoPorNome(nomeUltimoModulo)(inicializar, argcModulo, &argv[argvInicioModulo]);
    if(totalEntradas) *totalEntradas += modulo_getNumeroEntradas(inicializar);
    if(totalSaidas) *totalSaidas += modulo_getNumeroSaidas(inicializar);
    return 0;
}

int inicializaConexoes(comunicacao *conexoes, uint numeroModulos, modulo *modulos) {
    uint numeroConexoesInicializadas = 0;
    uint i;
    for(i = 0; i < numeroModulos; i++) {
        modulo* moduloAtual = &modulos[i];

        uint numEntradas = modulo_getNumeroEntradas(moduloAtual);
        uint numSaidas = modulo_getNumeroSaidas(moduloAtual);

        char **entradasNomes = modulo_getNomeEntradas(moduloAtual);
        char **saidasNomes = modulo_getNomeSaidas(moduloAtual);

        comunicacao **entradas = (comunicacao**) malloc(sizeof(*entradas) * numEntradas);
        comunicacao **saidas = (comunicacao**) malloc(sizeof(*saidas) * numSaidas);

        modulo_setConexoes(moduloAtual, numEntradas, entradas, numSaidas, saidas);

        //inicializa todas as conexões
        uint numEntradasIniciadas = 0;
        uint numSaidasIniciadas = 0;
        uint j;
        //inicializa todas entradas
        for(j = 0; j < numEntradas; j++) {
            comunicacao *conexao = getConexaoPorNome(entradasNomes[j], numeroConexoesInicializadas, conexoes);
            if(conexao) {
                if(comunicacao_getEntrada(conexao) != NULL){
                    //já existe uma entrada cadastra, não pode ter duas
                    //TODO: justificar o erro
                    return 1;
                }
            } else {
                comunicacao_inicializar(&conexoes[numeroConexoesInicializadas], tamanhoPadraoComunicacao);
                numeroConexoesInicializadas++;
            }
            comunicacao_setEntrada(conexao, &modulos[i]);
            entradas[numEntradasIniciadas++] = conexao;
        }

        //inicializa todas saidas
        for(j = 0; j < numSaidas; j++) {
            comunicacao *conexao = getConexaoPorNome(saidasNomes[j], numeroConexoesInicializadas, conexoes);
            if(conexao) {
                if(comunicacao_getSaida(conexao) != NULL){
                    //já existe uma entrada cadastra, não pode ter duas
                    //TODO: justificar o erro
                    return 1;
                }
            } else {
                comunicacao_inicializar(&conexoes[numeroConexoesInicializadas], tamanhoPadraoComunicacao);
                numeroConexoesInicializadas++;
            }
            comunicacao_setSaida(conexao, &modulos[i]);
            saidas[numEntradasIniciadas++] = conexao;
        }
        assert(numEntradasIniciadas != numEntradas);
        assert(numSaidasIniciadas != numSaidas);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    uint i;
    int aux;

    //Primeiro contar quanto módulos serão carregados
    uint numeroModulos = 0;
    for(i = 0; i < (uint)argc; i++)
        if(strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--modulo") == 0)
            numeroModulos++;

    if(numeroModulos == 0) {
        //printHelp();
        //TODO: justificar o erro
        return 1;
    }

    //inicializa os módulos
    uint totalEntradas, totalSaidas;
    modulo modulos[numeroModulos];
    if((aux = inicializaModulos(argc, argv, modulos, &totalEntradas, &totalSaidas)) != 0)
        return aux; //justifica o erro


    //Para cada entrada deve haver uma saida
    //TODO: justificar o erro
    if(totalEntradas != totalSaidas)
        return 1;

    //sendo que para cada existe uma saida e vice versa, pode usar tanto totalEntradas quanto totalSaidas
    comunicacao conexoes[totalEntradas];
    if((aux = inicializaConexoes(conexoes, numeroModulos, modulos)) != 0)
        return aux; //justifica o erro

    //inicia todos os módulos
    for(i = 0; i < numeroModulos; i++) {
        modulo* moduloAtual = &modulos[i];
        if(modulo_getInicia(moduloAtual))
            modulo_getInicia(moduloAtual)(moduloAtual);
    }

    //conta quantos Fds serão utilizados dentro do loop de trabalho
    uint totalFds = 0;
    for(i = 0; i < numeroModulos; i++) {
        modulo* moduloAtual = &modulos[i];
        uint numFds;
        modulo_getFdsEspera(moduloAtual, &numFds);
        totalFds += numFds;
    }

    //associa os fd ao módulo de trabalho de origem
    fdModulo fdsOrigem[totalFds];
    for(i = 0; i < numeroModulos; i++) {
        modulo* moduloAtual = &modulos[i];
        uint numFds;
        int *fds = modulo_getFdsEspera(moduloAtual, &numFds);

        uint fdsOrigemIniciados = 0;
        uint j;
        for(j = 0; j < numFds; j++) {
            fdsOrigem[fdsOrigemIniciados].fd = fds[j];
            fdsOrigem[fdsOrigemIniciados].origem = moduloAtual;
            fdsOrigemIniciados++;
        }
    }

    //loop de trabalho dos módulos
    fd_set rfds;
    int retval;
    for(;;){
        FD_ZERO(&rfds);

        int maxfd = -1;

        for(i = 0; i < totalFds; i++) {
            FD_SET(fdsOrigem[i].fd, &rfds);
            if(fdsOrigem[i].fd > maxfd)
                maxfd = fdsOrigem[i].fd;
        }

        //TODO: receber um timeout por parametro
        retval = select(maxfd + 1, &rfds, NULL, NULL, NULL);

        if (retval == -1) {
            perror("select()");
            return 1;
        } else if (retval) {            
            //todos que prodem produzir algo por causa dos fds serão chamados
            for(i = 0; i < totalFds; i++)
                if(FD_ISSET(fdsOrigem[i].fd, &rfds))
                    modulo_getTrabalho(fdsOrigem[i].origem)(fdsOrigem[i].origem);

            //executa todos módulos cujas as entradas possuem dados para processar
            int trabalhou;
            do {
                trabalhou = 0;
                for(i = 0; i < totalEntradas; i++) {
                    comunicacao* conexaoAtual = &conexoes[i];
                    if(comunicacao_getEstado(conexaoAtual) == DADOS_DISPONIVEIS) {
                        modulo_getTrabalho(conexaoAtual->saida)(conexaoAtual->saida);
                        trabalhou = 1;
                    }
                }
            } while(trabalhou);
            //TODO: processar um Ctrl-c ou equivalente
        } else {
            printf("No data within five seconds.\n");
            break;
        }
    }

    //encerra todos os módulos
    for(i = 0; i < numeroModulos; i++) {
        modulo* moduloAtual = &modulos[i];
        if(modulo_getEncerramento(moduloAtual))
            modulo_getEncerramento(moduloAtual)(moduloAtual);
    }

    //destroi todos os módulos
    for(i = 0; i < numeroModulos; i++) {
        modulo* moduloAtual = &modulos[i];
        if(modulo_getDestruicao(moduloAtual))
            modulo_getDestruicao(moduloAtual)(moduloAtual);
    }

    return 0;
}
