#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../Tad/TADF.h"


//#define MAXCHAVE 8333333

int crescente()
{
  FILE *arq;
  arq = fopen("crescente.bin", "wb");
  if (arq == NULL)
    return 0;

  for (long i = 0; i < MAXCHAVE; i++)
  {
    fwrite(&i, 1, sizeof(int), arq);
  }
  fclose(arq);
  return 1;
}
int decrescente()
{
  FILE *arq;
  arq = fopen("decrescente.bin", "wb");
  if (arq == NULL)
    return 0;

  for (long i = MAXCHAVE - 1; i != -1; i--)
  {
    fwrite(&i, 1, sizeof(int), arq);
  }
  fclose(arq);
  return 1;
}
int aleatorio()
{
  FILE *arq;
  long aleatorio;
  srand(time(NULL));
  arq = fopen("aleatorio.bin", "wb");
  if (arq == NULL)
    return 0;

  for (long i = 0; i < MAXCHAVE; i++)
  {
    aleatorio = rand() % (MAXCHAVE - 1);
    fwrite(&aleatorio, 1, sizeof(int), arq);
  }
  fclose(arq);
  return 1;
}
void visualizar(char *nome, char* arquivo)
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
  while (fread(&c, sizeof(int),1, arq) == 1)
  {
    fprintf(arqTxt, "%d ", c);
    cont++;
    if (cont == 10){
      fprintf(arqTxt, "\n");
      cont = 0;
    }
  }

  fclose(arqTxt);
  fclose(arq);
}

int main()
{
  FILE *arq;
  int c;
  int cont = 0;
  
  if(crescente() != 1)
  {
    printf("[X] ERRO NO ARQUIVO CRESCENTE\n");
  }
  else printf("-- CRESCENTE COCLUIDO COM SUCESSO\n");

  if(decrescente() != 1)
  {
    printf("[X] ERRO NO ARQUIVO DECRESCENTE\n");
  }
  else printf("-- DECRESCENTE COCLUIDO COM SUCESSO\n");

  if(aleatorio() != 1)
  {
    printf("[X] ERRO NO ARQUIVO ALEATORIO\n");
  }
  else printf("-- ALEATORIO COCLUIDO COM SUCESSO\n");
  
  
  arq = fopen("aleatorio.bin","rb");

  visualizar("aleatorio.txt","aleatorio.bin");
  visualizar("crescente.txt","crescente.bin");
  visualizar("decrescente.txt","decrescente.bin");

  fclose(arq);
  return 0;
}
