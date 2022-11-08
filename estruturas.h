#define MAX 80

struct tArquivos
{
  char nome01[MAX];
  char nome02[MAX];
  char nome03[MAX];
  char nome04[MAX];
  char nome05[MAX];
};

struct tTamanhos
{
  int max01, max02, max03, max04, max05;
};

struct tCursosEPesos
{
  int codigo;
  char nome[MAX];
  int red, mat, lin, hum, nat;
};

struct tCursosEVagas
{
  int codigo, ac, l1, l3, l4, l5, l7, l8, l9, l11, l13, l15;
};

struct tDados
{
  int codigo, qtdInscritos, inscricao, dia, mes, ano, idade;
  char nome[MAX];
  char vaga[4];
};

struct tAcertos
{
  int inscricao, v_lin, v_mat, v_nat, v_hum, red;
};

struct tMediaAcertos
{
  float mediaV_lin, mediaV_mat, mediaV_nat, mediaV_hum;
};

struct tDesvioPadrao
{
  float desvioPadraoV_lin, desvioPadraoV_mat, desvioPadraoV_nat,
      desvioPadraoV_hum;
};

struct tPontuacao
{
  float pontuacaoV_lin, pontuacaoV_mat, pontuacaoV_nat, pontuacaoV_hum,
      notaFinal;
  char vaga[4];
  int inscricao, classificacao, red;
};

struct tAlteraRed
{
  int inscricao, notaAntes, notaDepois;
};