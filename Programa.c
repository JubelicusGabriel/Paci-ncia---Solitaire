#include "baralho.h"
#include "raylib.h"
#include "opcoes.h"


int main(void)
{
    iniciaMenu();
    return 0;
}

    /*const int screenWidth = 1000;
    const int screenHeight = 650;
    InitWindow(screenWidth, screenHeight, "Jogo Paciencia - trabalho final");

    //Informa��es referentes as imagens das cartas
    Image carta = LoadImage("cartas/2_of_clubs.png");
    ImageResize(&carta, (carta.width - carta.width * 0.8), (carta.height - carta.height * 0.8));
    Texture2D imagem = LoadTextureFromImage(carta);
    UnloadImage(carta);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);


        DrawTexture(imagem, screenWidth/2 - imagem.width/2, screenHeight/2 - imagem.height/2, WHITE);

        DrawText("Jogo Paciencia", 190, 200, 20, RED);

        EndDrawing();
    }


    CloseWindow();*/