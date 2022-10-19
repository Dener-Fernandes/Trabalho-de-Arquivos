#include "funcoesEntrada.h"
#include <stdio.h>
#include <stdlib.h>

// Ordem de inserção dos arquivos: cursos_e_pesos.,
// cursos_e_vagas.txt, dados.txt e acertos.txt

void imprimir(tDados *lst) {
  tDados *p;
  for (p = lst; p != NULL; p = p->prox) {
    printf("%d %d %d %s %d/%d/%d %s\n", p->codigo, p->qtdInscritos,
           p->inscricao, p->nome, p->dia, p->mes, p->ano, p->vaga);
  }

  return;
}

int main() {
  tCursosEPesos *cursosEPesos = NULL;
  tCursosEVagas *cursosEVagas = NULL;
  tDados *dados = NULL;
  tAcertos *acertos = NULL;
  tMediaAcertos mediaAcertos = {0.0};
  tDesvioPadrao desvioPadrao = {0.0};

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

  calcularMediaEDesvioPadrao(acertos, &mediaAcertos, &desvioPadrao);

  free(cursosEPesos);
  free(cursosEVagas);
  free(dados);
  free(acertos);

  return 0;
}
