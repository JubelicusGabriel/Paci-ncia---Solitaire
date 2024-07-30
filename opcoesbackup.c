#include "baralho.h"
#include "opcoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"

void iniciaMenu() {
    //opcao = qual tela de jogo.
    int opcao;

    //Raylib
    


    //Terminal
    while(opcao>= 0 && opcao<=4){
        printf("INICIAR JOGO [1]\nCARREGAR JOGO [2]\nCREDITOS [3]\nSAIR DO JOGO [4]\n");
        scanf("%i", &opcao);
    }
    
    


    //Enviando para a tela responsável
    if (opcao == 1) {
        novoJogo();
    }
    else if (opcao == 4) {
        sair();
    }
    else iniciaMenu();
}

void novoJogo() {
    int opcao_res = 1;
    float multi_res = 1.0;
    printf("Qual sua resolução de preferência?\n");
    printf("[1]640x400 [2]960x600 [3]1280x800 [4]1600x1000\n");
    scanf("%d", &opcao_res);

    switch(opcao_res) {
        case 1:
            printf("Resolução 640x400\n");
            multi_res = 1.0;
            break;
        case 2:
            printf("Resolução 960x600\n");
            multi_res = 1.5;
            break;
        case 3:
            printf("Resolução 1280x800\n");
            multi_res = 2.0;
            break;
        case 4:
            printf("Resolução 1600x1000\n");
            multi_res = 2.5;
            break;
        default:
            printf("Opção inválida!\n");
            novoJogo();
    }


    ListaCircEnc *baralho = cria_baralho();
    ListaCircEnc *baralho_embaralhado = embaralha_baralho(baralho);
    
    const int screenWidth = ((int)640*multi_res);
    const int screenHeight = ((int)400*multi_res);
    InitWindow(screenWidth, screenHeight, "Paciência - Solitaire");

    //pilhas superiores (onde os naipes devem ser organizados)
    PilhaEnc *pilha_copas = criaPilhaEnc();
    PilhaEnc *pilha_ouro = criaPilhaEnc();
    PilhaEnc *pilha_paus = criaPilhaEnc();
    PilhaEnc *pilha_espadas = criaPilhaEnc();

    //colunas
    FilaEnc *coluna1_cima = criaFilaEnc();

    FilaEnc *coluna2_cima = criaFilaEnc();
    PilhaEnc *coluna2_baixo = criaPilhaEnc();

    FilaEnc *coluna3_cima = criaFilaEnc();
    PilhaEnc *coluna3_baixo = criaPilhaEnc();

    FilaEnc *coluna4_cima = criaFilaEnc();
    PilhaEnc *coluna4_baixo = criaPilhaEnc();

    FilaEnc *coluna5_cima = criaFilaEnc();
    PilhaEnc *coluna5_baixo = criaPilhaEnc();

    FilaEnc *coluna6_cima = criaFilaEnc();
    PilhaEnc *coluna6_baixo = criaPilhaEnc();

    FilaEnc *coluna7_cima = criaFilaEnc();
    PilhaEnc *coluna7_baixo = criaPilhaEnc();

    //monte de compras
    ListaCircEnc *baralho_compras = criaListaCircEnc();
    NodoLEnc *carta = baralho_embaralhado->prim;
    //inserindo cartas em cada coluna
    for (int i =0; i<28; i++) {
        if (i == 0){
            insereFilaViradoCima(coluna1_cima, carta->info);
        }
        else if (i == 1) {
            inserePilhaViradoBaixo(coluna2_baixo, carta->info);
        }
        else if (i == 2) {
            insereFilaViradoCima(coluna2_cima, carta->info);
        }
        else if (i <= 4) {
            inserePilhaViradoBaixo(coluna3_baixo, carta->info);
        }
        else if (i == 5) {
            insereFilaViradoCima(coluna3_cima, carta->info);
        }
        else if (i <= 8) {
            inserePilhaViradoBaixo(coluna4_baixo, carta->info);
        }
        else if (i == 9) {
            insereFilaViradoCima(coluna4_cima, carta->info);
        }
        else if (i <= 13) {
            inserePilhaViradoBaixo(coluna5_baixo, carta->info);
        }
        else if (i == 14) {
            insereFilaViradoCima(coluna5_cima, carta->info);
        }
        else if (i <= 19) {
            inserePilhaViradoBaixo(coluna6_baixo, carta->info);
        }
        else if (i == 20) {
            insereFilaViradoCima(coluna6_cima, carta->info);
        }
        else if (i <= 26) {
            inserePilhaViradoBaixo(coluna7_baixo, carta->info);
        }
        else insereFilaViradoCima(coluna7_cima, carta->info);

        carta = carta->prox;
    }

    

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GREEN);

        //Desenhando overlays deck + naipes
        //Verificar se tá de mau gosto, tô com opiniões mistas.

        
            //Esquerda
        DrawRectangle(0, 0, 70*multi_res, 400*multi_res, DARKGREEN);
        DrawRectangleGradientH(70 * multi_res, 0, 10*multi_res, 400*multi_res, DARKGREEN, GREEN);

            //Direita
        DrawRectangle(570*multi_res, 0, 70*multi_res, 400*multi_res, DARKGREEN);
        DrawRectangleGradientH(560 * multi_res, 0, 10*multi_res, 400*multi_res, GREEN, DARKGREEN);

        //desenhando cartas na tela

        int numBaixo = 0; // numero de cartas virada para baixo em cada coluna
        numBaixo = desenhaCartasColuna(coluna1_cima, NULL, 1, 1, multi_res, numBaixo);

        numBaixo = desenhaCartasColuna(NULL, coluna2_baixo, 2, 0, multi_res, numBaixo);
        numBaixo = desenhaCartasColuna(coluna2_cima, NULL, 2, 1, multi_res, numBaixo);

        numBaixo = desenhaCartasColuna(NULL, coluna3_baixo, 3, 0, multi_res, numBaixo);
        numBaixo = desenhaCartasColuna(coluna3_cima, NULL, 3, 1, multi_res, numBaixo);

        numBaixo = desenhaCartasColuna(NULL, coluna4_baixo, 4, 0, multi_res, numBaixo);
        numBaixo = desenhaCartasColuna(coluna4_cima, NULL, 4, 1, multi_res, numBaixo);

        numBaixo = desenhaCartasColuna(NULL, coluna5_baixo, 5, 0, multi_res, numBaixo);
        numBaixo = desenhaCartasColuna(coluna5_cima, NULL, 5, 1, multi_res, numBaixo);

        numBaixo = desenhaCartasColuna(NULL, coluna6_baixo, 6, 0, multi_res, numBaixo);
        numBaixo = desenhaCartasColuna(coluna6_cima, NULL, 6, 1, multi_res, numBaixo);

        numBaixo = desenhaCartasColuna(NULL, coluna7_baixo, 7, 0, multi_res, numBaixo);
        numBaixo = desenhaCartasColuna(coluna7_cima, NULL, 7, 1, multi_res, numBaixo);


        EndDrawing();

        /*for (int i=0; i<52; i++) {
            Image cartaImagem = LoadImage(carta->info.imagemtxt);
            ImageResize(&cartaImagem, 50*multi_res, 70*multi_res);
            carta->info.imagem = LoadTextureFromImage(cartaImagem);
            UnloadImage(cartaImagem);
            int j = i/7;
            int k = i%7;

            DrawTexture(carta->info.imagem, (100+ k*65)*multi_res, (10+ j*20)*multi_res, WHITE);
            carta = carta->prox;
        }
        DrawText("Jogo Paciencia", 190, 200, 20, RED);

        EndDrawing();*/
    }

    CloseWindow();


    destroiListaCircEnc(baralho);
    destroiListaCircEnc(baralho_embaralhado);
    destroiListaCircEnc(baralho_compras);
    destroiPilhaEnc(pilha_copas);
    destroiPilhaEnc(pilha_ouro);
    destroiPilhaEnc(pilha_espadas);
    destroiPilhaEnc(pilha_paus);
    destroiPilhaEnc(coluna2_baixo);
    destroiPilhaEnc(coluna3_baixo);
    destroiPilhaEnc(coluna4_baixo);
    destroiPilhaEnc(coluna5_baixo);
    destroiPilhaEnc(coluna6_baixo);
    destroiPilhaEnc(coluna7_baixo);
    destroiFilaEnc(coluna1_cima);
    destroiFilaEnc(coluna2_cima);
    destroiFilaEnc(coluna3_cima);
    destroiFilaEnc(coluna4_cima);
    destroiFilaEnc(coluna5_cima);
    destroiFilaEnc(coluna6_cima);
    destroiFilaEnc(coluna7_cima);
}

void carregarJogo() {

}

void creditos() {
    printf("TODOS OS DIREITOS RESERVADOS\nGABRIEL\nGUSTAVO\nMURILO");
}

void sair() {
    abort();
}