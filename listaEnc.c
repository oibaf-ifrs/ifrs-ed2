/* 
 * File:   ListaEnc.c
 * Author: Fábio Tramasoli (0619132)
 * About: Lista Encadeada agnóstica a tipos.
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "listaEnc.h"

int inicializaListaEnc(tListaEnc *f, int bytes) {
    if(f!=NULL) {
        f->head=f->tail=NULL;
        f->bytes=bytes;
        return LISTAENC_OPERACAO_OK;
        f->size=0;
    }
    return LISTAENC_OPERACAO_ERR;
}

int finalizaListaEnc(tListaEnc *f) {
    char *aux = malloc(f->bytes);
    while(removerListaEnc(f,1,aux)==LISTAENC_OPERACAO_OK) {
    }
    free(aux);
    return LISTAENC_OPERACAO_OK;
}

int vaziaListaEnc(tListaEnc *f) {
    if (f->head==NULL)
        return LISTAENC_VAZIA;
    else
        return LISTAENC_OPERACAO_OK;
}

int cheiaListaEnc(tListaEnc *f) {
    return LISTAENC_OPERACAO_OK;
}

int inserirListaEnc(tListaEnc *f, int pos, void *valor) {
    if(f!=NULL && pos>0) {
        tListaEncItem *newVal = malloc(sizeof(tListaEncItem));
        newVal->content = malloc(f->bytes);
        memcpy(newVal->content, valor, f->bytes);
        newVal->next=newVal->previous=NULL;
        if(vaziaListaEnc(f)==LISTAENC_VAZIA)
            f->head=f->tail=newVal;
        else {
            int count;
            tListaEncItem *aux=f->head;
            for (count=1;count<pos&&aux->next!=NULL;count++)
                aux=aux->next;
            if(pos==1) {
                newVal->next=aux;
                aux->previous=newVal;
                f->head=newVal;
            }
            else {
                newVal->previous=aux;
                newVal->next=aux->next;
                aux->next=newVal;
                if(newVal->next!=NULL)
                    ((tListaEncItem*)(newVal->next))->previous=newVal;
                if(count==tamanhoListaEnc(f)+1)
                f->tail=newVal;
            }   
        }
        return LISTAENC_OPERACAO_OK;
    }
    return LISTAENC_OPERACAO_ERR;
}

int removerListaEnc(tListaEnc *f, int pos, void *content) {
    if (vaziaListaEnc(f)==LISTAENC_VAZIA)
        return LISTAENC_VAZIA;
    else {
        int count;
        tListaEncItem *aux=f->head,*tmp;
        for (count=1;count<pos&&aux->next!=NULL;count++)
            aux=aux->next;
        if(aux==NULL)
            return LISTAENC_OPERACAO_ERR;
        memcpy(content,aux->content, f->bytes);
        if(f->head==aux)
            f->head=aux->next;
        if(f->tail==aux)
            f->tail=aux->previous;
        if(aux->next!=NULL)
            ((tListaEncItem *)aux->next)->previous=aux->previous;
        if(aux->previous!=NULL)
            ((tListaEncItem *)aux->previous)->next=aux->next;
        free(aux->content);
        free(aux);
        return LISTAENC_OPERACAO_OK;
    }
    return LISTAENC_OPERACAO_ERR;
}

int posicaoListaEnc(tListaEnc *f, void *valor) {
    if (vaziaListaEnc(f)==LISTAENC_VAZIA)
        return LISTAENC_VAZIA;
    else {
        int count=0,tamanho=tamanhoListaEnc(f), diff=1;
        tListaEncItem *aux=f->head;
        while(count<tamanho && diff && aux!=NULL) {
            diff=memcmp(valor,aux->content,f->bytes);
            aux=aux->next;
            count++;
        }
        if(aux==NULL && diff!=0)
            return LISTAENC_OPERACAO_ERR;
        memcpy(valor,&count, f->bytes);
        return LISTAENC_OPERACAO_OK;
    }
    return LISTAENC_OPERACAO_ERR;
}

int elementoListaEnc(tListaEnc *f, int pos, void *valor) {
    if (vaziaListaEnc(f)==LISTAENC_VAZIA)
        return LISTAENC_VAZIA;
    else {
        tListaEncItem *aux=f->head;
        int count;
        for (count=1;count<pos&&aux!=NULL;count++)
            aux=aux->next;
        if(aux==NULL)
            return LISTAENC_OPERACAO_ERR;
        memcpy(valor,aux->content, f->bytes);
        return LISTAENC_OPERACAO_OK;
    }
    return LISTAENC_OPERACAO_ERR;
}

int tamanhoListaEnc(tListaEnc * f){
    if(vaziaListaEnc(f)==LISTAENC_VAZIA)
        return 0;
    unsigned int retorno=0;
    tListaEncItem *go;
    for(go=f->head;go!=NULL;go=go->next)
        retorno++;
    return retorno;
}
