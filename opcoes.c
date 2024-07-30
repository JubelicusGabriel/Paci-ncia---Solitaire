#include "baralho.h"
#include "opcoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"

    /*
        Global, utilizada por todas as funcões. Se acharem que tem problema, só avisar que mudamos
        A implementação
    */
    float multi_res = 1.0;


void iniciaMenu() {
    //opcao = qual tela de jogo.
    int opcao = 0;


    //Dando load na fonte
    Font fontMenu = LoadFont("resources/coolvetica_rg.otf");
      //Verificação se a fonte falhou ao carregar (Obrigado StackOverflow.)
    if (fontMenu.texture.id == 0){
        printf("Falha ao carregar fonte!\n");
        return;
    }
    
    int opcao_res = 0;
    while(opcao_res == 0){
        
        
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
                multi_res = 1.0;
                opcao_res = 0;
        }

    }
    //Terminal
    while(opcao < 1 || opcao > 4){
        printf("INICIAR JOGO [1]\nCARREGAR JOGO [2]\nCREDITOS [3]\nSAIR DO JOGO [4]\n");
        scanf("%i", &opcao);
    }

    

    //Raylib 

    //Setando a resolução do programa
    const int screenWidth = ((int)640*multi_res);
    const int screenHeight = ((int)400*multi_res);

    //Inicializando as texturas antes de SetTargetFPS
        //CARTA 01
    Image carta_menu01 = LoadImage("cartas/1_of_clubs.png");

    //Mesma verificação anterior mas agora pra carta.
    if (carta_menu01.data == NULL) {
        printf("Erro ao carregar a imagem 1_of_clubs.png");
        return;
    }

    
    ImageResize(&carta_menu01, (int)(100 * multi_res), (int)(140 * multi_res)); //Pra garantir tô colocando casting
    Texture2D textcarta_menu01 = LoadTextureFromImage(carta_menu01);
    UnloadImage(carta_menu01); //Unload na imagem pq só precisa da textura

        //CARTA 02
    Image carta_menu02 = LoadImage("cartas/1_of_diamonds.png");
    //Mesma verificação
    if (carta_menu02.data == NULL) {
        printf("Erro ao carregar a imagem 1_of_diamonds.png");
        return;
    }

    ImageResize(&carta_menu02, (int)(100 * multi_res), (int)(140 * multi_res));
    Texture2D textcarta_menu02 = LoadTextureFromImage(carta_menu02);
    UnloadImage(carta_menu02); //Unload na imagem pq só precisa da textura

    //PRINCIPAL - MENU

    InitWindow(screenWidth, screenHeight, "Paciência - Solitaire");

    SetTargetFPS(30); //Testando para a implementação nos menus.
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GREEN);

        /*PARA MUDAR O TAMANHO DA FONTE
        Alterar os valores que estão no lugar de X:
        Exemplo: ((float) X * multi_res) 
        A primeira vai ser referente ao tamanho, a segunda, espaçamento
        */

        //Título
            //Rectangle
        DrawRectangle(200*multi_res, 40*multi_res, 240*multi_res, 60*multi_res, LIGHTGRAY);
            //Texto do Título
        DrawTextEx(fontMenu, "SOLITAIRE", (Vector2){ 40.0f*multi_res, 200.0f*multi_res}, ((float) 8 * multi_res), (float) 2 * multi_res, RAYWHITE);
        
        //Opções
        DrawRectangleLines(240*multi_res, 140*multi_res, 160*multi_res, 40*multi_res, RAYWHITE);
        DrawRectangleLines(240*multi_res, 200*multi_res, 160*multi_res, 40*multi_res, RAYWHITE);
        DrawRectangleLines(240*multi_res, 260*multi_res, 160*multi_res, 40*multi_res, RAYWHITE);
        DrawRectangleLines(240*multi_res, 320*multi_res, 160*multi_res, 40*multi_res, RAYWHITE);

        //Textos das opções
        DrawTextEx(fontMenu, "Novo Jogo", (Vector2){ 140.0f*multi_res, 240.0f*multi_res}, ((float) 1 * multi_res), (float) 2 * multi_res, RAYWHITE);
        DrawTextEx(fontMenu, "Continuar", (Vector2){ 200.0f*multi_res, 240.0f*multi_res}, ((float) 1 * multi_res), (float) 2 * multi_res, RAYWHITE);
        DrawTextEx(fontMenu, "Creditos", (Vector2){260.0f*multi_res, 240.0f*multi_res}, ((float) 1 * multi_res), (float) 2 * multi_res, RAYWHITE);
        DrawTextEx(fontMenu, "Sair do Jogo", (Vector2){320.0f*multi_res, 240.0f*multi_res}, ((float) 1 * multi_res), (float) 2 * multi_res, RAYWHITE);

        //Desenhando as cartas do menu
        DrawTexture(textcarta_menu01, 60*multi_res, 120*multi_res, RAYWHITE);
        DrawTexture(textcarta_menu02, 60*multi_res, 480*multi_res, RAYWHITE);



        EndDrawing();

        //Unloading textures
        
    }

    UnloadTexture(textcarta_menu01);
    UnloadTexture(textcarta_menu02);
    UnloadFont(fontMenu);
    CloseWindow();

    //Enviando para a tela responsável
    if (opcao == 1) {
        novoJogo();
    }
    else if (opcao == 4) {
        UnloadFont(fontMenu);
        sair();
    }
    else iniciaMenu();
}

void novoJogo() {


    ListaCircEnc *baralho = cria_baralho();
    ListaCircEnc *baralho_embaralhado = embaralha_baralho(baralho);
    
    

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