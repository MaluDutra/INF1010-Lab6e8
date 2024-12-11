#include <stdio.h>
#include <stdlib.h>

typedef struct _viz Viz;
struct _viz {
    int noj; /* numero do no? */
    float peso;
    Viz* prox;
};

typedef struct _grafo Grafo;
struct _grafo {
    int nv; /* numero de nos ou vertices */
    int na; /* numero de arestas */
    Viz** viz; /* viz[i] aponta para a lista de arestas incidindo em i */
};

typedef struct _arestas Arestas;
struct _arestas {
    int no1;
    int no2;
    float peso;
};

Grafo* cria_grafo(void);
void busca_amplitude(Grafo* grafo);
int pertence(int fila[], int visitados[], int no);
void mapeia_grafo(Grafo* grafo, Arestas arestas[]);
void ordenar_pesos(Arestas arestas[], int qtd_arestas);
void atualizar_floresta(int florestas[], int num, int mudar);
void algoritmo_kruskal(Grafo* grafo);

Grafo* cria_grafo(void){ // cria o grafo em lista de adjacências
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->nv = 9;
    grafo->na = 14;
    grafo->viz = (Viz**)malloc(sizeof(Viz*)*grafo->nv);
    for (int i = 0; i < grafo->nv; i++){
        grafo->viz[i] = (Viz*)malloc(sizeof(Viz));
    }

    Viz* no = grafo->viz[0];
    no->noj = 1;
    no->peso = 4;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 8;
    no->peso = 8;
    no->prox = NULL;

    no = grafo->viz[1];
    no->noj = 0;
    no->peso = 4;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 3;
    no->peso = 8;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 8;
    no->peso = 11;
    no->prox = NULL;

    no = grafo->viz[2];
    no->noj = 1;
    no->peso = 8;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 4;
    no->peso = 7;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 6;
    no->peso = 4;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 9;
    no->peso = 2;
    no->prox = NULL;

    no = grafo->viz[3];
    no->noj = 3;
    no->peso = 7;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 5;
    no->peso = 9;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 6;
    no->peso = 14;
    no->prox = NULL;

    no = grafo->viz[4];
    no->noj = 4;
    no->peso = 9;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 6;
    no->peso = 10;
    no->prox = NULL;

    no = grafo->viz[5];
    no->noj = 3;
    no->peso = 4;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 4;
    no->peso = 14;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 5;
    no->peso = 10;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 7;
    no->peso = 2;
    no->prox = NULL;

    no = grafo->viz[6];
    no->noj = 6;
    no->peso = 2;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 8;
    no->peso = 1;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 9;
    no->peso = 6;
    no->prox = NULL;

    no = grafo->viz[7];
    no->noj = 0;
    no->peso = 8;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 1;
    no->peso = 11;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 7;
    no->peso = 1;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 9;
    no->peso = 7;
    no->prox = NULL;

    no = grafo->viz[8];
    no->noj = 3;
    no->peso = 2;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 7;
    no->peso = 6;
    no->prox = (Viz*)malloc(sizeof(Viz));
    no = no->prox;
    no->noj = 8;
    no->peso = 7;
    no->prox = NULL;

    return grafo;
}

