#ifndef CARTA_H_INCLUDED
#define CARTA_H_INCLUDED


#include <raylib.h>

#define NOME_NAIPE 10
#define TAMANHO_NOME_IMAGEM 30

typedef struct {
    int chave; //Identificador da carta
    int valor; // valor da carta. Varia de 1-13
    char naipe[NOME_NAIPE];
    int sentido; // de costas (0) ou de frente (1);
    int seq_compat; // Bool, sequência de cartas na pilha e compativel ou nao
    Vector2 posicaoCarta;
    Texture2D Imagem_carta;
} Carta;

typedef Carta Info;

#endif // CARTA_H_INCLUDED
