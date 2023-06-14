#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../Tad/TADF.h"

int crescente()
{
  FILE *arq;
  Registro reg;
  arq = fopen("crescente.bin", "wb");
  if (arq == NULL)
    return 0;

  for (int i = 0; i <= MAXCHAVE; i++)
  {
    reg.chave = i;
    fwrite(&reg,1,sizeof(Registro),arq);
  }
  fclose(arq);
  return 1;
}


int decrescente()
{
  FILE *arq;
  Registro reg;
  
  arq = fopen("decrescente.bin", "wb");
  if (arq == NULL)
    return 0;

  for (int i = MAXCHAVE - 1; i != -1; i--)
  {
    reg.chave = i;
    fwrite(&reg,1,sizeof(Registro),arq);
  }
  fclose(arq);
  return 1;
}
int aleatorio()
{
  FILE *arq;
  int chave;
  Registro reg;
  srand(time(NULL));
  arq = fopen("aleatorio.bin", "wb");
  if (arq == NULL)
    return 0;

  for (int i = 0; i < MAXCHAVE; i++)
  {
    chave = rand() % (MAXCHAVE - 1);
    reg.chave = chave;
    fwrite(&reg,1,sizeof(Registro),arq);
  }
  fclose(arq);
  return 1;
}

void visualizarBin(char *nome, char* arquivo)
{
  FILE *arq;
  arq = fopen(arquivo, "rb");
  FILE *arqTxt;
  Registro reg;
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
  while (fread(&reg, sizeof(Registro),1, arq) == 1)
  {
    fprintf(arqTxt, "%d\n", reg.chave);
  }

  fclose(arqTxt);
  fclose(arq);
}

int main()
{
  if(crescente() != 1)
  {
    printf("[X] ERRO NO ARQUIVO CRESCENTE\n");
  }
  else printf("-- CRESCENTE COCLUIDO COM SUCESSO\n");
  /*
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
  */
  
  visualizarBin("crescente.txt","crescente.bin");
  //visualizarBin("decrescente.txt","decrescente.bin");
  //visualizarBin("aleatorio.txt","aleatorio.bin");

  return 0;
}
