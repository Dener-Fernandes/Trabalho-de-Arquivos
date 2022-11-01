#define MAX 80

struct tCursosEPesos
{
  int codigo;
  char nome[MAX];
  int red, mat, lin, hum, nat;
  struct tCursosEPesos *prox;
};

struct tCursosEVagas
{
  int codigo, ac, l1, l3, l4, l5, l7, l8, l9, l11, l13, l15;
  struct tCursosEVagas *prox;
};

struct tDados
{
  int codigo, qtdInscritos, inscricao, dia, mes, ano;
  char nome[MAX];
  char vaga[4];
  struct tDados *prox;
};

struct tAcertos
{
  int inscricao, v_lin, v_mat, v_nat, v_hum, red;
  struct tAcertos *prox;
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
  struct tPontuacao *prox;
};

struct tAlteraRed
{
  int inscricao, notaAntes, notaDepois;
  struct tAlteraRed *prox;
};