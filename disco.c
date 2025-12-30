#include <stdio.h>
#include "funcAloca.h"

void iniciarDisco(Bloco *disco) {
    for (int i = 0; i < TAM_DISCO; i++) {
        disco[i].ocupado = FALSE;
        disco[i].idArquivoNoBloco = -1;
        disco[i].nextBloco = -1;
    }
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
            if (cont == 0) {
                inicio = i;
            }

            cont++;

            if (cont == file->tamArquivo){
                break;
            }
        } else {
            cont = 0;
            inicio = -1;
        }
    }

    if (cont < file->tamArquivo){
        return FALSE;
    }

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

// void alocacaoIndexada(Bloco disco, Arquivo file) {

// }

void removerArquivo(Bloco *disco, Arquivo *file) {
    if (file->inicioBloco == -1) {
        printf("Arquivo nao encontrado.\n");
        return;
    }

    int atual = file->inicioBloco;

    while (atual != -1) {
        int prox = disco[atual].nextBloco;

        disco[atual].ocupado = FALSE;
        disco[atual].idArquivoNoBloco = -1;
        disco[atual].nextBloco = -1;

        atual = prox;
    }

    file->inicioBloco = -1;
    printf("Arquivo removido com sucesso.\n");
}

void exibirEspacoDisco(Bloco *disco) {
    printf("\n=========================================\n");
    printf("        VISUALIZACAO DO DISCO\n");
    printf("=========================================\n");

    for (int i = 0; i < TAM_DISCO; i++) {
        if (disco[i].ocupado)
            printf("|%02d", disco[i].idArquivoNoBloco);
        else
            printf("|__");

        if ((i + 1) % 16 == 0)
            printf("|\n");
    }

    printf("\nLegenda:\n");
    printf("|__| -> Bloco livre\n");
    printf("|XX| -> Bloco ocupado pelo arquivo XX\n");
    printf("=========================================\n");
}

void menu(Bloco *disco) {
    int opcao;
    Arquivo file;

    do {
        printf("\n================ MENU ================\n");
        printf("1 - Exibir disco\n");
        printf("2 - Alocar arquivo (Contigua)\n");
        printf("3 - Alocar arquivo (Encadeada)\n");
        printf("4 - Remover arquivo\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                exibirEspacoDisco(disco);
                break;

            case 2:
                printf("Nome do arquivo: ");
                scanf("%s", file.nome);
                printf("ID do arquivo: ");
                scanf("%d", &file.idArquivo);
                printf("Tamanho do arquivo (em blocos): ");
                scanf("%d", &file.tamArquivo);

                file.inicioBloco = -1;

                if (alocacaoContigua(disco, &file))
                    printf("Arquivo alocado com sucesso (Contigua).\n");
                else
                    printf("Falha na alocacao contigua.\n");

                exibirEspacoDisco(disco);
                break;

            case 3:
                printf("Nome do arquivo: ");
                scanf("%s", file.nome);
                printf("ID do arquivo: ");
                scanf("%d", &file.idArquivo);
                printf("Tamanho do arquivo (em blocos): ");
                scanf("%d", &file.tamArquivo);

                file.inicioBloco = -1;

                alocacaoEncadeada(disco, &file);

                if (file.inicioBloco != -1)
                    printf("Arquivo alocado com sucesso (Encadeada).\n");
                else
                    printf("Falha na alocacao encadeada.\n");

                exibirEspacoDisco(disco);
                break;

            case 4:
                printf("ID do arquivo a remover: ");
                scanf("%d", &file.idArquivo);

                removerArquivo(disco, &file);
                exibirEspacoDisco(disco);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);
}
