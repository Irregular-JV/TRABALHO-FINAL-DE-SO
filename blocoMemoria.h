#ifndef _BLOCO_MEMORIA_H
#define _BLOCO_MEMORIA_H

    #define true 1
    #define false 0
    #define tam_disco 255

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

    
    
    extern Bloco disco[tam_disco];
    
    void iniciarDisco(Bloco disco);
    void imprimirDisco(Bloco disco);
#endif