// Aqui vai ter muita batatinha.
#include "estruturas.h"


void ler_e_inserir(char nomeArquivo01[MAX], char nomeArquivo02[MAX],
                   char nomeArquivo03[MAX], char nomeArquivo04[MAX],
                   tCursosEPesos *&cursosEPesos, tCursosEVagas *&cursosEVagas,
                   tDados *&dados, tAcertos *&acertos);

void calcularMediaEDesvioPadrao(tAcertos *&acertos, tMediaAcertos *mediaAcertos,
                                tDesvioPadrao *desvioPadrao);

void calcularPontuacao(tPontuacao *&pontuacao, tAcertos *&acertos,
                       tMediaAcertos *mediaAcertos, tDesvioPadrao *desvioPadrao,
                       tDados *&dados, tCursosEPesos *&cursosEPesos);

void ord(tPontuacao *pontuacao);

void pesquisaCand(tDados* &p, int insc, tCursosEPesos* &q);

void desalocarCursosEPesos(tCursosEPesos* &L);

void desalocarCursosEVagas(tCursosEVagas* &L);

void desalocarDados(tDados* &L);

void desalocarAcertos(tAcertos* &L);

void LeArqRed(char nomeArquivo05[MAX], tAlteraRed *& AlteraRed);

void menu0();

void menu1();

void AlteraReda(tAlteraRed* &p, tAcertos* &q);

