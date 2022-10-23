// Aqui vai ter muita batatinha.
#include "funcoesEntrada.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ler_e_inserir(char nomeArquivo01[MAX], char nomeArquivo02[MAX],
                   char nomeArquivo03[MAX], char nomeArquivo04[MAX],
                   tCursosEPesos *&cursosEPesos, tCursosEVagas *&cursosEVagas,
                   tDados *&dados, tAcertos *&acertos)
{

  FILE *arquivo01, *arquivo02, *arquivo03, *arquivo04;

  arquivo01 = fopen(nomeArquivo01, "r");
  arquivo02 = fopen(nomeArquivo02, "r");
  arquivo03 = fopen(nomeArquivo03, "r");
  arquivo04 = fopen(nomeArquivo04, "r");

  if (!(arquivo01 && arquivo02 && arquivo03 && arquivo04))
  {
    printf("Erro ao abrir os arquivos!");
    return;
  }
  else
  {

    int nCursos, nVagas, nDados, nAcertos, dadosCodigoCurso;
    fscanf(arquivo01, "%d", &nCursos);
    fscanf(arquivo02, "%d", &nVagas);
    fscanf(arquivo03, "%d %d", &dadosCodigoCurso, &nDados);
    fscanf(arquivo04, "%d", &nAcertos);

    // Arquivo01
    while (nCursos)
    {
      tCursosEPesos *novo, *p;

      novo = (tCursosEPesos *)malloc(sizeof(tCursosEPesos));

      fscanf(arquivo01, "%d %[^/0123456789] %d %d %d %d %d", &novo->codigo,
             novo->nome, &novo->red, &novo->mat, &novo->lin, &novo->hum,
             &novo->nat);
      novo->prox = NULL;

      if (!cursosEPesos)
      {
        cursosEPesos = novo;
      }
      else
      {
        p = cursosEPesos;

        while (p->prox != NULL)
        {
          p = p->prox;
        }

        p->prox = novo;
      }

      nCursos--;
    }

    // Arquivo02
    while (nVagas)
    {
      tCursosEVagas *novo, *p;

      novo = (tCursosEVagas *)malloc(sizeof(tCursosEVagas));

      fscanf(arquivo02, "%d %d %d %d %d %d %d %d %d %d %d %d", &novo->codigo,
             &novo->ac, &novo->l1, &novo->l3, &novo->l4, &novo->l5, &novo->l7,
             &novo->l8, &novo->l9, &novo->l11, &novo->l13, &novo->l15);

      novo->prox = NULL;

      if (!cursosEVagas)
      {
        cursosEVagas = novo;
      }
      else
      {
        p = cursosEVagas;

        while (p->prox != NULL)
        {
          p = p->prox;
        }

        p->prox = novo;
      }

      nVagas--;
    }

    // Arquivo03

    int qtdInscritos = nDados;
    while (nDados)
    {
      tDados *novo, *p;

      novo = (tDados *)malloc(sizeof(tDados));

      novo->codigo = dadosCodigoCurso;
      novo->qtdInscritos = qtdInscritos;

      fscanf(arquivo03, "%d %[^/0123456789] %d/%d/%d %s", &novo->inscricao,
             novo->nome, &novo->dia, &novo->mes, &novo->ano, novo->vaga);
      novo->prox = NULL;

      if (!dados)
      {
        dados = novo;
      }
      else
      {
        p = dados;

        while (p->prox != NULL)
        {
          p = p->prox;
        }

        p->prox = novo;
      }

      nDados--;

      if (!nDados)
      {
        fscanf(arquivo03, "%d %d", &dadosCodigoCurso, &nDados);
        qtdInscritos = nDados;
      }
    }

    // Arquivo04

    while (nAcertos)
    {
      tAcertos *novo, *p;

      novo = (tAcertos *)malloc(sizeof(tAcertos));

      fscanf(arquivo04, "%d %d %d %d %d %d", &novo->inscricao, &novo->v_lin,
             &novo->v_mat, &novo->v_nat, &novo->v_hum, &novo->red);
      novo->prox = NULL;

      if (!acertos)
      {
        acertos = novo;
      }
      else
      {
        p = acertos;

        while (p->prox != NULL)
        {
          p = p->prox;
        }

        p->prox = novo;
      }

      nAcertos--;
    }
  }

  fclose(arquivo01);
  fclose(arquivo02);
  fclose(arquivo03);
  fclose(arquivo04);
  return;
}

