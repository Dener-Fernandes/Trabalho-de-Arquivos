#include "funcoes.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pegarTamanhoArquivoDados(tArquivos arquivosNomes, tTamanhos tamanhos)
{
  int codigoCurso, i = 0;
  FILE *arquivo03;

  arquivo03 = fopen(arquivosNomes.nome03, "r");

  if (!arquivo03)
  {
    printf("Erro ao abrir o arquivo dados.txt");
    return 0;
  }
  else
  {
    int x = fscanf(arquivo03, "%d %d", &codigoCurso, &tamanhos.max03);

    while (tamanhos.max03)
    {
      int dados;
      char dadosNome[MAX];
      int x = fscanf(arquivo03, "%d %[^/0123456789] %d/%d/%d %s", &dados,
                     dadosNome, &dados, &dados, &dados, dadosNome);

      i++;
      tamanhos.max03--;

      if (!tamanhos.max03)
      {
        int x = fscanf(arquivo03, "%d %d", &codigoCurso, &tamanhos.max03);
      }
      dados = 0;
      strcpy(dadosNome, "");
    }
  }

  return i;
}

int ler_e_inserir(tArquivos arquivosNomes, tTamanhos tamanhos,
                  tCursosEPesos *cursosEPesos, tCursosEVagas *cursosEVagas,
                  tDados *dados, tAcertos *acertos, tAlteraRed *alteraRedacao)
{

  FILE *arquivo01, *arquivo02, *arquivo03, *arquivo04, *arquivo05;

  int codigoCurso, i = 0;

  arquivo01 = fopen(arquivosNomes.nome01, "r");
  arquivo02 = fopen(arquivosNomes.nome02, "r");
  arquivo03 = fopen(arquivosNomes.nome03, "r");
  arquivo04 = fopen(arquivosNomes.nome04, "r");
  arquivo05 = fopen(arquivosNomes.nome05, "r");

  if (!(arquivo01 && arquivo02 && arquivo03 && arquivo04 && arquivo05))
  {
    printf("Erro ao abrir os arquivos!");
    return 0;
  }
  else
  {

    int x = fscanf(arquivo01, "%d", &tamanhos.max01);
    int y = fscanf(arquivo02, "%d", &tamanhos.max02);
    int z = fscanf(arquivo03, "%d %d", &codigoCurso, &tamanhos.max03);
    int a = fscanf(arquivo04, "%d", &tamanhos.max04);
    int b = fscanf(arquivo05, "%d", &tamanhos.max05);

    for (int i = 0; i < tamanhos.max01; i++)
    {
      int x = fscanf(arquivo01, "%d %[^/0123456789] %d %d %d %d %d",
                     &cursosEPesos[i].codigo, cursosEPesos[i].nome,
                     &cursosEPesos[i].red, &cursosEPesos[i].mat,
                     &cursosEPesos[i].lin, &cursosEPesos[i].hum,
                     &cursosEPesos[i].nat);
    }

    for (int i = 0; i < tamanhos.max02; i++)
    {
      int x = fscanf(
          arquivo02, "%d %d %d %d %d %d %d %d %d %d %d %d",
          &cursosEVagas[i].codigo, &cursosEVagas[i].ac, &cursosEVagas[i].l1,
          &cursosEVagas[i].l3, &cursosEVagas[i].l4, &cursosEVagas[i].l5,
          &cursosEVagas[i].l7, &cursosEVagas[i].l8, &cursosEVagas[i].l9,
          &cursosEVagas[i].l11, &cursosEVagas[i].l13, &cursosEVagas[i].l15);
    }

    int qtdInscritos = tamanhos.max03;

    while (tamanhos.max03)
    {

      dados[i].codigo = codigoCurso;

      int x = fscanf(arquivo03, "%d %[^/0123456789] %d/%d/%d %s",
                     &dados[i].inscricao, dados[i].nome, &dados[i].dia,
                     &dados[i].mes, &dados[i].ano, dados[i].vaga);

      i++;
      tamanhos.max03--;

      if (!tamanhos.max03)
      {
        int x = fscanf(arquivo03, "%d %d", &codigoCurso, &tamanhos.max03);
        qtdInscritos = tamanhos.max03;
      }
    }

    for (int i = 0; i < tamanhos.max04; i++)
    {
      int x = fscanf(arquivo04, "%d %d %d %d %d %d", &acertos[i].inscricao,
                     &acertos[i].v_lin, &acertos[i].v_mat, &acertos[i].v_nat,
                     &acertos[i].v_hum, &acertos[i].red);
    }

    for (int i = 0; i < tamanhos.max05; i++)
    {
      fscanf(arquivo05, "%d %d %d", &alteraRedacao[i].inscricao,
             &alteraRedacao[i].notaAntes, &alteraRedacao[i].notaDepois);
    }
  }

  return 0;
}

