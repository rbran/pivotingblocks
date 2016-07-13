#ifndef COMUNICACAO_H
#define COMUNICACAO_H

typedef enum ComunicacaoEstado_Enum{
    dadosNaoConsumidos,
    dadosConsumidos
} ComunicacaoEstado;

typedef struct Comunicacao_Struct {
    ComunicacaoEstado estado;
    unsigned int tamanhoTotal;
    unsigned int tamanhoGuardado;
    void *posicao;
    void *dados;
}Comunicacao;

int guardar(Comunicacao self, unsigned int tamanho, void* buffer);
int retirar(Comunicacao self, unsigned int tamanho, void* buffer);
inline unsigned int getEspacoDisponivelRetirar(Comunicacao self);
inline unsigned int getEspacoDisponivelGuardar(Comunicacao self);
inline int getEstado(Comunicacao self);
inline int setEstado(Comunicacao self, int estado);

#endif // COMUNICACAO_H
