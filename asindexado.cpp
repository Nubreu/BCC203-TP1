#include <iostream>
#include <stdio.h>
using namespace std;
#define ITENSPAGINA 4
#define MAXTABELA 100
// definição de uma entrada da tabela de índice das páginas
typedef struct
{
  int posicao;
  int chave;
} tipoindice;
// definição de um item do arquivo de dados
typedef struct
{
  char titulo[31];
  int chave;
  float preco;
} tipoitem;

int pesquisa(tipoindice tab[], int tam,
             tipoitem *item, FILE *arq)
{
  tipoitem pagina[ITENSPAGINA];
  int i, quantitens;
  long desloc;
  // procura pela página onde o item pode se encontrar
  i = 0;
  while (i < tam && tab[i].chave <= item->chave) i++;
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
      quantitens = (ftell(arq) / sizeof(tipoitem)) % ITENSPAGINA;
    }
    // lê a página desejada do arquivo
    desloc = (tab[i - 1].posicao - 1) * ITENSPAGINA * sizeof(tipoitem);

    desloc = (tab[i - 1].posicao - 1) * ITENSPAGINA * sizeof(tipoitem);
    fseek(arq, desloc, SEEK_SET);
    fread(&pagina, sizeof(tipoitem), quantitens, arq);
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
int main()
{
  tipoindice tabela[MAXTABELA];
  FILE *arq;
  tipoitem x;
  int pos, cont;
  // abre o arquivo de dados
  if ((arq = fopen("livros.bin", "rb")) == NULL)
  {
    cout << "Erro na abertura do arquivo\n";
    return 0;
  }

  // gera a tabela de índice das páginas
  cont = 0;
  pos = 0;
  while (fread(&x, sizeof(x), 1, arq) == 1)
  {
    cont++;
    if (cont % ITENSPAGINA == 1)
    {
      tabela[pos].chave = x.chave;
      tabela[pos].posicao = pos + 1;
      pos++;
    }
  }
  fflush(stdout);
  cout << "Código do livro desejado:";
  cin >> x.chave;
  // ativa a função de pesquisa
  if (pesquisa(tabela, pos, &x, arq))
    printf("Livro %s (codigo %d) foi localizado",
           x.titulo, x.chave);
  else
    printf("Livro de código %d nao foi localizado", x.chave);

  fclose(arq);
  return 0;
}