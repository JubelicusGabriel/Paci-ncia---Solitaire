#ifndef CARTA_H_INCLUDED
#define CARTA_H_INCLUDED


#include <raylib.h>

#define NOME_NAIPE 10
#define TAMANHO_NOME_IMAGEM 30

typedef struct{
    int chave; //Chave identificadora da carta
    int valor; // valor da carta. Varia de 1-13
    int naipe; // naipe/suits da carta
    char imagemtxt[35]; // txt responsável pela identificação da imagem
    Texture2D imagem; // Textura para renderização na interface
    Rectangle hitBox; // Dimensões de hitbox da carta
    int sentido; //de costas (0) ou de frente (1);
}Carta;

typedef Carta Info;

#endif