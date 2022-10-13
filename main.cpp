#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  tCursosEPesos *cursosEPesos = NULL;

  // Variável que irá manipular o arquivo.
  FILE *arquivo;
  char nome[MAX];
  int tamanhoArquivo;
  char cursoNome[MAX];

  scanf(" %s", nome);

  // Abrindo o arquivo em modo de leitura.
  arquivo = fopen(nome, "r");

  if (!arquivo) {
    printf("Erro ao abrir o arquivo");
  } else {
    fscanf(arquivo, "%d", &tamanhoArquivo);

    while (feof(arquivo) == 0) {
      cursosEPesos = (tCursosEPesos *)malloc(sizeof(tCursosEPesos));
      fscanf(arquivo, "%d %s %d %d %d %d %d", &cursosEPesos->codigo, cursosEPesos->nome,);
      // printf("CURSO: %s ", cursoNome);
    }
  }

  // Fechando o arquivo.
  fclose(arquivo);
  return 0;
}
