#include <stdio.h>
#include <stdlib.h>
#include "listaEnc.h"

#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif

#define TAM 10

typedef struct contato {
    char nome[100];
    char telefone[50];
} contato;

tListaEnc *tabela[TAM];

int inserir (int pos, int n)
{
    int retorno = inserirListaEnc(tabela[pos],3,&n);
    return retorno;
}

int procurar (int pos, contato* info)
{
    int retorno=LISTAENC_OPERACAO_ERR;
    if (vaziaListaEnc(tabela[pos])==LISTAENC_VAZIA)
        retorno=LISTAENC_VAZIA;
    else {
        int count=0,tamanho=tamanhoListaEnc(tabela[pos]), diff=1;
        tListaEncItem *aux=tabela[pos]->head;
        while(count<tamanho && diff && aux!=NULL) {
            diff=strcmp(info->nome,((contato*)aux->content)->nome);
            aux=aux->next;
            count++;
        }
        if(!diff)
            retorno=count;
    }
    return retorno;
}

int hash(contato info){
    int retorno=0,count;
    for(count=0;info.nome[count];count++)
        retorno+=info.nome[count];
    return retorno%TAM;
}


main(){
    int pos,i,valor;
    tListaEncItem *tmp;
    for( i=0; i < TAM; i++) {
        tabela[i] = malloc(sizeof(tListaEnc));
        inicializaListaEnc(tabela[i],sizeof(contato));
    }
    
    //VARIÁVEIS AUXILIARES
    int ler,count,tmphash;
    contato *aux;
    //MENUS
    do {
        printf("== MENU PRINCIPAL\n");
        printf("-->  1) Inserir contato\n");
        printf("-->  2) Consultar contato\n");
        printf("-->  3) Excluir contato\n");
        printf("-->  4) Exibir fator de carga\n");
        printf("-->  5) Exibir quantidade de elementos\n");
        printf("--> 99) Sair\n");
        scanf("%d",&ler);
        getc(stdin);
        switch(ler) {
            case 1:
                aux=malloc(sizeof(contato));
                printf("Informe o nome: ");
                fgets (aux->nome, sizeof(aux->nome), stdin);
                printf("Informe o telefone: ");
                fgets (aux->telefone, sizeof(aux->telefone), stdin);
                tmphash=hash(*aux);
                inserirListaEnc(tabela[tmphash],1,aux);
                break;
            case 2:
                aux=malloc(sizeof(contato));
                printf("Informe o nome: ");
                fgets (aux->nome, sizeof(aux->nome), stdin);
                tmphash=hash(*aux);
                i=procurar(tmphash,aux);
                free(aux);
                if(i!=LISTAENC_OPERACAO_ERR)
                    printf("Seu item está em tabela[%d], índice %d da lista.\n",tmphash,i);
                else
                    printf("Seu item não foi encontrado.\n");
                break;
            case 3:
                aux=malloc(sizeof(contato));
                printf("Informe o nome: ");
                fgets (aux->nome, sizeof(aux->nome), stdin);
                tmphash=hash(*aux);
                i=procurar(hash(*aux),aux);
                if(i!=LISTAENC_OPERACAO_ERR) {
                    printf("Seu item estava em tabela[%d], índice %d da lista.\n",tmphash,i);
                    removerListaEnc(tabela[tmphash],i,aux);
                }
                else
                    printf("Seu item não foi encontrado.\n");
                free(aux);
                break;
            case 4:
                count=0;
                for( i=0; i < TAM; i++) {
                    count+=tamanhoListaEnc(tabela[i]);
                }
                printf("Fator de carga: %.2f\n",(float)count/TAM);
                break;
            case 5:
                count=0;
                for( i=0; i < TAM; i++) {
                    count+=tamanhoListaEnc(tabela[i]);
                }
                printf("Quantidade de elementos indexados: %d\n",count);
                break;
        }
    }while(ler!=99);
    printf("Até logo! \\o/\n");
    printf("@AUTHOR: Fábio B. Tramasoli - IFRS POA - 0619132\n");
    printf("copyleft 2014 - https://github.com/tramasoli/ed2");

    for( i=0; i < TAM; i++) {
        finalizaListaEnc(tabela[i]);
        free(tabela[i]);
    }
    return(0);
   
}