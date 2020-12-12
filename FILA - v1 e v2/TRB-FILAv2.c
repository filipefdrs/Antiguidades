						/*IMPLEMENTAÇÃO DE FILAv2 COM LISTA LINEAR SIMPLES*/
#include <stdio.h>
#include <stdlib.h>
#include "filav2.h" //BIBLIOTECA COM OS PROTÓTIPOS E STRUCTS UTILIZADOS

FILA *fila_init(void){ //INICIALIZANDO A FILA
	FILA *fil = (FILA*)malloc(sizeof(FILA));
	if(fil == NULL){ //testando a alocação dinâmica
		printf("Segmentation Fault\n");
		exit(5);
	}
	fil->begin = fil->end = NULL; //inicia com a fila vazia
	return fil;
}

int fila_empt(FILA *fil){//TESTANDO SE ESTÁ VAZIA OU CHEIA
	return (fil->begin == NULL); //retorna 1 caso verdadeiro e 0 caso contrário
}

void fila_adde(FILA *fil, int n){ //ADICIONANDO NOVOS ELEMENTOS À FILA
	FILA1 *no = (FILA1*)malloc(sizeof(FILA1));
	if(no == NULL){ //teste de alocação
		printf("Segmentation Fault\n");
		exit(1);
	}
	no->n1 = n;
	no->next = NULL;
	if(fil->end != NULL){//ajustes de encadeamento
		fil->end->next = no;
	}else{
		fil->begin = no;
	}	
	fil->end = no;
}

int fila_dele(FILA *fil){//REMOVENDO ELEMENTOS
	FILA1 *temp;
	int t;
	
	temp = fil->begin;
	t = temp->n1; //copiando a informação a ser removida
	fil->begin = temp->next; //ajustes de encadeamento
	if(fil->begin == NULL){
		fil->end = NULL;
	}
	free(temp);
	return t; //retorna a informação da estrutura removida
}

void fila_freedom(FILA *fil){ //FUNÇÃO QUE DESTROI TODOS OS ELEMENTOS DA FILA
	FILA1 *no = fil->begin;
	while(no != NULL){
		FILA1 *temp = no->next;
		free(no);
		no = temp;
	}
	free(fil);
}

void fila_imprime(FILA *fil){ //FUNÇÃO QUE IMPRIME A FILA
	FILA1 *no = fil->begin;
	
	for(; no != NULL; no = no->next){
		printf("%d\t", no->n1);
	}
	printf("\n");
}

int main(){
	FILA *fil;
	int n, op, nn;
	
	fil = fila_init();
	while(1){
		printf("===============MENU===============\n");
		printf("1 = Adiciona elemento à fila;\n2 = Remove elemento da fila;\n3 = Testa se a fila é vazia;\n4 = Destroi a fila;\n5 = Imprime a fila;\n6 = Sair;\n");
		printf("==================================\n");
		scanf("%d", &op);
	
		switch(op){
			case 1:
				scanf("%d", &n);
				fila_adde(fil, n);
				break;
			
			case 2:
				if(fil->begin == NULL){
					printf("Fila vazia\n");
					break;
				}
				nn = fila_dele(fil);
				printf("Elemento retirado: %d\n", nn);
				break;
				
			case 3:
				if(fila_empt(fil)){
					printf("Fila vazia\n");
					break;
				}
				printf("Fila não vazia\n");
				break;
			
			case 4:
				if(fila_empt(fil)){
					printf("Fila vazia\n");
					break;
				}
				fila_freedom(fil);
				fil = fila_init(); //como a fila foi destruída é necessário recriá-la para continuar no laço.
				printf("Sucesso\n");
				break;
				
			case 5: 
				if(fila_empt(fil)){
					printf("Fila vazia\n");
					break;
				}
				fila_imprime(fil);
				break;
				
			case 6:
				fila_freedom(fil);//destruição permanente do programa
				printf("Tchau!!!\n");
				return 0; //saindo da execução
				
			default:
				printf("Operação invalida\n");
				break;
		}
		printf("\n");
	}
	printf("\n");	
	return 0;
}
