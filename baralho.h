#ifndef BARALHO_H_INCLUDED
#define BARALHO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>

#define NOME_NAIPE 10

typedef struct{
    int chave;
    int valor;
    char naipe[NOME_NAIPE];
    char imagemtxt[35];
    Texture2D imagem;
    int sentido; //de costas (0) ou de frente (1);
}Carta;

typedef Carta Info;

typedef struct nodoLEnc{
    Info info;
    struct nodoLEnc *prox;
    struct nodoLEnc *ant;
}NodoLEnc;

typedef struct{
    struct nodoLEnc *prim;
}ListaCircEnc;

typedef NodoLEnc NodoPEnc;

typedef struct pilhaEnc{
   NodoPEnc *topo;
} PilhaEnc;

typedef NodoLEnc NodoFEnc;

typedef struct filaEnc{
   NodoFEnc *ini;
   NodoFEnc *fim;
} FilaEnc;

// Funcao que cria uma fila
FilaEnc* criaFilaEnc();

// Funcao que destroi uma fila
void destroiFilaEnc(FilaEnc *fila);

// Funcao que insere um elemento na fila
void enfileiraFilaEnc(FilaEnc *fila, Info info);

// Funcao que remove um elemento da fila
Info desenfileiraFilaEnc(FilaEnc *fila);

// Funcao que determina se uma fila eh vazia
int vaziaFilaEnc(FilaEnc* fila);

// Funcao que cria uma pilha
PilhaEnc* criaPilhaEnc();

// Funcao que destroi uma pilha
void destroiPilhaEnc(PilhaEnc *pilha);

// Funcao que insere um elemento na pilha
void empilhaPilhaEnc(PilhaEnc *pilha, Info info);

// Funcao que remove um elemento da pilha
Info desempilhaPilhaEnc(PilhaEnc *pilha);

// Funcao que determina se uma pilha eh vazia
int vaziaPilhaEnc(PilhaEnc* pilha);

// Funcao que cria uma lista
ListaCircEnc* criaListaCircEnc();

// Funcao que destroi uma lista
void destroiListaCircEnc(ListaCircEnc *lista);

// Funcao que imprime todos os nodos de uma lista
void imprimeListaCircEnc(ListaCircEnc *lista);

// Funcao que insere um nodo no inicio de uma lista
int insereInicioListaCircEnc(ListaCircEnc *lista, Info info);

// Fun��o que insere um nodo no fim de uma lista
int insereFimListaCircEnc(ListaCircEnc *lista, Info info);

// Funcao que resgata um nodo com uma informacao de uma lista
NodoLEnc* buscaInfoListaCircEnc(ListaCircEnc* lista, int chave);

ListaCircEnc* cria_baralho();

ListaCircEnc* embaralha_baralho(ListaCircEnc* baralho);

int insereFilaViradoCima(FilaEnc *fila, Info info);

int inserePilhaViradoBaixo(PilhaEnc *pilha, Info info);

int desenhaCartasColuna(FilaEnc *fila, PilhaEnc *pilha, int coluna, int sentido, float multi_res, int numBaixo);

#endif // BARALHO_H_INCLUDED
