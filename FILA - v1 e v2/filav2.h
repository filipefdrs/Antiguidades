					/*MÓDULO CONTENDO OS PROTÓTIPOS DA BIBLIOTECA, RECÉM-CRIADA, DO TIPO FILA VERSÃO 2*/
struct fila1{ //ESTRUTURA INTERNA
	int n1;
	struct fila1 *next;
};
typedef struct fila1 FILA1;

struct fila{ //ESTRUTURA EXTERNA
	FILA1 *begin;
	FILA1 *end;
};
typedef struct fila FILA;

FILA *fila_init(void); //FUNÇÃO DE INICIALIZAÇÃO DA FILA

int fila_empt(FILA *fil);//FUNÇÃO QUE TESTA SE A FILA É OU NÃO VAZIA

void fila_adde(FILA *fil, int n); //FUNÇÃO QUE ADICIONA ELEMENTOS

int fila_dele(FILA *fil); //FUNÇÃO QUE REMOVE ELEMENTOS E RETORNA A INFORMAÇÃO RETIRADA

void fila_freedom(FILA *fil); //LIBERANDO A FILA

void fila_imprime(FILA *fil); //IMPRIMINDO A FILA
