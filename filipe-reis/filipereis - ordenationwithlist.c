						/*IMPLEMENTAÇÃO DE INSERTION SORT E BUBBLE SORT COM LISTA DUPLA*/
					

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HI 100
#define DI 1000


struct list{
	int number;
	struct list *next;
	struct list *back;
};
typedef struct list List;

struct first{
	struct list *head;
};
typedef struct first First;

//cria uma estrutura auxiliar
First *first_init(void){
	First *new = (First*)malloc(sizeof(First));
	if(new == NULL){
		printf("segmentation fault\n");
		exit(1);
	}
	new->head = NULL;
	return new;
}

//cria novo nó da lista
List *list_init(void){
	List *new = (List*)malloc(sizeof(List));
	if(new == NULL){
		printf("segmentation fault\n");
		exit(1);
	}
	new->next = new->back = NULL;
	return new;
}

//destroi a lista
void list_destroy(List *l){
	List *walk = l;
	
	while(walk != NULL){
		List *temp = walk->next;
		free(walk);
		walk = temp;
	}
}
	
//adiciona novo nó na lista	
List *list_adic(List *l, int d){
	List *new = list_init();
	new->number = d;
	if(l == NULL){
		return new;
	}
	new->next = l;
	if(l != NULL){
		l->back = new;
	}
	return new;
}

//busca um elemento na lista
List *list_search(List *l, int a){
	List *walk = l;
	
	while(walk != NULL){
		if(walk->number == a){
				return walk;
		}
		walk = walk->next;
	}
	return NULL;
}

//imprimindo a lista
void list_print(List *l){
	List *walk = l;
	int cont = 0;
	while(walk != NULL){
		printf("%d\t", walk->number);
		walk = walk->next;
		cont++;
		if(cont == 10){
				printf("\n");
				cont = 0;
		}
	}
	printf("\n");
}

//deletando elemento da lista
List *list_delet(List *l, int b){
	List *remove = list_search(l, b);
	
	if(remove != NULL){
		if(remove->back == NULL){
			l->next->back = NULL;
		}else{
			remove->back->next = remove->next;
			if(remove->next != NULL){
				remove->next->back = remove->back; 
			}
		}		
	}
	return l;
}

//calculando o tamanho da lista
int list_comprimento(List *l){
	List *walk = l;
	int counter = 0;
	
	while(walk != NULL){
		counter++;
		walk = walk->next;
	}
	return counter;
}

//ordenação por inserção
float sort_insertion(List *l){
	List *pont1, *pont2, *copy = NULL;
	int key = 0;
	float begin = 0.0, end = 0.0;
	
	begin = clock();
	pont1 = l->next;
	while( pont1 != NULL ){
		key = pont1->number;
		pont2 = pont1->back;
		while(pont2 != NULL && pont2->number > key){
			copy = pont2;
			pont2->next->number = pont2->number;
			pont2 = pont2->back;
		
		}
		if(pont2 != NULL){
			pont2->next->number = key;
		}else{
			copy->number = key;
		}	
		pont1 = pont1->next;	
	}
	end = clock();
	
	return (end - begin)/DI;	
}

//ordenação bolha
float sort_bubble(List *l){
	int change;
	List *walk;
	float begin = 0.0, end = 0.0;
	
	begin = clock();	
	do{
		change = 0;
		
		for(walk = l->next; walk != NULL; walk = walk->next){
			if(walk->back->number > walk->number){
				int copy = walk->number;
				walk->number = walk->back->number;
				walk->back->number = copy;			
				change = 1;
			}
		}
	}while(change);
	end = clock();
	
	return (end - begin)/DI;	
}

//gerando números aleatórios e preenchendo a lista
List *make_random(List *l){
	int i = 0;
	
	srand(time(NULL));
	while(i < HI){
		int temp = rand()%500;
		l = list_adic(l, temp); 
		i++;
	}
	return l;
}

//função que testa as ordenações
void testando(){
	First *base = first_init();
	float tim;
	
	//resultados com a sort_insertion();
	base->head = make_random(base->head);
	printf("Lista aleatoria 1\n");
	list_print(base->head);
	tim = sort_insertion(base->head);
	printf("\n\nLista ordenada com a insertion\n");
	list_print(base->head);
	printf("tempo de execucao: %.2f (seg)\n", tim);
	list_destroy(base->head);
	free(base);
	
	//resultados com a sort_bubble();
	base = first_init();
	base->head = make_random(base->head);
	printf("\n\nLista aleatoria 2\n");
	list_print(base->head);
	tim = sort_bubble(base->head);
	printf("\n\nLista ordenada com a bubble\n");
	list_print(base->head);
	printf("tempo de execucao: %.2f (seg)\n", tim);
	list_destroy(base->head);
	free(base);
}


int main (){

	testando();
	
	return 0;
}
