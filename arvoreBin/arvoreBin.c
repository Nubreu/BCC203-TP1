#include "../Tad/TADF.h"

int buscaBinaria(char *nome, int chave, int limiteSuperior)
{
  FILE *arq = fopen(nome, "r+b");
  Node no;
  if (arq == NULL)
    return -3;
  while (true)
  {
    fread(&no, sizeof(Node), 1, arq);
    if (no.reg.chave == chave)
    {
      return (ftell(arq) / sizeof(Node)) - 1;
    }
    else if (chave > no.reg.chave)
    {
      if (no.nDir == -1|| no.nDir > limiteSuperior)
        break;
      fseek(arq, sizeof(Node) * no.nDir, SEEK_SET);
    }
    else
    {
      if (no.nEsq == -1 || no.nEsq > limiteSuperior)
        break;
      fseek(arq, sizeof(Node) * no.nEsq, SEEK_SET);
    }
  }
  fclose(arq);
  return -1;
}

void inserirOdenado(FILE **arvore, Registro reg, int ordem, long int tam)
{
  Node no, pai;
  no.nDir = -1;
  no.nEsq = -1;
  no.reg = reg;
  if (tam == 0)
  {
    fwrite(&no, sizeof(Node), 1, *arvore);
    return;
  }
  if (ordem == 1)
  {
    fseek(*arvore, sizeof(Node) * (tam - 1), SEEK_SET);
    fread(&pai, sizeof(Node), 1, *arvore);
    pai.nDir = tam;
    fseek(*arvore, sizeof(Node) * (-1), SEEK_CUR);
    fwrite(&pai, sizeof(Node), 1, *arvore);
    fwrite(&no, sizeof(Node), 1, *arvore);
    return;
  }
  if (ordem == 2)
  {
    fseek(*arvore, sizeof(Node) * (tam - 1), SEEK_SET);
    fread(&pai, sizeof(Node), 1, *arvore);
    pai.nEsq = tam;
    fseek(*arvore, sizeof(Node) * (-1), SEEK_CUR);
    fwrite(&pai, sizeof(Node), 1, *arvore);
    fwrite(&no, sizeof(Node), 1, *arvore);
    return;
  }
  return;
}

void inserir(FILE **arvore, Registro reg, int tam)
{
  Node no, noLido, pai;
  long int posPai, posFilho;

  no.reg = reg;
  no.nDir = -1;
  no.nEsq = -1;

  pai.nDir = pai.nEsq = -1;

  posPai = 0;

  if (tam == 0)
  {
    fwrite(&no, sizeof(Node), 1, *arvore);
    return;
  }
  fseek(*arvore, posPai * sizeof(Node), SEEK_SET);

  while (true)
  {
    fseek(*arvore, posPai * sizeof(Node), SEEK_SET);
    fread(&noLido, sizeof(Node), 1, *arvore);
    pai = noLido;
    if (reg.chave > noLido.reg.chave)
    {
      if (noLido.nDir == -1)
        break;
      posPai = noLido.nDir;
    }
    else
    {
      if (noLido.nEsq == -1)
        break;
      posPai = noLido.nEsq;
    }
  }

  fseek(*arvore, 0, SEEK_END);
  posFilho = ftell(*arvore) / sizeof(Node);
  fwrite(&no, sizeof(Node), 1, *arvore);

  if (reg.chave > pai.reg.chave)
    pai.nDir = posFilho;
  else
    pai.nEsq = posFilho;

  fseek(*arvore, (posPai) * sizeof(Node), SEEK_SET);
  fwrite(&pai, sizeof(Node), 1, *arvore);

  return;
}

bool criarArvore(int ordem)
{
  FILE *arvore, *arqDados;
  int tam = 0;
  switch (ordem)
  {
  case 1:
    arqDados = fopen("../dados/crescente.bin", "r+b");
    break;
  case 2:
    arqDados = fopen("../dados/decrescente.bin", "r+b");
    break;
  case 3:
    arqDados = fopen("../dados/aleatorio.bin", "r+b");
    break;
  }

  switch (ordem)
  {
  case 1:
    arvore = fopen("arvores/arvoreCrescente.bin", "w+b");
    break;
  case 2:
    arvore = fopen("arvores/arvoreDecrescente.bin", "w+b");
    break;
  case 3:
    arvore = fopen("arvores/arvoreAleatoria.bin", "w+b");
    break;
  }

  if (arqDados == NULL)
    return false;
  if (arvore == NULL)
  {
    fclose(arqDados);
    return false;
  }
  tam = 0;
  Registro regLido;
  if (ordem == 1)
  {
    while (fread(&regLido, sizeof(Registro), 1, arqDados) == 1)
    {
      inserirOdenado(&arvore, regLido, 1,tam);
      tam++;
    }
  }
  else if (ordem == 2)
  {
    while (fread(&regLido, sizeof(Registro), 1, arqDados) == 1)
    {
      inserirOdenado(&arvore, regLido, 2,tam);
      tam++;
    }
  }
  else
  {
    while (fread(&regLido, sizeof(Registro), 1, arqDados) == 1)
    {
      inserir(&arvore, regLido, tam);
      tam++;
    }
  }

fclose(arvore);
fclose(arqDados);
return true;
}

void previewBin(char *nome)
{
  FILE *arq = fopen(nome, "r+b");
  Node no;
  while (fread(&no, sizeof(no), 1, arq))
  {
    printf("Chave: %d | nEsq: %d | nDir: %d\n", no.reg.chave, no.nEsq, no.nDir);
  }
  fclose(arq);
}

int main()
{

  //printf("%d \n", criarArvore(1));
  //previewBin("arvores/arvoreCrescente.bin");

  //printf("%d \n", criarArvore(2));
  //  previewBin("arvores/arvoreDecrescente.bin");

  // printf("%d \n", criarArvore(3));
  // previewBin("arvores/arvoreAleatoria.bin");

  //int busca, limiteSuperior;
  //limiteSuperior = 10000;
  //busca = buscaBinaria("arvores/arvoreCrescente.bin", 76600, limiteSuperior);
  //busca = buscaBinaria("arvores/arvoreDecrescente.bin", 76600, limiteSuperior);
  //busca = buscaBinaria("arvores/arvoreAleatoria.bin", 10000, limiteSuperior);

  /*
  FILE *arq = fopen("arvores/arvoreCrescente.bin", "r+b");
  fseek(arq, sizeof(Node) * busca, SEEK_SET);
  Node no;
  fread(&no, sizeof(Node), 1, arq);
  printf("\n%d \n", no.reg.chave);
  fclose(arq);
  */
  return 0;
}
