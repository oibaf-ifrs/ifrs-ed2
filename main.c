#include <stdio.h>
#include <stdlib.h>

#define OK   1
#define ERRO 0
#define PRE_ORDER 0
#define IN_ORDER 1
#define POS_ORDER 2

// Crie mais 5 funções para mostrar a árvore das formas:In-order, Pre-order, Pos-Order


typedef struct def_arvore
        {
           int  Dado;
           struct def_arvore    *FilhoEsq;
           struct def_arvore    *FilhoDir;
           struct def_arvore    *Pai;
        }  tipo_arvore;

tipo_arvore *nodo=NULL;


int insere_arv (int Dado)
{
   tipo_arvore *novo, *aux, *temp;
 
   novo = (tipo_arvore *) malloc (sizeof (tipo_arvore) );

   if ( novo == NULL ) return (ERRO);

   novo -> Dado = Dado;
   novo -> FilhoEsq = NULL;
   novo -> FilhoDir = NULL;
   aux = nodo;

   while ( aux != NULL )     /* Acha o ponto onde vai inserir */
   {

      temp = aux;
      if ( Dado > (aux -> Dado) )
         aux = aux -> FilhoDir;
      else
         aux = aux -> FilhoEsq;
   }

   if ( aux == nodo)
   {
      novo -> Pai = NULL;
      nodo = novo;
   }
   else
   {
      novo -> Pai = temp;
      if (Dado > temp->Dado)
          temp -> FilhoDir = novo;
      else
          temp -> FilhoEsq = novo;
   }
   return(OK);
}

int exclui_arv (int Dado,tipo_arvore **nodo )
{
    tipo_arvore *aux, *temp, **refPai=NULL;
    aux = *nodo;
    temp=aux->Pai;
    while ( aux != NULL && aux->Dado != Dado)
    {
    temp = aux;
    if ( Dado > (aux-> Dado) )
        aux = aux -> FilhoDir;
    else
        aux = aux -> FilhoEsq;
    }

    if (aux != NULL) {
        //ATACA CASOS DE SER FOLHA OU TER SOMENTE UM FILHO
        if ( aux->FilhoEsq == NULL || aux->FilhoDir == NULL )
        {
            //Atualiza PAI
            if(temp!=NULL) {
                refPai=(temp->FilhoDir == aux)?&(temp->FilhoDir):&(temp->FilhoEsq);
                *refPai=(aux->FilhoDir == NULL)?aux->FilhoEsq:aux->FilhoDir;
            }
            //Atualiza FILHO
            if(refPai!=NULL && *refPai!=NULL)
                (*refPai)->Pai=((*refPai)->Pai!=NULL)?(*refPai)->Pai->Pai:NULL;
            if(aux==*nodo) {
                *nodo=(aux->FilhoDir == NULL)?aux->FilhoEsq:aux->FilhoDir;
                if(*nodo!=NULL)
                    (*nodo)->Pai=NULL;
            }
            free(aux);
        }
        //ATACA CASOS DE TER DOIS FILHOS
        else
        {
            for(temp=aux->FilhoEsq;temp->FilhoDir!=NULL;temp=temp->FilhoDir);
            aux->Dado=temp->Dado;
            temp->Dado=Dado;
            exclui_arv(Dado,&temp);
        }
        return(OK);
    }
   return(ERRO);
}

void exibePRE(tipo_arvore *Arvore)
{    
    if ( Arvore != NULL )
    {
        printf ("%d\n", Arvore -> Dado);
        exibePRE( Arvore -> FilhoEsq );
        exibePRE( Arvore -> FilhoDir);
    }
}

void exibeIN(tipo_arvore *Arvore)
{    
    if ( Arvore != NULL )
    {
        exibeIN( Arvore -> FilhoEsq );
        printf ("%d\n", Arvore -> Dado);
        exibeIN( Arvore -> FilhoDir);
    }
}

void exibePOS(tipo_arvore *Arvore)
{    
    if ( Arvore != NULL )
    {
        exibePOS( Arvore -> FilhoEsq );
        exibePOS( Arvore -> FilhoDir);
        printf ("%d\n", Arvore -> Dado);
    }
}

void exibe(tipo_arvore *Arvore, int order) {
    switch(order) {
        case PRE_ORDER:
            exibePRE(Arvore);
            break;
        case POS_ORDER:
            exibePOS(Arvore);
            break;
        default:
            exibeIN(Arvore);
            break;
    }
}

main ( )
{
    int result;
    result = insere_arv(30);
    result = insere_arv(50);
    result = insere_arv(40);
    result = insere_arv(60);
    result = insere_arv(42);
    result = insere_arv(47);
    result = insere_arv(45);
    result = insere_arv(44);
    result = insere_arv(46);
    result = insere_arv(20);
    result = insere_arv(10);
    result = insere_arv(25);
    if ( result==OK )
        printf("Insercao sem problemas\n");
    else
        printf(">> Erro na insercao!\n");
    /*
    printf("*** PRE ORDER\n");
    exibe(nodo,PRE_ORDER);
    
    printf("*** POS ORDER\n");
    exibe(nodo,POS_ORDER);
    */
    printf("*** IN ORDER\n");
    exibe(nodo,IN_ORDER);
    //excluir
    //exclui ok
    //exclui_arv(40);
    //nao exclui
    exclui_arv(50,&nodo);
    exclui_arv(40,&nodo);
    exclui_arv(30,&nodo);
    exclui_arv(20,&nodo);
    exclui_arv(10,&nodo);
    exclui_arv(25,&nodo);
    
    //plus plus (limpa)
    /*
    exclui_arv(60,&nodo);
    exclui_arv(42,&nodo);
    exclui_arv(47,&nodo);
    exclui_arv(45,&nodo);
    exclui_arv(44,&nodo);
    exclui_arv(46,&nodo);
    */
    /*
    printf("*** IN ORDER\n");
    exibe(nodo,IN_ORDER);
    printf("*** POS ORDER\n");
    exibe(nodo,POS_ORDER);
    */
    printf("*** PRE ORDER\n");
    exibe(nodo,IN_ORDER);
    printf("Pressione uma tecla para sair...\n");
    getchar();
    return(EXIT_SUCCESS);
}
