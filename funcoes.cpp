#include "funcoes.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pegarTamanhoArquivoDados(tArquivos arquivosNomes, tTamanhos tamanhos) {
  int codigoCurso, i = 0;
  FILE *arquivo03;

  arquivo03 = fopen(arquivosNomes.nome03, "r");

  if (!arquivo03) {
    printf("Erro ao abrir o arquivo dados.txt");
    return 0;
  } else {
    int x = fscanf(arquivo03, "%d %d", &codigoCurso, &tamanhos.max03);

    while (tamanhos.max03) {
      int dados;
      char dadosNome[MAX];
      int x = fscanf(arquivo03, "%d %[^/0123456789] %d/%d/%d %s", &dados,
                     dadosNome, &dados, &dados, &dados, dadosNome);

      i++;
      tamanhos.max03--;

      if (!tamanhos.max03) {
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
                  tDados *dados, tAcertos *acertos, tAlteraRed *alteraRedacao) {

  FILE *arquivo01, *arquivo02, *arquivo03, *arquivo04, *arquivo05;

  int codigoCurso, i = 0;

  arquivo01 = fopen(arquivosNomes.nome01, "r");
  arquivo02 = fopen(arquivosNomes.nome02, "r");
  arquivo03 = fopen(arquivosNomes.nome03, "r");
  arquivo04 = fopen(arquivosNomes.nome04, "r");
  arquivo05 = fopen(arquivosNomes.nome05, "r");

  if (!(arquivo01 && arquivo02 && arquivo03 && arquivo04 && arquivo05)) {
    printf("Erro ao abrir os arquivos!");
    return 0;
  } else {

    int x = fscanf(arquivo01, "%d", &tamanhos.max01);
    int y = fscanf(arquivo02, "%d", &tamanhos.max02);
    int z = fscanf(arquivo03, "%d %d", &codigoCurso, &tamanhos.max03);
    int a = fscanf(arquivo04, "%d", &tamanhos.max04);
    int b = fscanf(arquivo05, "%d", &tamanhos.max05);

    for (int i = 0; i < tamanhos.max01; i++) {
      int x = fscanf(arquivo01, "%d %[^/0123456789] %d %d %d %d %d",
                     &cursosEPesos[i].codigo, cursosEPesos[i].nome,
                     &cursosEPesos[i].red, &cursosEPesos[i].mat,
                     &cursosEPesos[i].lin, &cursosEPesos[i].hum,
                     &cursosEPesos[i].nat);
    }

    for (int i = 0; i < tamanhos.max02; i++) {
      int x = fscanf(
          arquivo02, "%d %d %d %d %d %d %d %d %d %d %d %d",
          &cursosEVagas[i].codigo, &cursosEVagas[i].ac, &cursosEVagas[i].l1,
          &cursosEVagas[i].l3, &cursosEVagas[i].l4, &cursosEVagas[i].l5,
          &cursosEVagas[i].l7, &cursosEVagas[i].l8, &cursosEVagas[i].l9,
          &cursosEVagas[i].l11, &cursosEVagas[i].l13, &cursosEVagas[i].l15);
    }

    int qtdInscritos = tamanhos.max03;

    while (tamanhos.max03) {

      dados[i].codigo = codigoCurso;

      int x = fscanf(arquivo03, "%d %[^/0123456789] %d/%d/%d %s",
                     &dados[i].inscricao, dados[i].nome, &dados[i].dia,
                     &dados[i].mes, &dados[i].ano, dados[i].vaga);

      i++;
      tamanhos.max03--;

      if (!tamanhos.max03) {
        int x = fscanf(arquivo03, "%d %d", &codigoCurso, &tamanhos.max03);
        qtdInscritos = tamanhos.max03;
      }
    }

    for (int i = 0; i < tamanhos.max04; i++) {
      int x = fscanf(arquivo04, "%d %d %d %d %d %d", &acertos[i].inscricao,
                     &acertos[i].v_lin, &acertos[i].v_mat, &acertos[i].v_nat,
                     &acertos[i].v_hum, &acertos[i].red);
    }

    for (int i = 0; i < tamanhos.max05; i++) {
      fscanf(arquivo05, "%d %d %d", &alteraRedacao[i].inscricao,
             &alteraRedacao[i].notaAntes, &alteraRedacao[i].notaDepois);
    }
  }

  return 0;
}

void calcularMediaEDesvioPadrao(tAcertos acertos[MAX04],
                                tMediaAcertos *mediaAcertos, tTamanhos tamanhos,
                                tDesvioPadrao *desvioPadrao) {

  int n = 0;
  for (int i = 0; i < tamanhos.max04; i++) {
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

  for (int i = 0; i < tamanhos.max04; i++) {
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
                       tCursosEPesos *cursosEPesos) {
  int codigoCurso;

  for (int i = 0; i < tamanhos.max04; i++) {
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

    for (int j = 0; j < tamanhos.max03; j++) {
      if (pontuacao[i].inscricao == dados[j].inscricao) {
        strcpy(pontuacao[i].vaga, dados[j].vaga);

        codigoCurso = dados[j].codigo;
        break;
      }
    }

    for (int k = 0; k < tamanhos.max01; k++) {
      if (codigoCurso == cursosEPesos[k].codigo) {

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
                        tAcertos *acertos) {

  for (int j = 0; j < tamanhos.max04; j++) {
    for (int i = 0; i < tamanhos.max05; i++) {
      if (acertos[j].inscricao == alteraRedacao[i].inscricao) {
        acertos[j].red = alteraRedacao[i].notaDepois;
        // printf("Batata %d\n", acertos[j].red);
      }
    }
  }

  return;
}

void procurarCandidato(tTamanhos tamanhos, int inscricao, tDados *dados,
                       tCursosEPesos *cursosEPesos) {
  char nomeCandidato[MAX], nomeCurso[MAX];
  int diaInscricao, mesInscricao, anoInscricao;
  int codigoCurso;
  int flag = 0;

  for (int i = 0; i < tamanhos.max03; i++) {
    if (dados[i].inscricao == inscricao) {
      strcpy(nomeCandidato, dados[i].nome);
      diaInscricao = dados[i].dia;
      mesInscricao = dados[i].mes;
      anoInscricao = dados[i].ano;
      codigoCurso = dados[i].codigo;
      flag = 1;
      break;
    }
  }
  if (flag == 0) {
    printf("Aluno não encontrado\n");
    return;
  }

  for (int i = 0; i < tamanhos.max01; i++) {
    if (cursosEPesos[i].codigo == codigoCurso) {
      strcpy(nomeCurso, cursosEPesos[i].nome);
      break;
    }
  }

  printf("%d %s %d/%d/%d %d %s\n", inscricao, nomeCandidato, diaInscricao,
         mesInscricao, anoInscricao, codigoCurso, nomeCurso);

  return;
}

void menu0() {
  printf("*********** MENU ***********");
  printf("\n0 - Ler arquivos de entrada");
  printf("\n1 - Gerar arquivo de saída.txt");
  printf("\n2 - Pesquisar candidatos");
  printf("\n3 - Gerar arquivos dos candidatos não aprovados");
  printf("\n4 - Alterar nota dos candidatos que entraram com recurso");
  printf("\n5 - Encerrar programa\n");
}

void menu1() {
  printf("*********** MENU ***********");
  printf("\n1 - Gerar arquivo de saída.txt");
  printf("\n2 - Pesquisar candidatos");
  printf("\n3 - Gerar arquivos dos candidatos não aprovados");
  printf("\n4 - Alterar nota dos candidatos que entraram com recurso");
  printf("\n5 - Encerrar programa\n");
}

void imprimirPontuacao(tTamanhos tamanhos, tPontuacao *lst) {

  tPontuacao *pontuacao = lst;
  for (int i = 0; i < tamanhos.max04; i++) {

    printf("%d %.3f %.3f %.3f %.3f %d %s %.3f\n", pontuacao[i].inscricao,
           pontuacao[i].pontuacaoV_lin, pontuacao[i].pontuacaoV_mat,
           pontuacao[i].pontuacaoV_nat, pontuacao[i].pontuacaoV_hum,
           pontuacao[i].red, pontuacao[i].vaga, pontuacao[i].notaFinal);
  }
}

void ordenaAlfabetica(tTamanhos tamanhos, tCursosEPesos *lst) {
  tCursosEPesos *i = lst;
  char aux[MAX];
  for (int j = 1; j < tamanhos.max01; j++) {
    for (int k = 0; k < tamanhos.max01 - j; k++) {
      if (strcmp(i[k].nome, i[j].nome) > 0) {
        strcpy(aux, i[k].nome);
        strcpy(i[k].nome, i[j].nome);
        strcpy(i[j].nome, aux);
      }
    }
  }
}

void imprimirNome(tTamanhos tamanhos, tCursosEPesos *lst) {
  tCursosEPesos *i = lst;
  for (int j = 0; j < tamanhos.max01; j++) {
    printf(" %s\n", i[j].nome);
  }
}

void calculaIdade(tDados *lst, tTamanhos tamanhos) {

  for (int i = 0; i < tamanhos.max03; i++) {
    lst[i].idade = (lst[i].ano * 365) + (lst[i].mes * 30) + lst[i].dia;
  }
  return;
}

void trocaPont(tPontuacao *a, tPontuacao *b) {
  tPontuacao *aux;
  aux = a;
  a = b;
  b = aux;
}

void bubblePont(tTamanhos tamanhos, tPontuacao *lst, tDados *x) {
  tPontuacao *v = lst;
  tDados *vDados = x;
  for (int i = 1; i < tamanhos.max04; i++) {
    for (int j = 0; j < tamanhos.max04 - i; j++) {
      if (v[j].notaFinal < v[j + 1].notaFinal)
        trocaPont(&v[j], &v[j + 1]);
    }
  }
  for (int i = 1; i < tamanhos.max04; i++) {
    for (int j = 0; j < tamanhos.max04 - i; j++) {
      if (v[j].notaFinal == v[j + 1].notaFinal &&
          vDados[j + 1].idade >= 21900 && vDados[j].idade < vDados[j + 1].idade)
        trocaPont(&v[j], &v[j + 1]);
    }
  }

  for (int i = 1; i < tamanhos.max04; i++) {
    for (int j = 0; j < tamanhos.max04 - i; j++) {
      if (v[j].notaFinal == v[j + 1].notaFinal && v[j].red < v[j + 1].red)
        trocaPont(&v[j], &v[j + 1]);
    }
  }
  for (int i = 1; i < tamanhos.max04; i++) {
    for (int j = 0; j < tamanhos.max04 - i; j++) {
      if (v[j].notaFinal == v[j + 1].notaFinal &&
          v[j].pontuacaoV_lin < v[j + 1].pontuacaoV_lin)
        trocaPont(&v[j], &v[j + 1]);
    }
  }
  for (int i = 1; i < tamanhos.max04; i++) {
    for (int j = 0; j < tamanhos.max04 - i; j++) {
      if (v[j].notaFinal == v[j + 1].notaFinal &&
          v[j].pontuacaoV_mat < v[j + 1].pontuacaoV_mat)
        trocaPont(&v[j], &v[j + 1]);
    }
  }
  for (int i = 1; i < tamanhos.max04; i++) {
    for (int j = 0; j < tamanhos.max04 - i; j++) {
      if (v[j].notaFinal == v[j + 1].notaFinal &&
          v[j].pontuacaoV_hum < v[j + 1].pontuacaoV_hum)
        trocaPont(&v[j], &v[j + 1]);
    }
  }
  for (int i = 1; i < tamanhos.max04; i++) {
    for (int j = 0; j < tamanhos.max04 - i; j++) {
      if (v[j].notaFinal == v[j + 1].notaFinal &&
          v[j].pontuacaoV_nat < v[j + 1].pontuacaoV_nat)
        trocaPont(&v[j], &v[j + 1]);
    }
  }
}

void ordenaPont(tPontuacao *lst, tDados *x, tTamanhos tamanhos,
                tCursosEPesos *k) {
  tPontuacao *a = lst;
  tDados *b = x;
  tCursosEPesos *c = k;
  int idade = 0;

  for (int i = 0; i < tamanhos.max01; i++) {
    for (int j = 0; j < tamanhos.max03; j++) {
      if (x[j].codigo == k[i].codigo && k[i].codigo == 465) {
        if (strcmp(x[j].vaga, "AC") == 0) {
          bubblePont(tamanhos, lst, x);
        } else if (strcmp(x[j].vaga, "L1") == 0) {
          bubblePont(tamanhos, lst, x);
        } else if (strcmp(x[j].vaga, "L3") == 0) {
          bubblePont(tamanhos, lst, x);
        } else if (strcmp(x[j].vaga, "L4") == 0) {
          bubblePont(tamanhos, lst, x);
        } else if (strcmp(x[j].vaga, "L5") == 0) {
          bubblePont(tamanhos, lst, x);
        } else if (strcmp(x[j].vaga, "L7") == 0) {
          bubblePont(tamanhos, lst, x);
        } else if (strcmp(x[j].vaga, "L8") == 0) {
          bubblePont(tamanhos, lst, x);
        } else if (strcmp(x[j].vaga, "L9") == 0) {
          bubblePont(tamanhos, lst, x);
        } else if (strcmp(x[j].vaga, "L11") == 0) {
          bubblePont(tamanhos, lst, x);
        } else if (strcmp(x[j].vaga, "L13") == 0) {
          bubblePont(tamanhos, lst, x);
        } else if (strcmp(x[j].vaga, "L15") == 0) {
          bubblePont(tamanhos, lst, x);
        }
      }
    }
  }
}

