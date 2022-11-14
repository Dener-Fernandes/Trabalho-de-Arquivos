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

    pontuacao[i].codigoCurso = codigoCurso;

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

void imprimirPontuacao(tTamanhos tamanhos, tPontuacao *pontuacao) {

  for (int i = 0; i < tamanhos.max04; i++) {

    printf("%d %.2f %.2f %.2f %.2f %d %s %.2f\n", pontuacao[i].inscricao,
           pontuacao[i].pontuacaoV_lin, pontuacao[i].pontuacaoV_mat,
           pontuacao[i].pontuacaoV_nat, pontuacao[i].pontuacaoV_hum,
           pontuacao[i].red, pontuacao[i].vaga, pontuacao[i].notaFinal);
  }
}

void ordenaAlfabetica(tTamanhos tamanhos, tCursosEPesos *cursosEPesos) {
  char aux[MAX];
  for (int j = 1; j < tamanhos.max01; j++) {
    for (int k = 0; k < tamanhos.max01 - j; k++) {
      if (strcmp(cursosEPesos[k].nome, cursosEPesos[j].nome) > 0) {
        strcpy(aux, cursosEPesos[k].nome);
        strcpy(cursosEPesos[k].nome, cursosEPesos[j].nome);
        strcpy(cursosEPesos[j].nome, aux);
      }
    }
  }
}

void imprimirNome(tTamanhos tamanhos, tCursosEPesos *cursosEPesos) {
  for (int j = 0; j < tamanhos.max01; j++) {
    printf(" %s\n", cursosEPesos[j].nome);
  }
}

void calculaIdade(tDados *dados, tTamanhos tamanhos) {

  for (int i = 0; i < tamanhos.max03; i++) {
    dados[i].idade = (dados[i].ano * 365) + (dados[i].mes * 30) + dados[i].dia;
  }
  return;
}

void bubblePont(tTamanhos tamanhos, tPontuacao *&pontuacao, tDados *&dados) {
  for (int i = 1; i < tamanhos.max04; i++) {
    for (int j = 0; j < tamanhos.max04 - i; j++) {
      if (pontuacao[j].notaFinal < pontuacao[j + 1].notaFinal) {
        tPontuacao aux = pontuacao[j];
        pontuacao[j] = pontuacao[j + 1];
        pontuacao[j + 1] = aux;
      }
    }
  }
}

void ordenaPont(tPontuacao *pontuacao, tDados *dados, tTamanhos tamanhos,
                tCursosEPesos *cursosEPesos) {

  for (int i = 0; i < tamanhos.max01; i++) {
    for (int j = 0; j < tamanhos.max03; j++) {
      if (dados[j].codigo == cursosEPesos[i].codigo) {
        if (strcmp(dados[j].vaga, "AC") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        } else if (strcmp(dados[j].vaga, "L1") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        } else if (strcmp(dados[j].vaga, "L3") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        } else if (strcmp(dados[j].vaga, "L4") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        } else if (strcmp(dados[j].vaga, "L5") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        } else if (strcmp(dados[j].vaga, "L7") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        } else if (strcmp(dados[j].vaga, "L8") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        } else if (strcmp(dados[j].vaga, "L9") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        } else if (strcmp(dados[j].vaga, "L11") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        } else if (strcmp(dados[j].vaga, "L13") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        } else if (strcmp(dados[j].vaga, "L15") == 0) {
          bubblePont(tamanhos, pontuacao, dados);
        }
      }
    }
  }
}

void ordenarCursos(tCursosEPesos *cursosEPesos, tTamanhos tamanhos) {
  for (int i = 1; i < tamanhos.max01; i++) {
    for (int j = 0; j < tamanhos.max01 - i; j++) {
      if (cursosEPesos[j].codigo > cursosEPesos[j + 1].codigo) {
        tCursosEPesos aux;
        aux = cursosEPesos[j];
        cursosEPesos[j] = cursosEPesos[j + 1];
        cursosEPesos[j + 1] = aux;
      }
    }
  }

  return;
}

