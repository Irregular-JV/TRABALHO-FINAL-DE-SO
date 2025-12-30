#ifndef _FUNCA_ALOCACAO_
#define _FUNC_ALOCACAO_
#include "blocoMemoria.h"

int alocacaoContigua(Bloco *disco, Arquivo *file);
void alocacaoEncadeada(Bloco *disco, Arquivo *file);
// void alocacaoIndexada(Bloco *disco, Arquivo *file);

void removerArquivo(Bloco *disco, Arquivo *file);
void exibirEspacoDisco(Bloco *disco);
void menu(Bloco *disco);

#endif