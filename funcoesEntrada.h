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