void criarArquivoSaida01(tPontuacao *pontuacao, tCursosEPesos *cursosEPesos,
                         tCursosEVagas *cursosEVagas, tTamanhos tamanhos) {
  FILE *saida1 = fopen("saida1.txt", "a");
  fprintf(saida1, "/*LISTA GERAL CLASSIFICADO POR NOTA*/\n");

  for (int i = 0; i < tamanhos.max01; i++) {
    tCursosEPesos curso = cursosEPesos[i];

    fprintf(saida1, "%d %s\n", curso.codigo, curso.nome);

    tCursosEVagas cursoEVaga;

    for (int j = 0; j < tamanhos.max02; j++) {
      if (curso.codigo == cursosEVagas[j].codigo) {
        cursoEVaga = cursosEVagas[i];
        break;
      }
    }

    int countAc = 0, countL1 = 0, countL3 = 0, countL4 = 0, countL5 = 0,
        countL7 = 0, countL8 = 0, countL9 = 0, countL11 = 0, countL13 = 0,
        countL15 = 0;

    fprintf(saida1,
            "INSC	   V_LIN	V_MAT	V_NAT	V_HUM	   RED COTA "
            "NOTA FINAL	CLASSIFICAÇÃO\n");

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countAc < (cursoEVaga.ac) && !(strcmp(pontuacao[a].vaga, "AC"))) {
        countAc++;

        fprintf(saida1,
                "%d	 %.2f	%.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countAc);
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {
      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL1 < (cursoEVaga.l1) && !(strcmp(pontuacao[a].vaga, "L1"))) {
        countL1++;

        fprintf(saida1, "%d  %.2f %.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countL1);
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {
      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL3 < (cursoEVaga.l3) && !(strcmp(pontuacao[a].vaga, "L3"))) {
        countL3++;

        fprintf(saida1, "%d  %.2f %.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countL3);
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL4 < (cursoEVaga.l4) && !(strcmp(pontuacao[a].vaga, "L4"))) {
        countL4++;

        fprintf(saida1, "%d  %.2f %.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countL4);
      }
    }
    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL5 < (cursoEVaga.l5) && !(strcmp(pontuacao[a].vaga, "L5"))) {
        countL5++;

        fprintf(saida1, "%d  %.2f %.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countL5);
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL7 < (cursoEVaga.l7) && !(strcmp(pontuacao[a].vaga, "L7"))) {
        countL7++;

        fprintf(saida1, "%d  %.2f %.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countL7);
      }
    }
    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL8 < (cursoEVaga.l8) && !(strcmp(pontuacao[a].vaga, "L8"))) {
        countL8++;

        fprintf(saida1, "%d  %.2f %.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countL8);
      }
    }
    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL9 < (cursoEVaga.l9) && !(strcmp(pontuacao[a].vaga, "L9"))) {
        countL9++;

        fprintf(saida1, "%d  %.2f %.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countL9);
      }
    }
    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL11 < (cursoEVaga.l11) && !(strcmp(pontuacao[a].vaga, "L11"))) {
        countL11++;

        fprintf(saida1, "%d  %.2f %.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countL11);
      }
    }
    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL13 < (cursoEVaga.l13) && !(strcmp(pontuacao[a].vaga, "L13"))) {
        countL13++;

        fprintf(saida1, "%d  %.2f %.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countL13);
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL15 < (cursoEVaga.l15) && !(strcmp(pontuacao[a].vaga, "L15"))) {
        countL15++;

        fprintf(saida1, "%d  %.2f %.2f %.2f %.2f %d %s %.2f             %d\n",
                pontuacao[a].inscricao, pontuacao[a].pontuacaoV_lin,
                pontuacao[a].pontuacaoV_mat, pontuacao[a].pontuacaoV_nat,
                pontuacao[a].pontuacaoV_hum, pontuacao[a].red,
                pontuacao[a].vaga, pontuacao[a].notaFinal, countL15);
      }
    }
    fprintf(saida1, "\n");
  }

  fclose(saida1);
  return;
}

int pegarTamanhoAprovados(tPontuacao *pontuacao, tCursosEPesos *cursosEPesos,
                          tCursosEVagas *cursosEVagas, tTamanhos tamanhos) {

  int totalAprovados = 0;

  for (int i = 0; i < tamanhos.max01; i++) {
    tCursosEPesos curso = cursosEPesos[i];

    tCursosEVagas cursoEVaga;

    for (int j = 0; j < tamanhos.max02; j++) {
      if (curso.codigo == cursosEVagas[j].codigo) {
        cursoEVaga = cursosEVagas[i];
        break;
      }
    }

    int countAc = 0, countL1 = 0, countL3 = 0, countL4 = 0, countL5 = 0,
        countL7 = 0, countL8 = 0, countL9 = 0, countL11 = 0, countL13 = 0,
        countL15 = 0;

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countAc < (cursoEVaga.ac) && !(strcmp(pontuacao[a].vaga, "AC"))) {
        countAc++;
        totalAprovados++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {
      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL1 < (cursoEVaga.l1) && !(strcmp(pontuacao[a].vaga, "L1"))) {
        countL1++;
        totalAprovados++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {
      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL3 < (cursoEVaga.l3) && !(strcmp(pontuacao[a].vaga, "L3"))) {
        countL3++;
        totalAprovados++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL4 < (cursoEVaga.l4) && !(strcmp(pontuacao[a].vaga, "L4"))) {
        countL4++;
        totalAprovados++;
      }
    }
    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL5 < (cursoEVaga.l5) && !(strcmp(pontuacao[a].vaga, "L5"))) {
        countL5++;
        totalAprovados++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL7 < (cursoEVaga.l7) && !(strcmp(pontuacao[a].vaga, "L7"))) {
        countL7++;
        totalAprovados++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL8 < (cursoEVaga.l8) && !(strcmp(pontuacao[a].vaga, "L8"))) {
        countL8++;
        totalAprovados++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL9 < (cursoEVaga.l9) && !(strcmp(pontuacao[a].vaga, "L9"))) {
        countL9++;
        totalAprovados++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL11 < (cursoEVaga.l11) && !(strcmp(pontuacao[a].vaga, "L11"))) {
        countL11++;
        totalAprovados++;
      }
    }
    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL13 < (cursoEVaga.l13) && !(strcmp(pontuacao[a].vaga, "L13"))) {
        countL13++;
        totalAprovados++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL15 < (cursoEVaga.l15) && !(strcmp(pontuacao[a].vaga, "L15"))) {
        countL15++;
        totalAprovados++;
      }
    }
  }

  return totalAprovados;
}

