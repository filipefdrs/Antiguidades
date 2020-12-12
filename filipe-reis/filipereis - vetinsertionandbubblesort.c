						/*IMPLEMENTAÇÃO DE INSERTION SORT E BUBBLE SORT COM VETOR*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOR 100
#define DI 1000

//ordenção por inserção
float sort_insertion(int ord[]){
	int key = 0, b = 1, c;
	float init = 0.0, end = 0.0;
	
	init = clock();
	while(b < TOR){
		key = ord[b];
		c = b-1;
		while(c >= 0 && ord[c] > key){
			ord[c+1] = ord[c];
			c--;			
		}
		ord[c+1] = key;
		b++;
	}
	end = clock();
	
	return (end - init)/DI;
}

//ordenção bolha
float sort_bubble(int ord[]){
	int change;
	float init = 0.0, end = 0.0;
	
	init = clock();
	do{
		change = 0;
		int cont;
		
		for(cont = 1; cont < TOR; cont++){
			if(ord[cont-1] > ord[cont]){
				int key = ord[cont];
				ord[cont] = ord[cont-1];
				ord[cont-1] = key;
				change = 1;				
			}
		}		
	}while(change);
	end = clock();
	
	return (end - init)/DI;	
}

//gerando números aleatórios
void make_random(int ord[]){
	int i = 0;
	
	srand(time(NULL));
	while(i < TOR){
		ord[i] = rand()%500;
		i++;
	}
}

//imprimindo vetor
void vet_print(int ord[]){
	int n, cont = 0;
	
	for(n = 0; n < TOR; n++){
		printf("%d\t", ord[n]);
		cont++;
		if(cont == 10){
				printf("\n");
				cont = 0;
		}	
	}
	printf("\n");	
}
	
//função que testa as ordenações	
void testando(){
	int ord[TOR];
	float temp;
	
	make_random(ord);
	printf("Lista 1\n");
	vet_print(ord);
	temp = sort_bubble(ord);
	printf("\nOrdenacao com a bubble\n");
	vet_print(ord);
	printf("tempo de execucao: %.2f (seg)\n", temp);
	make_random(ord);
	printf("\nLista 2\n");
	vet_print(ord);
	temp = sort_insertion(ord);
	printf("\nOrdenacao com a insertion\n");
	vet_print(ord);
	printf("tempo de execucao: %.2f (seg)\n", temp);
}

//programa cliente
int main(){
	
	testando();
	
	return 0;
}