void calcularMediaEDesvioPadrao(tAcertos *&acertos, tMediaAcertos *mediaAcertos,
                                tDesvioPadrao *desvioPadrao)
{

  tAcertos *p;
  int n = 0;

  for (p = acertos; p != NULL; p = p->prox)
  {

    mediaAcertos->mediaV_hum += p->v_hum;
    mediaAcertos->mediaV_lin += p->v_lin;
    mediaAcertos->mediaV_mat += p->v_mat;
    mediaAcertos->mediaV_nat += p->v_nat;
    n++;
  }

  mediaAcertos->mediaV_hum /= n;
  mediaAcertos->mediaV_lin /= n;
  mediaAcertos->mediaV_mat /= n;
  mediaAcertos->mediaV_nat /= n;

  for (p = acertos; p != NULL; p = p->prox)
  {

    desvioPadrao->desvioPadraoV_hum +=
        pow(p->v_hum - mediaAcertos->mediaV_hum, 2);
    desvioPadrao->desvioPadraoV_lin +=
        pow(p->v_lin - mediaAcertos->mediaV_lin, 2);
    desvioPadrao->desvioPadraoV_mat +=
        pow(p->v_mat - mediaAcertos->mediaV_mat, 2);
    desvioPadrao->desvioPadraoV_nat +=
        pow(p->v_nat - mediaAcertos->mediaV_nat, 2);
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

void calcularPontuacao(tPontuacao *&pontuacao, tAcertos *&acertos,
                       tMediaAcertos *mediaAcertos, tDesvioPadrao *desvioPadrao,
                       tDados *&dados, tCursosEPesos *&cursosEPesos)
{
  int codigoCurso;
  tPontuacao *novo, *p;
  tAcertos *q;
  tDados *j;
  tCursosEPesos *k;

  for (q = acertos; q != NULL; q = q->prox)
  {

    novo = (tPontuacao *)malloc(sizeof(tPontuacao));
    novo->inscricao = q->inscricao;

    novo->pontuacaoV_lin = 500 + 100 *
                                     (2 * q->v_lin - mediaAcertos->mediaV_lin) /
                                     desvioPadrao->desvioPadraoV_lin;
    novo->pontuacaoV_mat = 500 + 100 *
                                     (2 * q->v_mat - mediaAcertos->mediaV_mat) /
                                     desvioPadrao->desvioPadraoV_mat;
    novo->pontuacaoV_nat = 500 + 100 *
                                     (2 * q->v_nat - mediaAcertos->mediaV_nat) /
                                     desvioPadrao->desvioPadraoV_nat;
    novo->pontuacaoV_hum = 500 + 100 *
                                     (2 * q->v_hum - mediaAcertos->mediaV_hum) /
                                     desvioPadrao->desvioPadraoV_hum;
    novo->red = q->red;
    novo->prox = NULL;

    for (j = dados; j != NULL; j = j->prox)
    {
      if (novo->inscricao == j->inscricao)
      {
        strcpy(novo->vaga, j->vaga);
        codigoCurso = j->codigo;
        break;
      }
    }

    for (k = cursosEPesos; k != NULL; k = k->prox)
    {
      if (codigoCurso == k->codigo)
      {
        novo->notaFinal =
            ((k->red * novo->red) + (k->hum * novo->pontuacaoV_hum) +
            (k->nat * novo->pontuacaoV_nat) + (k->lin * novo->pontuacaoV_lin) +
             (k->mat * novo->pontuacaoV_mat)) /
                (k->red + k->hum + k->nat + k->lin + k->mat);
        break;
      }
    }

    if (!pontuacao)
    {
      pontuacao = novo;
    }
    else
    {
      p = pontuacao;

      while (p->prox != NULL)
      {
        p = p->prox;
      }

      p->prox = novo;
    }
  }

  return;
}