void calcularMediaEDesvioPadrao(tAcertos acertos[MAX04],
                                tMediaAcertos *mediaAcertos, tTamanhos tamanhos,
                                tDesvioPadrao *desvioPadrao)
{

  int n = 0;
  for (int i = 0; i < tamanhos.max04; i++)
  {
    mediaAcertos->mediaV_hum += acertos[i].v_hum;
    mediaAcertos->mediaV_lin += acertos[i].v_lin;
    mediaAcertos->mediaV_mat += acertos[i].v_mat;
    mediaAcertos->mediaV_nat += acertos[i].v_nat;

    n++;
  }

  mediaAcertos->mediaV_hum /= n;
  mediaAcertos->mediaV_lin /= n;
  mediaAcertos->mediaV_mat /= n;
  mediaAcertos->mediaV_nat /= n;

  for (int i = 0; i < tamanhos.max04; i++)
  {
    desvioPadrao->desvioPadraoV_hum +=
        pow(acertos[i].v_hum - mediaAcertos->mediaV_hum, 2);
    desvioPadrao->desvioPadraoV_lin +=
        pow(acertos[i].v_lin - mediaAcertos->mediaV_lin, 2);
    desvioPadrao->desvioPadraoV_mat +=
        pow(acertos[i].v_mat - mediaAcertos->mediaV_mat, 2);
    desvioPadrao->desvioPadraoV_nat +=
        pow(acertos[i].v_nat - mediaAcertos->mediaV_nat, 2);
  }

  desvioPadrao->desvioPadraoV_hum =
      sqrt(desvioPadrao->desvioPadraoV_hum / (n - 1));
  desvioPadrao->desvioPadraoV_lin =
      sqrt(desvioPadrao->desvioPadraoV_lin / (n - 1));
  desvioPadrao->desvioPadraoV_mat =
      sqrt(desvioPadrao->desvioPadraoV_mat / (n - 1));
  desvioPadrao->desvioPadraoV_nat =
      sqrt(desvioPadrao->desvioPadraoV_nat / (n - 1));

  mediaAcertos->mediaV_hum *= 2;
  mediaAcertos->mediaV_lin *= 2;
  mediaAcertos->mediaV_mat *= 2;
  mediaAcertos->mediaV_nat *= 2;

  desvioPadrao->desvioPadraoV_hum *= 2;
  desvioPadrao->desvioPadraoV_lin *= 2;
  desvioPadrao->desvioPadraoV_mat *= 2;
  desvioPadrao->desvioPadraoV_nat *= 2;

  return;
}

void calcularPontuacao(tPontuacao *pontuacao, tAcertos *acertos,
                       tTamanhos tamanhos, tMediaAcertos *mediaAcertos,
                       tDesvioPadrao *desvioPadrao, tDados *dados,
                       tCursosEPesos *cursosEPesos)
{
  int codigoCurso;

  for (int i = 0; i < tamanhos.max04; i++)
  {
    pontuacao[i].inscricao = acertos[i].inscricao;

    pontuacao[i].pontuacaoV_lin =
        500 + 100 * (2 * acertos[i].v_lin - mediaAcertos->mediaV_lin) /
                  desvioPadrao->desvioPadraoV_lin;
    pontuacao[i].pontuacaoV_mat =
        500 + 100 * (2 * acertos[i].v_mat - mediaAcertos->mediaV_mat) /
                  desvioPadrao->desvioPadraoV_mat;
    pontuacao[i].pontuacaoV_nat =
        500 + 100 * (2 * acertos[i].v_nat - mediaAcertos->mediaV_nat) /
                  desvioPadrao->desvioPadraoV_nat;
    pontuacao[i].pontuacaoV_hum =
        500 + 100 * (2 * acertos[i].v_hum - mediaAcertos->mediaV_hum) /
                  desvioPadrao->desvioPadraoV_hum;
    pontuacao[i].red = acertos[i].red;

    for (int j = 0; j < tamanhos.max03; j++)
    {
      if (pontuacao[i].inscricao == dados[j].inscricao)
      {
        strcpy(pontuacao[i].vaga, dados[j].vaga);

        codigoCurso = dados[j].codigo;
        break;
      }
    }

    for (int k = 0; k < tamanhos.max01; k++)
    {
      if (codigoCurso == cursosEPesos[k].codigo)
      {

        pontuacao[i].notaFinal =
            ((cursosEPesos[k].red * pontuacao[i].red) +
             (cursosEPesos[k].hum * pontuacao[i].pontuacaoV_hum) +
             (cursosEPesos[k].nat * pontuacao[i].pontuacaoV_nat) +
             (cursosEPesos[k].lin * pontuacao[i].pontuacaoV_lin) +
             (cursosEPesos[k].mat * pontuacao[i].pontuacaoV_mat)) /
            (cursosEPesos[k].red + cursosEPesos[k].hum + cursosEPesos[k].nat +
             cursosEPesos[k].lin + cursosEPesos[k].mat);
        break;
      }
    }
  }

  return;
}

void alterarNotaRedacao(tTamanhos tamanhos, tAlteraRed *alteraRedacao,
                        tAcertos *acertos)
{

  for (int j = 0; j < tamanhos.max04; j++)
  {
    for (int i = 0; i < tamanhos.max05; i++)
    {
      if (acertos[j].inscricao == alteraRedacao[i].inscricao)
      {
        acertos[j].red = alteraRedacao[i].notaDepois;
        // printf("Batata %d\n", acertos[j].red);
      }
    }
  }

  return;
}

void procurarCandidato(tTamanhos tamanhos, int inscricao, tDados *dados,
                       tCursosEPesos *cursosEPesos)
{
  char nomeCandidato[MAX], nomeCurso[MAX];
  int diaInscricao, mesInscricao, anoInscricao;
  int codigoCurso;

  for (int i = 0; i < tamanhos.max03; i++)
  {
    if (dados[i].inscricao == inscricao)
    {
      strcpy(nomeCandidato, dados[i].nome);
      diaInscricao = dados[i].dia;
      mesInscricao = dados[i].mes;
      anoInscricao = dados[i].ano;
      codigoCurso = dados[i].codigo;
      break;
    }
  }

  for (int i = 0; i < tamanhos.max01; i++)
  {
    if (cursosEPesos[i].codigo == codigoCurso)
    {
      strcpy(nomeCurso, cursosEPesos[i].nome);
      break;
    }
  }

  printf("%d %s %d/%d/%d %d %s\n", inscricao, nomeCandidato, diaInscricao,
         mesInscricao, anoInscricao, codigoCurso, nomeCurso);

  return;
}