void busca_amplitude(Grafo* grafo){ // realiza a busca por amplitude
    Viz* no;
    int fila[9] = {0, -1, -1, -1, -1, -1, -1, -1, -1};
    int visitados[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int prox = fila[0];
    int pos_fila = 1;
    int pos_visitados = 0;

    while (prox != -1){
        printf("bfs(%d)\t", prox);
        visitados[pos_visitados] = prox;
        pos_visitados++;
        if (prox > 2) prox -= 1; // realiza subtração para o número do nó alinhar com o da lista
        no = grafo->viz[prox];

        while (no){ // adiciona os vizinhos na fila caso eles não estejam nela e nem em visitados 
            if (!pertence(fila, visitados, no->noj)){
                fila[pos_fila++] = no->noj;
            }
            no = no->prox;
        }

        for (int i = 0; i < 8; i++){ // tira o nó atual da fila
            fila[i] = fila[i+1];
        }
        fila[8] = -1;
        pos_fila -=1;

        printf("[");
        for (int i = 0; fila[i] != -1; i++){ // printa a fila
            if (fila[i+1] != -1){
                printf("%d, ", fila[i]);
            }
            else {
                printf("%d", fila[i]);
            }
        }
        printf("]\n");

        prox = fila[0];
    }
}

int pertence(int fila[], int visitados[], int no){ // retorna 1 caso o numero esteja na fila ou em visitados
    int ver = 0;
    for (int i = 0; i < 9; i++){
        if (no == visitados[i] || no == fila[i]){
            ver = 1;
            break;
        }
    }
    return ver;
}

void mapeia_grafo(Grafo* grafo, Arestas arestas[]){ // pega o grafo gerado e transforma ele em um vetor somente com as arestas, sem repetir elas
    int visitados[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    int i = 0;
    int aux = 0;
    Viz* no = (Viz*)malloc(sizeof(Viz));
    while(i<grafo->nv){
        no = grafo->viz[i];
        do{
            int porra2 = no->noj;
            int porra = visitados[no->noj];
            if (visitados[no->noj] == -1){
                if (i >= 2){
                    arestas[aux].no1 = i+1;
                    arestas[aux].no2 = no->noj;
                    arestas[aux].peso = (int) no->peso;
                    aux++;
                } else{
                    arestas[aux].no1 = i;
                    arestas[aux].no2 = no->noj;
                    arestas[aux].peso = (int) no->peso;
                    aux++;
                }
            }
            no = no->prox;
        } while(no != NULL);
        
        if(i >= 2){
            visitados[i+1] = i+1;
        } else{
            visitados[i] = i;
        }
        i++;
    }
}

void ordenar_pesos(Arestas arestas[], int qtd_arestas){ // ordena o vetor de arestas de acordo com o peso delas, indo do menor para o maior
    Arestas aresta_temp;
    for (int i = 0; i < qtd_arestas; i++){
        for (int j = 0; j < qtd_arestas; j++){
            if (arestas[i].peso < arestas[j].peso){
                aresta_temp = arestas[i];
                arestas[i] = arestas[j];
                arestas[j] = aresta_temp;
            }
        }
    }
}

void atualizar_floresta(int florestas[], int num, int mudar){ // atualiza o vetor de inteiros que corresponde a qual floresta determinado nó (neste caso o índice) pertence
    for (int i = 0; i < 10; i++){
        if (florestas[i] == mudar){
            florestas[i] = num;
        }
    }
}

void algoritmo_kruskal(Grafo* grafo){ // realiza o algoritmo de kruskal e exibe a árvore geradora mínima obtida
    Arestas arestas[grafo->na];
    mapeia_grafo(grafo, arestas);
    ordenar_pesos(arestas, grafo->na);
    
    float custo_minimo = 0;
    int florestas[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int aux_floresta = 0;
    printf("\n\nÁrvore geradora mínima:\n\n");
    for (int i = 0; i < grafo->na; i++){
        if ((florestas[arestas[i].no1] == -1) && (florestas[arestas[i].no2] == -1)){
            florestas[arestas[i].no1] = aux_floresta++;
            florestas[arestas[i].no2] = florestas[arestas[i].no1];
        } else if ((florestas[arestas[i].no1] == -1) && (florestas[arestas[i].no2] != -1)){
            florestas[arestas[i].no1] = florestas[arestas[i].no2];
        } else if ((florestas[arestas[i].no1] != -1) && (florestas[arestas[i].no2] == -1)){
            florestas[arestas[i].no2] = florestas[arestas[i].no1];
        } else if ((florestas[arestas[i].no1] != florestas[arestas[i].no2])){
            atualizar_floresta(florestas, florestas[arestas[i].no1], florestas[arestas[i].no2]);
        } else{
            continue;
        }
        printf("%d -- %d = %0.1f\n", arestas[i].no1, arestas[i].no2, arestas[i].peso);
        custo_minimo += arestas[i].peso;
    }
    printf("Custo mínimo: %0.1f\n", custo_minimo);
}

int main (void){ 
    Grafo* grafo = cria_grafo();
    busca_amplitude(grafo);
    
    algoritmo_kruskal(grafo);

    return 0;
}

