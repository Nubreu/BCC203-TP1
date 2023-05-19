#ifndef TADF_H
#define TADF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

#define MAXCHAVE 1000 - 1
#define MINCHAVE 0
#define ITENSPAGINA 10

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

#endif