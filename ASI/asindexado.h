#ifndef ASSINDEXADO_H
#define ASSINDEXADO_H

#include <stdio.h>

// definição de uma entrada da tabela de índice das páginas
typedef struct
{
  // A posicao é desnecessária uma ves que sera utilizado o iterador do for
  int chave;
} Tipoindice;
// definição de um item do arquivo de dados
typedef struct
{
  char titulo[31];
  int chave;
  float preco;
} Tipoitem;

int pesquisa(Tipoindice tab[], int tam, Tipoitem *item, FILE *arq);
void gerarTabela(char* nome, char* arquivo);



#endif