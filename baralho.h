#ifndef BARALHO_H_INCLUDED
#define BARALHO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>

#define NOME_NAIPE 10
#define TAMANHO_NOME_IMAGEM 30

typedef struct
{
    int chave;
    int valor;
    char naipe[NOME_NAIPE];
    int sentido; //de costas (0) ou de frente (1);

    Texture2D Imagem_carta;


} Carta;

typedef Carta Info;

typedef struct nodoLEnc
{
    Info info;
    struct nodoLEnc *prox;
    struct nodoLEnc *ant;
} NodoLEnc;

typedef struct
{
    struct nodoLEnc *prim;
    struct nodoLEnc *fim;
} ListaCircEnc;

// Funcao que cria uma lista
ListaCircEnc* criaListaCircEnc();

// Funcao que destroi uma lista
void destroiListaCircEnc(ListaCircEnc *lista);

// Funcao que insere um nodo no inicio de uma lista
int insereInicioListaCircEnc(ListaCircEnc *lista, Info info);

// Função que insere um nodo no fim de uma lista
int insereFimListaCircEnc(ListaCircEnc *lista, Info info);

void carrega_imagem_cartas(ListaCircEnc* baralho);

ListaCircEnc* cria_baralho();



#endif // BARALHO_H_INCLUDED
