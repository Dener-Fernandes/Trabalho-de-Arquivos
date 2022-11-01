#include "funcoesEntrada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ordem de inserção dos arquivos: cursos_e_pesos.,
// cursos_e_vagas.txt, dados.txt e acertos.txt

/*void imprimir(tPontuacao *lst) {
  tPontuacao *p;
  for (p = lst; p != NULL; p = p->prox) 
  {   
    printf("%d %.3f %.3f %.3f %.3f %d %s %.3f\n", p->inscricao,
           p->pontuacaoV_lin, p->pontuacaoV_mat, p->pontuacaoV_nat,
           p->pontuacaoV_hum, p->red, p->vaga, p->notaFinal);
  }

  return;
} */

void imprimir(tPontuacao *lst)
{
  tPontuacao *p;
  for (p = lst; p != NULL; p = p->prox)
  {
    if (p->inscricao == 548349)
    {
      printf("%d %.3f %.3f %.3f %.3f %d %s %.3f\n", p->inscricao,
             p->pontuacaoV_lin, p->pontuacaoV_mat, p->pontuacaoV_nat,
             p->pontuacaoV_hum, p->red, p->vaga, p->notaFinal);
      break;
    }
  }

  return;
}

int main() {
  int op = -1; // variável de controle do menu
  tCursosEPesos *cursosEPesos = NULL;
  tCursosEVagas *cursosEVagas = NULL;
  tDados *dados = NULL;
  tAcertos *acertos = NULL;
  tPontuacao *pontuacao = NULL;
  tMediaAcertos mediaAcertos = {0.0};
  tDesvioPadrao desvioPadrao = {0.0};
  tAlteraRed* AlteraRed = NULL;
  
  int pesqCand = 0; // para função pesquisar candidato do menu

  // Variável que irá manipular o arquivo.
  FILE *arquivo;
  char nome01[MAX], nome02[MAX], nome03[MAX], nome04[MAX], nome05[MAX];
  int tamanhoArquivo;
  char cursoNome[MAX];

  menu0();
  scanf("%d", &op);
  while(op != 0)
  {
      menu0();
      scanf("%d", &op);
     printf("Para executar as funções você precisa ler os arquivos!");
  }
  while(op != 5)
{
    menu1();
    scanf("%d", &op);
    // Lendo os arquivos, pois a função não seria executada no outro while
    strcpy(nome01, "cursos_e_pesos.txt");
    strcpy(nome02, "cursos_e_vagas.txt");
    strcpy(nome03, "dados.txt");
    strcpy(nome04, "acertos.txt");

    ler_e_inserir(nome01, nome02, nome03, nome04, cursosEPesos, cursosEVagas,
                    dados, acertos);
    if (op == 2){
    printf("\nDigite a inscrição do aluno que deseja procurar: ");
    scanf("%d", &pesqCand);
    pesquisaCand(dados, pesqCand, cursosEPesos);
  
    }
    if(op == 3){
  calcularMediaEDesvioPadrao(acertos, &mediaAcertos, &desvioPadrao);
   calcularPontuacao(pontuacao, acertos, &mediaAcertos, &desvioPadrao, dados, cursosEPesos);
    imprimir(pontuacao);
    }

    if (op == 4){
    strcpy(nome05, "alteraNotaRedacao.txt");
    LeArqRed(nome05, AlteraRed);
    AlteraReda(AlteraRed, acertos);
    }
    
}

 // calcularMediaEDesvioPadrao(acertos, &mediaAcertos, &desvioPadrao);
 // calcularPontuacao(pontuacao, acertos, &mediaAcertos, &desvioPadrao, dados,
                   // cursosEPesos);

  
  //imprimir(pontuacao);
  desalocarCursosEPesos(cursosEPesos);
  desalocarCursosEVagas(cursosEVagas);
  desalocarDados(dados);
  desalocarAcertos(acertos);

  return 0;
}