void criarListaAprovados(tPontuacao *pontuacao, tCursosEPesos *cursosEPesos,
                         tCursosEVagas *cursosEVagas, tDados *dados,
                         tTamanhos tamanhos, tAprovados *aprovados) {
  int index = 0;

  for (int i = 0; i < tamanhos.max01; i++) {
    tCursosEPesos curso = cursosEPesos[i];

    tCursosEVagas cursoEVaga;

    for (int j = 0; j < tamanhos.max02; j++) {
      if (curso.codigo == cursosEVagas[j].codigo) {
        cursoEVaga = cursosEVagas[i];
        break;
      }
    }

    int countAc = 0, countL1 = 0, countL3 = 0, countL4 = 0, countL5 = 0,
        countL7 = 0, countL8 = 0, countL9 = 0, countL11 = 0, countL13 = 0,
        countL15 = 0;

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countAc < (cursoEVaga.ac) && !(strcmp(pontuacao[a].vaga, "AC"))) {
        countAc++;
        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countAc;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }

        index++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {
      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL1 < (cursoEVaga.l1) && !(strcmp(pontuacao[a].vaga, "L1"))) {
        countL1++;

        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countL1;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }

        index++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {
      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL3 < (cursoEVaga.l3) && !(strcmp(pontuacao[a].vaga, "L3"))) {
        countL3++;

        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countL3;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }

        index++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL4 < (cursoEVaga.l4) && !(strcmp(pontuacao[a].vaga, "L4"))) {
        countL4++;
        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countL4;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }

        index++;
      }
    }
    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL5 < (cursoEVaga.l5) && !(strcmp(pontuacao[a].vaga, "L5"))) {
        countL5++;
        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countL5;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }

        index++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL7 < (cursoEVaga.l7) && !(strcmp(pontuacao[a].vaga, "L7"))) {
        countL7++;
        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countL7;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }

        index++;
      }
    }
    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL8 < (cursoEVaga.l8) && !(strcmp(pontuacao[a].vaga, "L8"))) {
        countL8++;
        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countL8;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }
        index++;
      }
    }
    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL9 < (cursoEVaga.l9) && !(strcmp(pontuacao[a].vaga, "L9"))) {
        countL9++;
        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countL9;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }

        index++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL11 < (cursoEVaga.l11) && !(strcmp(pontuacao[a].vaga, "L11"))) {
        countL11++;
        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countL11;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }

        index++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL13 < (cursoEVaga.l13) && !(strcmp(pontuacao[a].vaga, "L13"))) {
        countL13++;
        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countL13;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }

        index++;
      }
    }

    for (int a = 0; a < tamanhos.max04; a++) {

      if (pontuacao[a].codigoCurso == curso.codigo &&
          countL15 < (cursoEVaga.l15) && !(strcmp(pontuacao[a].vaga, "L15"))) {
        countL15++;
        aprovados[index].codigoCurso = pontuacao[a].codigoCurso;
        aprovados[index].inscricao = pontuacao[a].inscricao;
        aprovados[index].classificacao = countL15;
        strcpy(aprovados[index].vaga, pontuacao[a].vaga);

        for (int c = 0; c < tamanhos.max03; c++) {
          if (dados[c].inscricao == pontuacao[a].inscricao) {
            strcpy(aprovados[index].nome, dados[c].nome);
          }
        }

        index++;
      }
    }
  }
  return;
}

void criarArquivo02(tPontuacao *pontuacao, tCursosEPesos *cursosEPesos,
                    tDados *dados, tTamanhos tamanhos, tAprovados *aprovados) {
  int index = 0;

  FILE *saida02 = fopen("saida2.txt", "a");

  fprintf(saida02, ".+*******+.NAO APROVADOS.+*******+.\n");

  for (int i = 0; i < tamanhos.max01; i++) {
    tCursosEPesos curso = cursosEPesos[i];

    fprintf(saida02, "%d %s\n", curso.codigo, curso.nome);

    for (int j = 0; j < tamanhos.max04; j++) {
      bool flag = true;
      for (int k = 0; k < tamanhos.max06; k++) {
        if (pontuacao[j].inscricao == aprovados[k].inscricao) {
          flag = false;
        }
      }

      if (flag && pontuacao[j].codigoCurso == curso.codigo) {
        char nome[80];

        for (int a = 0; a < tamanhos.max03; a++) {
          if (pontuacao[j].inscricao == dados[a].inscricao) {
            strcpy(nome, dados[a].nome);
          }
        }
        fprintf(saida02, "%d %s\n", pontuacao[j].inscricao, nome);
      }
    }

    fprintf(saida02, "\n");
  }

  fclose(saida02);
  return;
}
