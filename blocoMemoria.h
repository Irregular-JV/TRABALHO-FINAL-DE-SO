#ifndef _BLOCO_MEMORIA_H
#define _BLOCO_MEMORIA_H
#define TRUE 1
#define FALSE 0
#define TAM_DISCO 255

typedef struct blocoMemoria{
    int ocupado;
    int idArquivoNoBloco;
    int nextBloco;
} Bloco;

typedef struct _arquivo{
    char nome [255];
    int idArquivo;
    int tamArquivo;
    int inicioBloco;
} Arquivo;

extern Bloco disco[TAM_DISCO];

void iniciarDisco(Bloco *disco);
void imprimirDisco(Bloco *disco);
#endif