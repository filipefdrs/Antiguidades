						/*IMPLEMENTAÇÃO DE FILAv1 COM LISTA LINEAR SIMPLES*/
#include <stdio.h>
#include <stdlib.h>
#include "filav1.h" //BIBLIOTECA COM OS PROTÓTIPOS E STRUCTS UTILIZADOS

FILA *fila_init(void){ //INICIALIZANDO A FILA
	return NULL;
}

int fila_empt(FILA *fil){
	if(fil == NULL){
		return 0; //Retorna 0 se vazia
	}
	return 1; //Retorna 1 se cheia
}

FILA *fila_adde(FILA *end, int n){ //FUNÇÃO QUE ADICIONA ELEMENTO À FILA
	FILA *no = (FILA*)malloc(sizeof(FILA)); //alocando elemento
	if(no == NULL){//teste de alocação
		printf("SEGMENTATION FAULT\n");
		exit(4);
	}
	no->n1 = n; //atribuindo o valor lido ao novo elemento da fila
	no->next = NULL; //ajustando o encadeamento para que se torne o último elemento da fila
	
	if(end == NULL){
		return no;
	}
	end->next = no;
	return no;
}

FILA *fila_dele(FILA *fil, int *nn){ //FUNÇÃO QUE REMOVE UM ELEMENTO DA FILA
	FILA *no = fil->next;
	*nn = fil->n1; //copiando a informação removida
	free(fil);
	fil = no;
	return fil;
}

FILA *fila_freedom(FILA *fil){ //FUNÇÃO QUE DESTROI TODOS OS ELEMENTOS DA FILA
	FILA *no = fil;
	while(no != NULL){
		FILA *temp = no->next;
		free(no);
		no = temp;
	}
	return NULL;
}
	

void fila_imprime(FILA *fil){ //FUNÇÃO QUE IMPRIME A FILA
	FILA *no = fil;
	
	for(; no != NULL; no = no->next){
		printf("%d\t", no->n1);
	}
	printf("\n");
}

int main(){
	FILA *fil;
	FILA *end;
	int n, op, nn;
	
	fil = end = fila_init();
	while(1){
		printf("===============MENU===============\n");
		printf("1 = Adiciona elemento à fila;\n2 = Remove elemento da fila;\n3 = Testa se a fila é vazia;\n4 = Destroi a fila;\n5 = Imprime a fila;\n6 = Sair;\n");
		printf("==================================\n");
		scanf("%d", &op);
	
		switch(op){
			case 1:
				scanf("%d", &n);
				if(fil == NULL){
					end = fil = fila_adde(fil, n);
					break;
				}
				end = fila_adde(end, n);
				break;
		
			case 2:
				if(fil != NULL){
					fil = fila_dele(fil, &nn);
					printf("Elemento removido: %d\n", nn);
					if(fil == NULL){
						end = NULL;
					}
					break;
				}
				
				printf("Fila vazia\n");
				break;
			
			case 3:
				if(fila_empt(fil) == 0){
					printf("Fila vazia\n");
				}else{
					printf("Fila nao vazia\n");
				}
				break;
			
			case 4:
				if(fil != NULL){
					fil = end = fila_freedom(fil);
					printf("Sucesso\n");
					break;
				}
				printf("Fila vazia\n");
				break;
		
			case 5:
				if(fil == NULL){
					printf("Fila vazia\n");
					break;
				}
				fila_imprime(fil);
				break;
			
			case 6:
				if(fil != NULL){
					fil = end = fila_freedom(fil);
				}
				printf("Tchau!\n");
				return 0;
			
			default:
				printf("Operação invalida\n");
				break;
		}
		printf("\n");
	}
	printf("\n");	
	return 0;
}
