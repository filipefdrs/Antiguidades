						/*MÓDULO CONTENDO OS PROTÓTIPOS DA BIBLIOTECA, RECÉM-CRIADA, DO TIPO FILA*/

struct fila{ //TIPO ESTRUTUDADO QUE DEFINE A FILA
	int n1;
	struct fila *next;
};
typedef struct fila FILA;


FILA *fila_init(void); //INICIALIZANDO A FILA

int fila_empt(FILA *fil); //TESTANDO SE A FILA É OU NÃO VAZIA

FILA *fila_adde(FILA *end, int n); //ADICIONANDO UM ELEMENTO À FILA

FILA *fila_dele(FILA *fil, int *v); //DELETA O PRIMEIRO ELEMENTO E USA A ARITIMÉTICA DE PONTEIROS PARA COPIAR A INFORMAÇÃO DO ELEMENTO REMOVIDO

FILA *fila_freedom(FILA *fil); //DESTROINDO A FILA

void fila_imprime(FILA *fil); // IMPRIMINDO A FILA

