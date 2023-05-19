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