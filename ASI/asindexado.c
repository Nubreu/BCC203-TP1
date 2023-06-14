#include <stdio.h>
#include <stdbool.h>
#include "asindexado.h"
#include "../Tad/TADF.h"

/*
int pesquisa(Tipoindice tab[], int tam, Tipoitem *item, FILE *arq)
{
  Tipoitem pagina[ITENSPAGINA];
  int i, quantitens;
  long desloc;
  // procura pela página onde o item pode se encontrar
  i = 0;
  while (i < tam && tab[i].chave <= item->chave)
    i++;
  // caso a chave desejada seja menor que a 1a chave, o item
  // não existe no arquivo
  if (i == 0)
    return 0;
  else
  {
    // a ultima página pode não estar completa
    if (i < tam)
      quantitens = ITENSPAGINA;
    else
    {
      fseek(arq, 0, SEEK_END);
      quantitens = (ftell(arq) / sizeof(Tipoitem)) % ITENSPAGINA;
    }
    // lê a página desejada do arquivo
    desloc = (tab[i - 1].posicao - 1) * ITENSPAGINA * sizeof(Tipoitem);

    desloc = (tab[i - 1].posicao - 1) * ITENSPAGINA * sizeof(Tipoitem);
    fseek(arq, desloc, SEEK_SET);
    fread(&pagina, sizeof(Tipoitem), quantitens, arq);
    // pesquisa sequencial na página lida
    for (i = 0; i < quantitens; i++)
      if (pagina[i].chave == item->chave)
      {
        *item = pagina[i];
        return 1;
      }
    return 0;
  }
}
*/

//                 texto gerado  binario lido
void visualizarTab(char *nome, char *arquivo)
{
  FILE *arq;
  arq = fopen(arquivo, "rb");
  FILE *arqTxt;
  arqTxt = fopen(nome, "w");
  Registro reg;
  if (arq == NULL)
    return;
  if (arqTxt == NULL)
  {
    fclose(arq);
    return;
  }

  while (fread(&reg.chave, sizeof(int), 1, arq) == 1)
  {
    fprintf(arqTxt, "%d\n", reg.chave);
  }
  fclose(arqTxt);
  fclose(arq);
}
//             tabela gerada   binario lido
void gerarTabela(char *tabela, char *bin)
{
  FILE *arqBin, *arqTabela;
  Registro reg;
  if ((arqTabela = fopen(tabela, "wb")) == NULL)
    return;
  if ((arqBin = fopen(bin, "rb")) == NULL)
  {
    fclose(arqTabela);
    return;
  }
  
  while (fread(&reg, sizeof(Registro), 1, arqBin) == 1)
  {
    fseek(arqBin, (ITENSPAGINA - 1) * sizeof(Registro), SEEK_CUR);
    fwrite(&reg.chave, sizeof(reg.chave), 1, arqTabela);
  }

  fclose(arqBin);
  fclose(arqTabela);
  fflush(stdout);
  return;
}

int encontrarPagina(char *caminho, int chaveBusca, int modo)
{
  int chaveAtual;
  chaveAtual = -1;
  int pos = 0;
  FILE *arq;

  if (chaveBusca > MAXCHAVE || chaveBusca < MINCHAVE)
    return -1;
  arq = fopen(caminho, "rb");
  while (fread(&chaveAtual, sizeof(int), 1, arq) == 1)
  {
    if (chaveAtual == chaveBusca){
      return pos;
      fclose(arq);
    }
     
    if (modo != 3)
    {
      if ((chaveAtual > chaveBusca) || ((chaveAtual + ITENSPAGINA) >= MAXCHAVE) && modo == 1)
      {
        return pos;fclose(arq);
      }
      if ((chaveAtual > chaveBusca) || (pos == MAXCHAVE) && modo == 2){
        return --pos; fclose(arq);
      }
    }
    pos++;
  }
  fclose(arq);
  return pos;
}

void imprimirPagina(char* caminho, int desloc)
{
  FILE* arq = fopen(caminho,"rb");
  Registro reg;
  fseek(arq, desloc * (ITENSPAGINA * sizeof(Registro)),SEEK_SET);
  for(int i = 0; i < ITENSPAGINA; i++)
  {
    fread(&reg,sizeof(Registro),1,arq);
    printf("%d ",reg.chave);
  }
  printf("\n");
  fclose(arq);
} 

int main()
{
  gerarTabela("tabelas/tabelaCrescente.bin", "../dados/crescente.bin");
  int desloc;
  desloc = encontrarPagina("tabelas/tabelaCrescente.bin", MAXCHAVE, 1);
  printf("Pag: %d \n\n", desloc);
  imprimirPagina("../dados/crescente.bin",desloc);
  return 0;
}