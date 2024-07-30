#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include "baralho.h"


void menu(){

    ListaCircEnc *baralho;
        NodoLEnc *carta;
        const int screenWidth = 1600;
        const int screenHeight = 1000;

        InitWindow(screenWidth, screenHeight, "Trabalho Final - Solitaire");


        baralho = cria_baralho();
        carta = baralho->prim;
        SetTargetFPS(60);

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);


            int posX = 50;
            int posY = 50;


            do
            {
                DrawTexture(carta->info.Imagem_carta, posX, posY, WHITE);
                carta = carta->prox;
                posX = posX+15;
                posY = posY+10;
            }
            while(carta != baralho->fim);

        //Informa��es referentes as imagens das cartas

        //Carta 01
        Image carta1 = LoadImage("cartas/1_of_clubs.png");
        ImageResize(&carta1, 300, 420);
        Texture2D imagem1 = LoadTextureFromImage(carta1);
        UnloadImage(carta1);

        //Carta 02 [Teste]
        Image carta2 = LoadImage("cartas/1_of_diamonds.png");
        ImageResize(&carta2, 300, 420);
        Texture2D imagem2 = LoadTextureFromImage(carta2);
        UnloadImage(carta2);

            //cartas
            DrawTexture(imagem1, 100, 290, RAYWHITE);   
            DrawTexture(imagem2, 1200, 290, RAYWHITE);

            //Blocos
        
            DrawRectangle(600, 100, 400, 90, WHITE);

            DrawRectangle(600, 290, 400, 80, WHITE);
            DrawRectangle(600, 410, 400, 80, WHITE);
            DrawRectangle(600, 530, 400, 80, WHITE);
            DrawRectangle(600, 650, 400, 80, WHITE);
            DrawRectangle(600, 770, 400, 80, WHITE);
            
            DrawRectangle(500, 910, 600, 40, WHITE);


            //Texto
            DrawText("SOLITAIRE", 630, 120, 60, GREEN);

            DrawText("Novo Jogo", 680, 310, 45, GREEN); 
            DrawText("Carregar Jogo", 630, 430, 45, GREEN); 
            DrawText("Credits", 680, 550, 45, GREEN); 
            DrawText("Cartas", 690, 670, 45, GREEN); 
            DrawText("Sair", 710, 790, 45, GREEN); 


            DrawText("Gabriel, Gustavo, Murilo", 600, 915, 30, GREEN); 
            


        
        

            EndDrawing();
        }


        CloseWindow();
}