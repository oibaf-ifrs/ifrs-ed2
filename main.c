#include <stdlib.h>
#include "listaEnc.h"

#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif

#define TAM 10

tListaEnc *tabela[TAM];

void inserir (int pos, int n)
{
    inserirListaEnc(tabela[pos],3,&n);
}


int hash(int num){
    return num%TAM;
}


main(){
    int pos,i,valor;
    tListaEncItem *tmp;
    for( i=0; i < TAM; i++) {
        tabela[i] = malloc(sizeof(tListaEnc));
        inicializaListaEnc(tabela[i],sizeof(int));
    }

    valor = 1;
    pos = hash(valor);
    inserir(pos, valor);

    valor = 10;
    inserir( hash(valor), valor);

    valor = 11;
    pos = hash(valor);
    inserir(pos, valor);

    for( i=0; i < TAM; i++) {
        printf("Conteúdo da lista em %d: ",i);
        for(tmp=tabela[i]->head;tmp!=NULL;tmp=tmp->next) {
            valor=*((int *)(tmp->content));
            printf("%d,",valor);
        }
        printf("\n");
        finalizaListaEnc(tabela[i]);
        free(tabela[i]);
    }
   
    if(PAUSE==1)
        system("pause");
    else
        system("read -p \"Pressione enter para sair\" saindo");
    return(0); 
   
}