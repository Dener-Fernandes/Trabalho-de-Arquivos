#include "funcoesEntrada.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  tCursosEPesos *cursosEPesos = NULL;
  tCursosEVagas *cursosEVagas = NULL;
  tDados *dados = NULL;
  tAcertos *acertos = NULL;

  // Variável que irá manipular o arquivo.
  FILE *arquivo;
  char nome01[MAX], nome02[MAX], nome03[MAX], nome04[MAX];
  int tamanhoArquivo;
  char cursoNome[MAX];

  printf("Informe os nomes dos arquivos\n");
  scanf(" %s", nome01);
  scanf(" %s", nome02);
  scanf(" %s", nome03);
  scanf(" %s", nome04);

  ler_e_inserir(nome01, nome02, nome03, nome04, cursosEPesos, cursosEVagas,
                dados, acertos);

  free(cursosEPesos);
  free(cursosEVagas);
  free(dados);
  free(acertos);

  return 0;
}
