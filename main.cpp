#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

  tArquivos arquivosNomes;
  FILE *arquivo01, *arquivo02, *arquivo03, *arquivo04, *arquivo05;
  tTamanhos tamanhos;

  strcpy(arquivosNomes.nome01, "cursos_e_pesos.txt");
  strcpy(arquivosNomes.nome02, "cursos_e_vagas.txt");
  strcpy(arquivosNomes.nome03, "dados.txt");
  strcpy(arquivosNomes.nome04, "acertos.txt");
  strcpy(arquivosNomes.nome05, "alteraNotaRedacao.txt");

  arquivo01 = fopen(arquivosNomes.nome01, "r");
  arquivo02 = fopen(arquivosNomes.nome02, "r");
  arquivo04 = fopen(arquivosNomes.nome04, "r");
  arquivo05 = fopen(arquivosNomes.nome05, "r");

  if (!(arquivo01 && arquivo02 && arquivo04))
  {
    printf("Erro ao abrir os arquivos!");
    return 0;
  }
  else
  {
    int x = fscanf(arquivo01, "%d", &tamanhos.max01);
    int y = fscanf(arquivo02, "%d", &tamanhos.max02);
    tamanhos.max03 = pegarTamanhoArquivoDados(arquivosNomes, tamanhos);
    int z = fscanf(arquivo04, "%d", &tamanhos.max04);
    int a = fscanf(arquivo05, "%d", &tamanhos.max05);
    fclose(arquivo01);
    fclose(arquivo02);
    fclose(arquivo04);
  }

  // tCursosEPesos cursosEPesos[tamanhos.max01];
  tCursosEPesos *cursosEPesos =
      (tCursosEPesos *)calloc(tamanhos.max01, sizeof(tCursosEPesos));

  tCursosEVagas *cursosEVagas =
      (tCursosEVagas *)calloc(tamanhos.max02, sizeof(tCursosEVagas));

  tDados *dados = (tDados *)calloc(tamanhos.max03, sizeof(tDados));
  tAcertos *acertos = (tAcertos *)calloc(tamanhos.max04, sizeof(tAcertos));

  tPontuacao *pontuacao =
      (tPontuacao *)calloc(tamanhos.max04, sizeof(tPontuacao));

  tMediaAcertos mediaAcertos = {0.0};
  tDesvioPadrao desvioPadrao = {0.0};
  tAlteraRed *alteraRedacao =
      (tAlteraRed *)calloc(tamanhos.max05, sizeof(tAlteraRed));

  ler_e_inserir(arquivosNomes, tamanhos, cursosEPesos, cursosEVagas, dados,
                acertos, alteraRedacao);

  calcularMediaEDesvioPadrao(acertos, &mediaAcertos, tamanhos, &desvioPadrao);

  calcularPontuacao(pontuacao, acertos, tamanhos, &mediaAcertos, &desvioPadrao,
                    dados, cursosEPesos);

  for (int i = 0; i < tamanhos.max04; i++)
  {
    if (pontuacao[i].inscricao == 548349)
    {
      printf("%d %.3f %.3f %.3f %.3f %d %s %.3f\n", pontuacao[i].inscricao,
             pontuacao[i].pontuacaoV_lin, pontuacao[i].pontuacaoV_mat,
             pontuacao[i].pontuacaoV_nat, pontuacao[i].pontuacaoV_hum,
             pontuacao[i].red, pontuacao[i].vaga, pontuacao[i].notaFinal);
    }
  }

  alterarNotaRedacao(tamanhos, alteraRedacao, acertos);

  calcularPontuacao(pontuacao, acertos, tamanhos, &mediaAcertos, &desvioPadrao,
                    dados, cursosEPesos);

  for (int i = 0; i < tamanhos.max04; i++)
  {
    if (pontuacao[i].inscricao == 548349)
    {
      printf("%d %.3f %.3f %.3f %.3f %d %s %.3f\n", pontuacao[i].inscricao,
             pontuacao[i].pontuacaoV_lin, pontuacao[i].pontuacaoV_mat,
             pontuacao[i].pontuacaoV_nat, pontuacao[i].pontuacaoV_hum,
             pontuacao[i].red, pontuacao[i].vaga, pontuacao[i].notaFinal);
    }
  }

  return 0;
}