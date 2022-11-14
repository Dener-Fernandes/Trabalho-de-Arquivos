#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

  tArquivos arquivosNomes;
  FILE *arquivo01, *arquivo02, *arquivo03, *arquivo04, *arquivo05;
  tTamanhos tamanhos;
  int op = -1; // variável do menu

  menu0();
  scanf("%d", &op);
  while (op != 0)
  {
    menu0();
    scanf("%d", &op);
  }

  strcpy(arquivosNomes.nome01, "cursos_e_pesos.txt");
  strcpy(arquivosNomes.nome02, "cursos_e_vagas.txt");
  strcpy(arquivosNomes.nome03, "dados.txt");
  strcpy(arquivosNomes.nome04, "acertos.txt");
  strcpy(arquivosNomes.nome05, "alteracaoNotaRedacao.txt");

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
  // calculaIdade(dados, tamanhos);
  ordenaPont(pontuacao, dados, tamanhos, cursosEPesos);
  ordenarCursos(cursosEPesos, tamanhos);
  tamanhos.max06 =
      pegarTamanhoAprovados(pontuacao, cursosEPesos, cursosEVagas, tamanhos);

  tAprovados *aprovados =
      (tAprovados *)calloc(tamanhos.max06, sizeof(tAprovados));

  while (op != 5)
  {
    menu1();
    scanf("%d", &op);

    if (op == 1)
    {

      criarArquivoSaida01(pontuacao, cursosEPesos, cursosEVagas, tamanhos);
      criarListaAprovados(pontuacao, cursosEPesos, cursosEVagas, dados,
                          tamanhos, aprovados);
      /*for (int i = 0; i < tamanhos.max06; i++) {
        printf("%d %s %d\n", aprovados[i].inscricao, aprovados[i].nome,
               aprovados[i].codigoCurso);
      }*/
    }

    if (op == 2)
    {
      int inscricao;
      printf("\nDigite a inscricao do aluno que deseja procurar: ");
      scanf("%d", &inscricao);
      procurarCandidato(tamanhos, inscricao, dados, cursosEPesos);
    }
    if (op == 3)
    {
      if (!aprovados[0].classificacao)
      {
        criarListaAprovados(pontuacao, cursosEPesos, cursosEVagas, dados,
                            tamanhos, aprovados);
        criarArquivo02(pontuacao, cursosEPesos, dados, tamanhos, aprovados);
      }
      else
      {
        criarArquivo02(pontuacao, cursosEPesos, dados, tamanhos, aprovados);
      }
    }

    if (op == 4)
    {
      alterarNotaRedacao(tamanhos, alteraRedacao, acertos);

      calcularPontuacao(pontuacao, acertos, tamanhos, &mediaAcertos,
                        &desvioPadrao, dados, cursosEPesos);
    }
  }

  return 0;
}