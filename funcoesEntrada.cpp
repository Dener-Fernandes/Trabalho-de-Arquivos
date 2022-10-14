// Aqui vai ter muita batatinha.
#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>

void ler_e_inserir(char nomeArquivo01[MAX], char nomeArquivo02[MAX],
                   char nomeArquivo03[MAX], char nomeArquivo04[MAX],
                   tCursosEPesos *&cursosEPesos, tCursosEVagas *&cursosEVagas,
                   tDados *&dados, tAcertos *&acertos) {
  FILE *arquivo01, *arquivo02, *arquivo03, *arquivo04;

  arquivo01 = fopen(nomeArquivo01, "r");
  // arquivo02 = fopen(nomeArquivo02, "r");
  // arquivo03 = fopen(nomeArquivo03, "r");
  // arquivo04 = fopen(nomeArquivo04, "r");

  if (!arquivo01) {
    printf("Erro ao abrir os arquivos!");
    return;
  } else {

    int nCursos, nVagas, nDados, nAcertos;
    fscanf(arquivo01, "%d", &nCursos);
    // fscanf(arquivo02, "%d", &nVagas);
    // fscanf(arquivo03, "%d", &nDados);
    // fscanf(arquivo04, "%d", &nAcertos);

    tCursosEPesos *novo, *p;

    while (nCursos > 0) {
      novo = (tCursosEPesos *)malloc(sizeof(tCursosEPesos));

      fscanf(arquivo01, "%d %[^/0123456789] %d %d %d %d %d", &novo->codigo,
             novo->nome, &novo->red, &novo->mat, &novo->lin, &novo->hum,
             &novo->nat);
      novo->prox = NULL;

      printf("%s\n", novo->nome);

      if (!cursosEPesos) {
        cursosEPesos = novo;
      } else {
        p = cursosEPesos;

        while (p->prox != NULL) {
          p = p->prox;
        }

        p->prox = novo;
      }

      nCursos--;
    }
  }
  fclose(arquivo01);
  // fclose(arquivo02);
  // fclose(arquivo03);
  // fclose(arquivo04);
  printf("Batata");
  return;
}
