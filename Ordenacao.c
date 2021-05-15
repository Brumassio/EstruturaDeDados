#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void imprimirVet(int *v, int n){
    printf("\n");
    for(int i=0; i<n; i++){
        printf(" [%d] ", v[i]);
    }
    printf("\n");
}


void bubbleSort(int *v, int n){
    int continua, aux, fim;
    fim = n;
    do{
        continua = 0;
        for(int i=0; i< fim-1; i++){
            if(v[i] > v[i+1]){
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                continua = i;
            }
        }
        fim--;
    }while(continua != 0);
}


void selectionSort(int *v, int n){
    int i, j, menor, troca;
    for (i=0; i<n-1; i++){
        menor = i;
        for(j = i+1; j<n; j++){
            if(v[j] < v[menor])
                menor = j;
        }
        if(i != menor){
            troca = v[i];
            v[i] = v[menor];
            v[menor] = troca;
        }
    }
}


void insertionSort(int *v, int n){

    int i, j, atual;
    for (i=1; i<n; i++){
        atual = v[i];
        for(j=i; (j>0) && (atual < v[j-1]); j--){
            v[j] = v[j-1];
            imprimirVet(v,10);
        }
        v[j] = atual;
    }
}

void insertionSort_Decress(int *v, int n){
    int i, j, a;
    for (i=1; i<n; i++){
        a = v[i];
        for(j=i; (j>0) && (a > v[j-1]); j--){
            v[j] = v[j-1];
        }
        v[j] = a;
    }
}


void merge(int *v,int inicio, int meio, int fim){
    int *temp, p1, p2, tamanho;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (int*) malloc(tamanho*sizeof(int));
    if(temp != NULL){
        for(int i=0; i<tamanho; i++){
            if((fim1==0) && (fim2==0)){
                if(v[p1] < v[p2])
                    temp[i] = v[p1++];
                else
                    temp[i] = v[p2++];
                if(p1>meio) fim1 = 1;
                if(p2>fim) fim2 = 1;
            }else{
                if(fim1==0)
                    temp[i] = v[p1++];
                else
                    temp[i] = v[p2++];
            }
        }
        for(int j=0, k=inicio; j<tamanho; j++, k++)
            v[k] = temp[j];
    }
    free(temp);
}


void mergeSort(int *v, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = floor((inicio+fim)/2);
        mergeSort(v, inicio, meio);
        mergeSort(v, meio+1, fim);
        imprimirVet(v, 7);
        merge(v, inicio, meio, fim);
    }
}


int particiona(int *v, int inicio, int final){
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = final;
    pivo = v[inicio];
    while(esq < dir){
        while(v[esq] <= pivo)
            esq++;
        while(v[dir] > pivo)
            dir--;
        if(esq < dir){
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
        }
    }
    v[inicio] = v[dir];
    v[dir] = pivo;
    return dir;
}


void quickSort(int *v, int inicio, int fim){
    int pivo;
    //printf("| i %d | f %d \n", inicio, fim);

    if(fim > inicio){
        pivo = particiona(v, inicio, fim);
        imprimirVet(v, 7);
        quickSort(v, inicio, pivo-1);
        quickSort(v, pivo+1, fim);
    }
    else return;
}


void criaHeap(int *v, int pai, int fim){
    int aux = v[pai];
    int filho = 2 * pai + 1;
    while(filho <= fim){
        if(filho < fim){
            if(v[filho] < v[filho + 1]){
                filho++;
            }
        }
        if(aux < v[filho]){
            v[pai] = v[filho];
            pai = filho;
            filho = 2 * pai + 1;
        }else{
            filho = fim + 1;
        }
    }
    v[pai] = aux;
}


void heapSort(int *v, int n){
    int i, aux;
    for(i=(n-1)/2; i>=0; i--){
        criaHeap(v, i, n-1);
    }

    for(i = n-1; i>=1; i--){
        aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        criaHeap(v, 0, i-1);
    }
}


#define TAM 5    //tamanho do balde
struct balde{
    int qtd;
    int valores[TAM]
};
void bucketSort(int *v, int N){
    int i,j,maior,menor,nroBaldes,pos;
    struct balde *bd;
    //acha maior e menor valor
    maior = menor = v[0];
    for (i=1; i<N; i++){
        if(v[i] > maior) maior = v[i];
        if(v[i] < menor) menor = v[i];
    }
    //inicializa baldes
    nroBaldes = (maior - menor) / TAM + 1;
    printf("Maior %d\nMenor %d\nNumero de Baldes: %d\n", maior, menor, nroBaldes);
    bd = (struct balde*) malloc(nroBaldes * sizeof(struct balde));
    for(i=0; i<nroBaldes; i++)
        bd[i].qtd = 0;
    //distribui os valores nos baldes
    for(i=0; i<N; i++){
        pos = (v[i] - menor)/TAM;
        bd[pos].valores[bd[pos].qtd] = v[i];
        bd[pos].qtd++;
    }

    //for (i=0; i<N; i++){
    //    imprimirVet(bd[i].valores, bd[i].qtd);
    //}

    //ordena baldes e coloca no array
    pos = 0;
    for(i = 0; i<nroBaldes; i++){
        insertionSort(bd[i].valores, bd[i].qtd);
        //imprimirVet(bd[i].valores, bd[i].qtd);
        for(j = 0; j<bd[i].qtd; j++){
            v[pos] = bd[i].valores[j];
            pos++;
        }
    }
    free(bd);
}


void radixSort(int *v, int n) {
    int i, *b, maior = v[0], exp = 1;

    b = (int *)calloc(n, sizeof(int));

    for (i = 0; i < n; i++) {
        if (v[i] > maior)
    	    maior = v[i];
    }

    while (maior/exp > 0) {
            printf("hiii\n");
        int bucket[10] = { 0 };
        //distribuindo os elementos
    	for (i = 0; i < n; i++)
    	    bucket[(v[i] / exp) % 10]++;
        //calculando a posição no vetor
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
        //ordenando conforme dígito menos significativo
    	for (i = n - 1; i >= 0; i--)
    	    b[--bucket[(v[i] / exp) % 10]] = v[i];
        //
    	for (i = 0; i < n; i++)
    	    v[i] = b[i];
        imprimirVet(v,n);
    	exp *= 10;
    }
    free(b);
}


int main(){

    int vet[10] = {5,2,4,7,9,10,1,3,8,6};
    //int vet[10] = {10,9,8,7,6,5,4,3,2,1};
    //int vet[7] = {23,4,67,-8,90,54,21};
    //int vet[7] = {23,4,17,8,29,14,21};
    //int vet[7] = {1,2,3,4,5,6,7};
    imprimirVet(vet, 10);
    printf("\n");

    //bubbleSort(vet, 10);
    //selectionSort(vet, 10);
    insertionSort(vet, 10);
    //mergeSort(vet, 0, 6);
    //quickSort(vet, 0, 6);
    //heapSort(vet, 7);
    //bucketSort(vet, 7);
    //radixSort(vet,7);
    //insertionSort_Decress(vet,10);
    printf("\n");
    imprimirVet(vet, 10);


}