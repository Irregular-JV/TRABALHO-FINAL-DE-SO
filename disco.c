#include <stdio.h>
#include "funcAloca.h"

void iniciarDisco(Bloco disco) {
    
}

void imprimirDisco(Bloco disco) {

}

int alocacaoContigua(Bloco* disco, Arquivo* file) {
    int cont = 0;
    int inicio = -1;
    if (disco == NULL || file == NULL){
        return FALSE;
    }
    if (file->tamArquivo > TAM_DISCO){
        return FALSE;
    }

    for (int i = 0; i < TAM_DISCO; i++) {
        if (disco[i].ocupado == FALSE) {
            if (cont == 0)
                inicio = i;

            cont++;

            if (cont == file->tamArquivo)
                break;
        } else {
            cont = 0;
            inicio = -1;
        }
    }

    if (cont < file->tamArquivo)
        return FALSE;

    file->inicioBloco = inicio;

    for (int i = inicio; i < inicio + file->tamArquivo; i++) {
        disco[i].ocupado = TRUE;
        disco[i].idArquivoNoBloco = file->idArquivo;
    }

    return TRUE;
}


void alocacaoEncadeada(Bloco* disco, Arquivo* file) {
    int prev = -1;
    int tamanho = file->tamArquivo;
    int blocos_alocados[TAM_DISCO];
    int count = 0;

    for(int i = 0; i < TAM_DISCO && tamanho > 0; i++){
        if (disco[i].ocupado == 0){
            disco[i].idArquivoNoBloco = file->idArquivo;
            disco[i].ocupado = TRUE;
            if(tamanho == file->tamArquivo){
                file->inicioBloco = i;
            }
            if(prev != -1){
                disco[prev].nextBloco = i;
            }
            blocos_alocados[count] = i;
            count++;
            prev = i;
            tamanho--;
        }
    }

    if(tamanho == 0 && prev != -1){
        disco[prev].nextBloco = -1;
    } else {
        for(int j = 0; j < count; j++){
            disco[blocos_alocados[j]].ocupado = FALSE;
            disco[blocos_alocados[j]].idArquivoNoBloco = 0;
            disco[blocos_alocados[j]].nextBloco = 0;
        }
        file->inicioBloco = -1; 
    }
    
}

void alocacaoIndexada(Bloco disco, Arquivo file) {

}

void removerArquivo(Bloco disco, Arquivo file) {

}

void exibirEspacoDisco(Bloco disco){

}