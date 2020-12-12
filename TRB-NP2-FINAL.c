						/*IMPLEMENTAÇÃO DE ALGUMAS TÉCNICAS DE ORDENAÇÃO COM LISTA DUPLA*/
					
						
                        //QuickSort is not working properly
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DI 100000
#define TAM1 40
#define TAM2 30

typedef struct _contato{
	char *nome;
	char *fone;
}TpContato;

struct list{
	char *name;
	char *phone;
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

//testa se é NULL
void list_test(void *p){
	if(p == NULL){
			printf("segmentation fault\n");
			exit(1);
		}	
}

//inicializa novo nome
char *name_init(void){ 
	char *nome = (char*)malloc(TAM2*sizeof(char));
	list_test(nome);
	int temp = (1000 + rand()%9000);
	char s[TAM1];	
	
	setbuf(stdin, NULL);
	sprintf(s, "%d", temp);
	strcpy(nome, "Fulano");
	strcat(nome, " "); 
	strcat(nome, s);
	
	return nome;
}

//inicializa novo telefone
char *phone_init(){
	char *phone = (char*)malloc(TAM2*sizeof(char));
	list_test(phone);
	int tel = (100000000 + rand()%999999999);
	char s[TAM2];
	
	setbuf(stdin, NULL);
	sprintf(phone, "%d", tel);
	
	return phone;
}
//cria novo nó da lista
List *list_init(void){
	List *new = (List*)malloc(sizeof(List));
	list_test(new);
	new->name = name_init();
	new->phone = phone_init();
	new->next = new->back = NULL;
	return new;
}

//adiciona novo nó na lista	
List *list_adic(List *l){
	List *new = list_init();
	if(l == NULL){
		return new;
	}
	new->next = l;
	if(l != NULL){
		l->back = new;
	}
	return new;
}

//busca um elemento na lista pela posição. Função axuliar para quicksort principalmente.
List *list_search(List *l, int a){
	List *walk = l;
	int counter = 0;
	
	while(walk != NULL){
		if(counter == a){
			return walk;
		
		}
		counter++;
		walk = walk->next;
	}
	return NULL;
}


//destroi a lista
void list_destroy(List *l){
	List *walk = l;
	
	while(walk != NULL){
		List *temp = walk->next;
		free(walk->name);
		free(walk->phone);
		free(walk);
		walk = temp;
	}
}

//imprimindo a lista
void list_print(List *l){
	List *walk = l;
	
	while(walk != NULL){
		printf("\n--------------------");
		printf("\nNome: %s\nFone: %s", walk->name, walk->phone);
		walk = walk->next;
	}
	printf("\n--------------------");
	printf("\n");
}

//imprimindo vetor
void vet_print(TpContato *l){
	int i = 0;
	
	while(i < TAM1){
		printf("\n--------------------");
		printf("\nNome: %s\nFone: %s", l[i].nome, l[i].fone);
		i++;
	}
	printf("\n--------------------");
	printf("\n");
}

//calculando o tamanho da lista
int list_dimension(List *l){
	List *walk = l;
	int counter = 0;
	
	while(walk != NULL){
		counter++;
		walk = walk->next;
	}
	return counter;
}

//ordenação cocktail (bubble bidirecional)
void sup_cocktail(List *l){
		List *low = l, *high = l, *i;
		
		while(high->next != NULL){ //encontra ultima posicao
			
			high = high->next; 
			
		}
		int flag = 0; //controle do laço principal
		
		while(flag == 0 && low != high){
				flag = 1;
			
				for(i = low; i->next != NULL; i = i->next){ //ida da esquerda para direita
						if(strcmp(i->name, i->next->name) > 0){//se a informação atual é maior que a próxima informação, troca
								char temp[TAM1];
								strcpy(temp, i->name);
								strcpy(i->name, i->next->name);
								strcpy(i->next->name, temp);
								
								strcpy(temp, i->phone);
								strcpy(i->phone, i->next->phone);
								strcpy(i->next->phone, temp);
										
								flag = 0;						
						}				
				}	 
			
				high = high->back;
				
				for(i = high; i->back != NULL; i = i->back){//ida da direita para esquerda
						if(strcmp(i->name, i->back->name) < 0){//se a informação atual menor que a próxima informação, troca
								char temp[TAM1];
								strcpy(temp, i->name);
								strcpy(i->name, i->back->name);
								strcpy(i->back->name, temp);
								
								strcpy(temp, i->phone);
								strcpy(i->phone, i->back->phone);
								strcpy(i->back->phone, temp);
								
								flag = 0;
						}
				}
				low = low->next;
		}
}

//chamando cocktail
float list_sort_cocktail(List *lt){
	float init = 0.0, end = 0.0;
	
	init = clock();
	sup_cocktail(lt);
	end = clock();

	return (end-init)/DI;	
}

//ordenação quicksort	
void partition(List *lt, int left, int right){
		List *i, *j, *infoleft;
		int ii, jj;
		char pivo[TAM1], ph[TAM2];
		
		while(right > left){
				i = list_search(lt, left); 
				j = list_search(lt, right);
				ii = left;
				jj = right;
				infoleft = list_search(lt, left);
				strcpy(pivo, infoleft->name);
				strcpy(ph, infoleft->phone);
								
				while(ii < jj){
						while(strcmp(j->name, pivo) > 0){//comparando com o pivo e decrementando o índice j
							jj--;
							j = j->back;	
						}
						//troca
						strcpy(i->name, j->name);
						strcpy(i->phone, j->phone);
						
						while(strcmp(pivo, i->name) > 0 && ii < jj){//comparando com o pivo e incrementando o índice i
							ii++;
							i = i->next;
						}
						//troca
						strcpy(j->name, i->name);
						strcpy(j->phone, i->phone);
				}
				//pivo vai para seu lugar
				strcpy(i->name, pivo);
				strcpy(i->phone, ph);
				//chamada recursiva
				partition(lt, left, ii-1);
				left = ii+1;
		}
}

//chamanda a quicksort
float list_sort_quick(List *lt){
	float init = 0.0, end = 0.0;
	
	init = clock();
	partition(lt, 0, list_dimension(lt)-1);
	end = clock();

	return (end-init)/DI;	
}

//gerando números aleatórios e preenchendo a lista
List *make_random(List *l, int j){	
	int i = 0;
	
	while(i < j){
		l = list_adic(l); 
		i++;
	}
	
	return l;
}

//ordenação cocktail com vetor
void OrdenarVetorCocktailSort(TpContato  Vetor[]){
    int NumeroElementosVetor,InicioDosElementos,UltimoDosElementos, Trocar,i;
    TpContato ElementoAuxiliar;
 
    NumeroElementosVetor = TAM1;
    InicioDosElementos   = 0;
    UltimoDosElementos   = NumeroElementosVetor - 1;
    Trocar = 0; 
     
    while(Trocar == 0 && InicioDosElementos < UltimoDosElementos){
        Trocar = 1; 
 
        for(i = InicioDosElementos; i < UltimoDosElementos; i = i + 1){ // Direção Do For [Esquerda -> Direita]
            if (strcmp(Vetor[i].nome, Vetor[i + 1].nome) > 0){
                ElementoAuxiliar = Vetor[i];
                Vetor[i]         = Vetor[i+1];
                Vetor[i+1]       = ElementoAuxiliar;
                Trocar           = 0;
            }
        }
        UltimoDosElementos = UltimoDosElementos - 1; 
 
        for(i = UltimoDosElementos; i > InicioDosElementos; i = i - 1){ // Direção Do For [Direita -> Esquerda]
            if (strcmp(Vetor[i].nome, Vetor[i - 1].nome) < 0){
                ElementoAuxiliar = Vetor[i];
                Vetor[i]         = Vetor[i-1];
                Vetor[i-1]       = ElementoAuxiliar;
                Trocar           = 0;
            }
        }
        InicioDosElementos = InicioDosElementos + 1;  
         
    }
}

//chamando cocktail com vetor
float vet_sort_cocktail(TpContato *vet){
	float init = 0.0, end = 0.0;
	
	init = clock();
	OrdenarVetorCocktailSort(vet);
	end = clock();

	return (end-init)/DI;	

}

//ordenação quicksort com vetor
void OrdenarVetorQuickSort(TpContato Vetor[], int IndiceEsquerda, int IndiceDireira){
    int Pivo = IndiceEsquerda, i, j;
    TpContato ElementoAuxiliar;
 
    for(i=IndiceEsquerda+1;i<=IndiceDireira;i++){
        j = i;
        if(strcmp(Vetor[j].nome, Vetor[Pivo].nome) < 0){
            ElementoAuxiliar = Vetor[j];
            while(j > Pivo){    
                Vetor[j] = Vetor[j-1];
                j--;
            }
            Vetor[j] = ElementoAuxiliar;
            Pivo++;        
        }  
    }
    if((Pivo-1) >= IndiceEsquerda){
        OrdenarVetorQuickSort(Vetor, IndiceEsquerda, (Pivo-1));
    }
    if((Pivo+1) <= IndiceDireira){
        OrdenarVetorQuickSort(Vetor, (Pivo+1), IndiceDireira);
    }
}

//chamando quicksort com vetor
float vet_sort_quick(TpContato *lt){
	float init = 0.0, end = 0.0;
	
	init = clock();
	OrdenarVetorQuickSort(lt, 0, TAM1-1);
	end = clock();

	return (end-init)/DI;	
}

//menu 
int menu(){
	int opc, tam_lista;
	First *lista = first_init();
	List *li1 = NULL, *li2 = NULL;
	float t;
	TpContato *vet = NULL, v1[TAM1], v2[TAM1];
	
	while(1){
		printf("\n1) Criar lista\n");
		printf("2) Criar vetor\n");
		printf("3) CockTailSort\n");
		printf("4) QuickSort\n");
		printf("5) Sair\n");
		printf("--> ");
		scanf("%d", &opc);
		
		if(opc == 1){ //criando a lista
			int j = 0;
			printf("Tamanho da lista a ser Criada: ");
			scanf("%d", &tam_lista);
			if(lista->head != NULL){
				list_destroy(lista->head);
				list_destroy(li1);
				list_destroy(li2);
				lista->head = li1 = li2 = NULL;
			}
			lista->head = make_random(lista->head, tam_lista);
			li1 = make_random(li1, tam_lista);
			li2 = make_random(li2, tam_lista);
			List *w1 = li1, *w2 = li2, *w = lista->head;
			
			while(w1 != NULL && w2 != NULL && w != NULL){
				strcpy(w1->name, w->name);
				strcpy(w1->phone, w->phone);
				strcpy(w2->name, w->name);
				strcpy(w2->phone, w->phone);
				w1 = w1->next;
				w2 = w2->next;
				w = w->next;
				
			}	
			printf("\nLista:\n");
			list_print(lista->head);
	
		}else if(opc == 2){//criando o vetor
			int j = 0;
			vet = (TpContato*)malloc(TAM1*sizeof(TpContato));
			list_test(vet);
			while(j < TAM1){
				vet[j].nome = name_init();
				vet[j].fone = phone_init();
				v1[j].nome = name_init();
				v1[j].fone = phone_init();
				v2[j].nome = name_init();
				v2[j].fone = phone_init();
				strcpy(v1[j].nome, vet[j].nome);
				strcpy(v1[j].fone, vet[j].fone);
				strcpy(v2[j].nome, vet[j].nome);
				strcpy(v2[j].fone, vet[j].fone);
				j++;
			}
			vet_print(vet);
		}else if(opc == 3 ){ //ordenação com a cocktail
			if(vet == NULL && lista->head != NULL){
				printf("vetor inexistente\n");
				t = list_sort_cocktail(li1);
				printf("\nExemplo de saída lista:");
				list_print(li1);
				printf("tempo de execucao: %f seg(s)\n\n", t);
			}else if(vet != NULL && lista->head == NULL){
				t = vet_sort_cocktail(v1);
				printf("\nExemplo de saída vetor:");
				vet_print(v1);
				printf("\ntempo de execucao: %f seg(s)\n\n", t);
				printf("lista inexistente\n");
			}else if(vet != NULL && lista->head != NULL){
				t = vet_sort_cocktail(v1);
				printf("\nExemplo de saída vetor:");
				vet_print(v1);
				printf("\ntempo de execucao: %f seg(s)\n\n", t);
		
				t = list_sort_cocktail(li1);
				printf("\nExemplo de saída lista:");
				list_print(li1);
				printf("tempo de execucao: %f seg(s)\n\n", t);
			}else if(vet == NULL && lista->head == NULL){
					printf("lista e vetor inexistentes\n");
			}
		}else if(opc == 4){	//ordenação com a quicksort
			if(vet == NULL && lista->head != NULL){
				printf("vetor inexistente\n");
				t = list_sort_quick(li2);
				printf("\nExemplo de saída lista:");
				list_print(li2);
				printf("tempo de execucao: %f seg(s)\n\n", t);
			}else if(vet != NULL && lista->head == NULL){
				t = vet_sort_quick(v2);
				printf("\nExemplo de saída vetor:");
				vet_print(v1);
				printf("\ntempo de execucao: %f seg(s)\n\n", t);
				printf("lista inexistente\n");
			}else if(vet != NULL && lista->head != NULL){
				t = vet_sort_quick(v2);
				printf("\nExemplo de saída vetor:");
				vet_print(v1);
				printf("\ntempo de execucao: %f seg(s)\n\n", t);
		
				t = list_sort_quick(li2);
				printf("\nExemplo de saída lista:");
				list_print(li2);
				printf("tempo de execucao: %f seg(s)\n\n", t);
			}else if(vet == NULL && lista->head == NULL){
					printf("lista e vetor inexistentes\n");
			}
		}else if(opc == 5){ //saindo
			system("clear");
			return 5;
		
		}else if(opc < 1 || opc > 5){
			printf("Opcao incorreta!\n\n");
		}
	}
}

//programa cliente
int main (){
	
	srand( (unsigned)time(NULL) );
	menu();
	
	return 0;
}
