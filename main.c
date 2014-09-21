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

int procurar (contato* info)
{
    int retorno, pos = posicaoListaEnc(tabela[pos],&info);
    retorno = elementoListaEnc(tabela[pos],pos,&info);
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
    /*
    valor = 1;
    pos = hash(valor);
    inserir(pos, valor);

    valor = 10;
    inserir( hash(valor), valor);

    valor = 11;
    pos = hash(valor);
    inserir(pos, valor);
    */
    
    //VARIÁVEIS AUXILIARES
    int ler,count;
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
                inserirListaEnc(tabela[hash(*aux)],1,aux);
                break;
            case 2:
                aux=malloc(sizeof(contato));
                printf("Informe o nome: ");
                fgets (aux->nome, sizeof(aux->nome), stdin);
                printf("Informe o telefone: ");
                fgets (aux->telefone, sizeof(aux->telefone), stdin);
                i=posicaoListaEnc(tabela[hash(*aux)],aux);
                free(aux);
                if(i!=LISTAENC_OPERACAO_ERR)
                    printf("Seu item está em tabela[%d], índice %d da lista.\n",hash(*aux),i);
                else
                    printf("Seu item não foi encontrado.\n");
                break;
            case 3:
                aux=malloc(sizeof(contato));
                printf("Informe o nome: ");
                fgets (aux->nome, sizeof(aux->nome), stdin);
                printf("Informe o telefone: ");
                fgets (aux->telefone, sizeof(aux->telefone), stdin);
                i=posicaoListaEnc(tabela[hash(*aux)],aux);
                
                if(i!=LISTAENC_OPERACAO_ERR) {
                    printf("Seu item estava em tabela[%d], índice %d da lista.\n",hash(*aux),i);
                    removerListaEnc(tabela[hash(*aux)],i,aux);
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