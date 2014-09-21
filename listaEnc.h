/* 
 * File:   ListaEnc.h
 * Author: Fábio Tramasoli (0619132)
 * About: Fila Encadeada agnóstica a tipos.
 * 
 */

#define LISTAENC_VAZIA -1
#define LISTAENC_CHEIA 10
#define LISTAENC_OPERACAO_OK 0
#define LISTAENC_OPERACAO_ERR 1

typedef struct{
    void *content;
    void *next;
    void *previous;
}tListaEncItem;

typedef struct{
    tListaEncItem *head;
    tListaEncItem *tail;
    int size;
    int bytes;
}tListaEnc;

int inicializaListaEnc(tListaEnc *,int);
int finalizaListaEnc(tListaEnc *);
int vaziaListaEnc(tListaEnc *);
int cheiaListaEnc(tListaEnc *);
int inserirListaEnc(tListaEnc *,int pos,  void *);
int removerListaEnc(tListaEnc *,int pos, void*);
int posicaoListaEnc(tListaEnc *f, void *valor);
int elementoListaEnc(tListaEnc *f, int pos, void *valor);
int tamanhoListaEnc(tListaEnc *);
