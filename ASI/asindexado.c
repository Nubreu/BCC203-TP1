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
//             texto gerado    binario lido
void visualizar(char *nome, char *arquivo)
{
  FILE *arq;
  arq = fopen(arquivo, "rb");
  FILE *arqTxt;
  arqTxt = fopen(nome, "w");
  int c, cont;
  if (arq == NULL)
    return;
  if (arqTxt == NULL)
  {
    fclose(arq);
    return;
  }
  cont = 0;
  while (fread(&c, sizeof(int), 1, arq) == 1)
  {
    fprintf(arqTxt, "%d ", c);
    cont++;
    if (cont == 2)
    {
      fprintf(arqTxt, "\n");
      cont = 0;
    }
  }

  fclose(arqTxt);
  fclose(arq);
}
//             tabela gerada   binario lido
void gerarTabela(char *tabela, char *bin)
{
  FILE *arqBin, *arqTabela;
  if ((arqTabela = fopen(tabela, "wb")) == NULL)
    return;
  if ((arqBin = fopen(bin, "rb")) == NULL)
  {
    fclose(arqTabela);
    return;
  }
  int dado;
  while (fread(&dado, sizeof(int), 1, arqBin) == 1)
  {
    fwrite(&dado, sizeof(dado), 1, arqTabela);
    fseek(arqBin, (ITENSPAGINA - 1) * sizeof(int), SEEK_CUR);
  }

  fclose(arqBin);
  fclose(arqTabela);
  fflush(stdout);
  return;
}

int encontrarPagina(char *caminho, int chaveBusca, int modo)
{
  int chaveAtual, chaveProx;
  chaveAtual = -1;
  chaveProx = -1;
  int pos = 0;
  FILE *arq;

  if (chaveBusca > MAXCHAVE || chaveBusca < MINCHAVE)
    return -1;
  /*
  if(!arquivoBinExiste(caminho))
    return -1;
  */
  arq = fopen(caminho, "rb");
  while (fread(&chaveAtual, sizeof(int), 1, arq) == 1)
  {
    if (chaveAtual == chaveBusca)
      return pos;
     
    if (modo != 3)
    {
      if ((chaveAtual > chaveBusca) && modo == 1)
      {
        return --pos;
      }
      if ((chaveAtual < chaveBusca) && modo == 2)
        return pos;
    }
    pos++;
  }
  return pos;
}

void imprimirPagina(char* caminho, int desloc)
{
  FILE* arq = fopen(caminho,"rb");
  fseek(arq, desloc * (ITENSPAGINA * sizeof(int)),SEEK_SET);
  int var;
  for(int i = 0; i < ITENSPAGINA; i++)
  {
    fread(&var,sizeof(int),1,arq);
    printf("%d ",var);
  }
  printf("\n");
  fclose(arq);
} 

int main()
{
  gerarTabela("tabelas/tabelaCrescente.bin", "../dados/crescente.bin");
  visualizar("tabelas/tabelaCrescente.txt", "tabelas/tabelaCrescente.bin");
  int desloc;
  desloc = encontrarPagina("tabelas/tabelaCrescente.bin", 20, 1);
  printf("Pag: %d \n\n", desloc);
  imprimirPagina("../dados/crescente.bin",desloc);
  return 0;
}