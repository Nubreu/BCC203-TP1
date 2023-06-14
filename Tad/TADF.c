#include "TADF.h"
bool arquivoBinExiste(char* caminho)
{
  FILE* arq = fopen(caminho,"rb");
  if(arq == NULL)
    return false;
  fclose(arq);
  return true;
}

bool arquivoTextoExiste(char* caminho)
{
  FILE* arq = fopen(caminho,"r");
  if(arq == NULL)
    return false;
  fclose(arq);
  return true;
}

int main(){
  Registro a;
  printf("%c",a.dado2);
  for(int i = 0; i < 1000;i++)
  {
    printf("%c",a.dado2[i]);
  }
  return 0;
}

Registro lerReg(FILE* arqBin)
{
  Registro reg;
  fread(&reg.chave,sizeof(reg.chave),1,arqBin);
  fread(&reg.dado1,sizeof(reg.dado1),1,arqBin);
  fread( reg.dado2,sizeof(reg.dado2),1,arqBin);
  fread( reg.dado3,sizeof(reg.dado3),1,arqBin);
  return reg;
}