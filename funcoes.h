#include "estruturas.h"
#define MAX01 113
#define MAX02 113
#define MAX03 16332
#define MAX04 13873

int ler_e_inserir(tArquivos arquivosNomes, tTamanhos tamanhos,
                  tCursosEPesos *cursosEPesos, tCursosEVagas *cursosEVagas,
                  tDados *dados, tAcertos *acertos, tAlteraRed *alteraRedacao);

int pegarTamanhoArquivoDados(tArquivos arquivosNomes, tTamanhos tamanhos);

void calcularMediaEDesvioPadrao(tAcertos acertos[MAX04],
                                tMediaAcertos *mediaAcertos, tTamanhos tamanhos,
                                tDesvioPadrao *desvioPadrao);

void calcularPontuacao(tPontuacao *pontuacao, tAcertos *acertos,
                       tTamanhos tamanhos, tMediaAcertos *mediaAcertos,
                       tDesvioPadrao *desvioPadrao, tDados *dados,
                       tCursosEPesos *cursosEPesos);

void alterarNotaRedacao(tAlteraRed alteraRedacao, tTamanhos tamanhos,
                        tAcertos acertos);

void alterarNotaRedacao(tTamanhos tamanhos, tAlteraRed *alteraRedacao,
                        tAcertos *acertos);

void procurarCandidato(tTamanhos tamanhos, int inscricao, tDados *dados,
                       tCursosEPesos *cursosEPesos);

void menu0();

void menu1();

void imprimirPontuacao(tTamanhos tamanhos, tPontuacao *pontuacao);

void ordenaAlfabetica(tTamanhos tamanhos, tCursosEPesos *cursosEPesos);

void imprimirNome(tTamanhos tamanhos, tCursosEPesos *cursosEPesos);

void calculaIdade(tDados *dados, tTamanhos tamanhos);

void trocaPont(tPontuacao *a, tPontuacao *b);

void bubblePont(tTamanhos tamanhos, tPontuacao *&pontuacao, tDados *&dados);

void ordenaPont(tPontuacao *pontuacao, tDados *dados, tTamanhos tamanhos,
                tCursosEPesos *cursosEPesos);