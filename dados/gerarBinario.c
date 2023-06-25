#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../Tad/TADF.h"

int crescente()
{
  FILE *arq;
  Registro reg;
  arq = fopen("crescente.bin", "w+b");
  if (arq == NULL)
    return 0;

  for (int i = 0; i <= MAXCHAVE; i++)
  {
    reg.chave = i;
    fwrite(&reg, 1, sizeof(Registro), arq);
  }
  fclose(arq);
  return 1;
}

int decrescente()
{
  FILE *arq;
  Registro reg;

  arq = fopen("decrescente.bin", "w+b");
  if (arq == NULL)
    return 0;

  for (int i = MAXCHAVE; i != -1; i--)
  {
    reg.chave = i;
    fwrite(&reg, 1, sizeof(Registro), arq);
  }
  fclose(arq);
  return 1;
}

int aleatorio()
{
  FILE *arquivo = fopen("aleatorio.bin", "w+b");

  if (arquivo != NULL)
  {
    Registro registro;
    int *vetor = calloc(MAXCHAVE, sizeof(int));
    srand(time(NULL));

    int valido = 0;
    for (int i = 0; i < MAXCHAVE; i++)
    {
      valido = 0;
      while (valido == 0)
      {
        registro.chave = (rand() % MAXCHAVE);
        if (vetor[registro.chave] == 0)
        {
          vetor[registro.chave] = 1;
          valido = 1;
        }
      }
      registro.chave++;

      fwrite(&registro, sizeof(Registro), 1, arquivo);
    }

    free(vetor);
    fclose(arquivo);
    return 1;
  }
  else
  {
    return 0;
  }
}

void visualizarBin(char *nome, char *arquivo)
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
  while (fread(&reg, sizeof(Registro), 1, arq) == 1)
  {
    fprintf(arqTxt, "%d\n", reg.chave);
  }

  fclose(arqTxt);
  fclose(arq);
}

int main()
{

  if (crescente() != 1)
  {
    printf("[X] ERRO NO ARQUIVO CRESCENTE\n");
  }
  else
    printf("-- CRESCENTE COCLUIDO COM SUCESSO\n");
  /*
  if (decrescente() != 1)
  {
    printf("[X] ERRO NO ARQUIVO DECRESCENTE\n");
  }
  else
    printf("-- DECRESCENTE COCLUIDO COM SUCESSO\n");

  if (aleatorio() != 1)
  {
    printf("[X] ERRO NO ARQUIVO ALEATORIO\n");
  }
  else
    printf("-- ALEATORIO COCLUIDO COM SUCESSO\n");
  */
  //visualizarBin("crescente.txt","crescente.bin");
  //visualizarBin("decrescente.txt","decrescente.bin");
  //visualizarBin("aleatorio.txt", "aleatorio.bin");

  return 0;
}
