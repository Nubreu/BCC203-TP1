#ifndef TADF_H
#define TADF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

#define MAXCHAVE 10000
#define MINCHAVE 0
#define ITENSPAGINA 4
typedef struct
{
  int chave;
  long int dado1;
  char dado2[1000];
  char dado3[5000];
}Registro;

typedef struct
{
  int tam;
  int item[ITENSPAGINA];
}Pagina;

bool arquivoTextoExiste(char* caminho);
bool arquivoBinExiste(char* caminho);
Registro lerReg(FILE* arqBin);

#endif