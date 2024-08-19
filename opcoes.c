#include "baralho.h"
#include "opcoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include <math.h>

int iniciaMenu() {

    //Tamanho inicial estipulado para a tela. Usado como alternativa à proposta inicial.
    int larguraTela = 800;
    int alturaTela = 600;

    InitWindow(larguraTela, alturaTela, "Menu Principal");

    
    // Dimensões dos retângulos
    int rectLargura = 200;
    int rectAltura = 60;

    // Posições dos retângulos
    int rectX = larguraTela / 2 - rectLargura / 2;
    int rectY1 = alturaTela / 2 - (2 * rectAltura + 30);  // "Iniciar Jogo"
    int rectY2 = rectY1 + rectAltura + 20;                // "Carregar Jogo"
    int rectY3 = rectY2 + rectAltura + 20;                // "Créditos"
    int rectY4 = rectY3 + rectAltura + 20;                // "Sair"

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Posição do mouse, usada para a interação com os menus
        Vector2 posicaoMouse = GetMousePosition();

        //Escrevendo o título no topo da tela
        DrawText("Paciência", larguraTela / 2 - MeasureText("Paciência", 40) / 2, rectY1 - 80, 40, DARKGRAY);

        // Primeiro retângulo: "Iniciar Jogo"
        Color rectColor1 = LIGHTGRAY;
        if (CheckCollisionPointRec(posicaoMouse, (Rectangle){rectX, rectY1, rectLargura, rectAltura})) {
            rectColor1 = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return 1;  // Retorna 1 quando "Iniciar Jogo" é clicado
            }
        }
        DrawRectangle(rectX, rectY1, rectLargura, rectAltura, rectColor1);
        DrawText("Iniciar Jogo", rectX + (rectLargura - MeasureText("Iniciar Jogo", 20)) / 2, rectY1 + (rectAltura - 20) / 2, 20, BLACK);

        // Segundo retângulo: "Carregar Jogo"
        Color rectColor2 = LIGHTGRAY;
        if (CheckCollisionPointRec(posicaoMouse, (Rectangle){rectX, rectY2, rectLargura, rectAltura})) {
            rectColor2 = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return 2;  // Retorna 2 quando "Carregar Jogo" é clicado
            }
        }
        DrawRectangle(rectX, rectY2, rectLargura, rectAltura, rectColor2);
        DrawText("Carregar Jogo", rectX + (rectLargura - MeasureText("Carregar Jogo", 20)) / 2, rectY2 + (rectAltura - 20) / 2, 20, BLACK);

        // Terceiro retângulo: "Créditos"
        Color rectColor3 = LIGHTGRAY;
        if (CheckCollisionPointRec(posicaoMouse, (Rectangle){rectX, rectY3, rectLargura, rectAltura})) {
            rectColor3 = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return 3;  // Retorna 3 quando "Créditos" é clicado
            }
        }
        DrawRectangle(rectX, rectY3, rectLargura, rectAltura, rectColor3);
        DrawText("Créditos", rectX + (rectLargura - MeasureText("Créditos", 20)) / 2, rectY3 + (rectAltura - 20) / 2, 20, BLACK);

        // Quarto retângulo: "Sair"
        Color rectColor4 = LIGHTGRAY;
        if (CheckCollisionPointRec(posicaoMouse, (Rectangle){rectX, rectY4, rectLargura, rectAltura})) {
            rectColor4 = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return 4;  // Retorna 4 quando "Sair" é clicado
            }
        }
        DrawRectangle(rectX, rectY4, rectLargura, rectAltura, rectColor4);
        DrawText("Sair", rectX + (rectLargura - MeasureText("Sair", 20)) / 2, rectY4 + (rectAltura - 20) / 2, 20, BLACK);

        EndDrawing();
    }

    CloseWindow(); // Fechar a janela ao terminar

    return 0; // Retorna 0 se a janela for fechada sem clicar em um retângulo
}

/// Para saber a dimenção da tela

float mult_res(){

    int larguraTela = 800;
    int alturaTela = 600;

    InitWindow(larguraTela, alturaTela, "Menu Principal");


    // Dimensões dos retângulos
    int rectLargura = 200;
    int rectAltura = 60;

    // Posições dos retângulos
    int rectX = larguraTela / 2 - rectLargura / 2;
    int rectY1 = alturaTela / 2 - (2 * rectAltura + 30);  // "Iniciar Jogo"
    int rectY2 = rectY1 + rectAltura + 20;                // "Carregar Jogo"
    int rectY3 = rectY2 + rectAltura + 20;                // "Créditos"
    int rectY4 = rectY3 + rectAltura + 20;                // "Sair"

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 posicaoMouse = GetMousePosition();
        
        /*
        Aqui, resolvemos colocar a seleção de resolução numa tela intermediária como uma alternativa às alternativas anteriores
        A função MeasureText, do Raylib, é usada para medir a largura do texto em pixels, de forma que possamos centralizar os textos nas opções.
        Por conveniência, usamos de resoluções que achamos serem mais comuns e, também, que se adequariam aos computadores dos integrantes e dos computadores
        dos laboratórios. Todos com o mesmo Aspect Ratio de 16:10. Mais próximo da razão áurea e das resoluções mais premium em notebooks / workstations.

        A função mult_res retorna um valor que funciona como multiplicador das outras medidas da tela. Todos os retângulos anteriores foram pensados na menor resolução possível
        e são basicamente "escalonados" para as resoluções maiores
        */
         DrawText("Qual tamanho de tela você deseja?", larguraTela / 2 - MeasureText("Qual tamanho de tela você deseja?", 40) / 2, rectY1 - 80, 40, DARKGRAY);

        // Primeiro retângulo: "640x400"
        Color rectColor1 = LIGHTGRAY;
        if (CheckCollisionPointRec(posicaoMouse, (Rectangle){rectX, rectY1, rectLargura, rectAltura})) {
            rectColor1 = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return 1;  // Retorna 1 para o multiplicador. 1 x 640x400 = 640 x 400.
            }
        }
        DrawRectangle(rectX, rectY1, rectLargura, rectAltura, rectColor1);
        DrawText("640x400", rectX + (rectLargura - MeasureText("640x400", 20)) / 2, rectY1 + (rectAltura - 20) / 2, 20, BLACK);

        // Segundo retângulo: "960x600"
        Color rectColor2 = LIGHTGRAY;
        if (CheckCollisionPointRec(posicaoMouse, (Rectangle){rectX, rectY2, rectLargura, rectAltura})) {
            rectColor2 = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return 1.5;  // Retorna 1.5 para o multiplicador. 1.5 x 640x400 = 960 x 600.
            }
        }
        DrawRectangle(rectX, rectY2, rectLargura, rectAltura, rectColor2);
        DrawText("960x600", rectX + (rectLargura - MeasureText("1280x800", 20)) / 2, rectY2 + (rectAltura - 20) / 2, 20, BLACK);

        // Terceiro retângulo: "1280x800"
        Color rectColor3 = LIGHTGRAY;
        if (CheckCollisionPointRec(posicaoMouse, (Rectangle){rectX, rectY3, rectLargura, rectAltura})) {
            rectColor3 = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return 2;  // Retorna 2 para o multiplicador. 2 x 640x400 = 1280 x 800.
            }
        }
        DrawRectangle(rectX, rectY3, rectLargura, rectAltura, rectColor3);
        DrawText("1280x800", rectX + (rectLargura - MeasureText("1280x800", 20)) / 2, rectY3 + (rectAltura - 20) / 2, 20, BLACK);

        // Quarto retângulo: "1600x1000"
        Color rectColor4 = LIGHTGRAY;
        if (CheckCollisionPointRec(posicaoMouse, (Rectangle){rectX, rectY4, rectLargura, rectAltura})) {
            rectColor4 = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return 2.5;  // Retorna 2.5 para o multiplicador. 2.5 x 640x400 = 1600 x 1000.
            }
        }
        DrawRectangle(rectX, rectY4, rectLargura, rectAltura, rectColor4);
        DrawText("1600x1000", rectX + (rectLargura - MeasureText("1600x1000", 20)) / 2, rectY4 + (rectAltura - 20) / 2, 20, BLACK);

        EndDrawing();
    }

    CloseWindow(); // Fechar a janela ao terminar

    return 0; // Retorna 0 se a janela for fechada sem clicar em um retângulo
}

/// Imprime os nomes de quem desenvolveu o jogo

void creditos(){
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Nomes com Cores Animadas");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Mudança de cor baseada no tempo
        Color color1 = (Color){ (unsigned char)(sin(GetTime() * 2.0f) * 127 + 128), 0, 0, 255 };
        Color color2 = (Color){ 0, (unsigned char)(sin(GetTime() * 2.0f + PI / 2) * 127 + 128), 0, 255 };
        Color color3 = (Color){ 0, 0, (unsigned char)(sin(GetTime() * 2.0f + PI) * 127 + 128), 255 };

        // Nomes a serem desenhados
        const char *nome1 = "Murilo Junqueira";
        const char *nome2 = "Gustavo Titow";
        const char *nome3 = "Gabriel Gonzalez";

        // Tamanho da fonte
        int fontSize = 30;

        // Cálculo das posições X para centralizar os nomes
        int textX1 = (screenWidth - MeasureText(nome1, fontSize)) / 2;
        int textX2 = (screenWidth - MeasureText(nome2, fontSize)) / 2;
        int textX3 = (screenWidth - MeasureText(nome3, fontSize)) / 2;

        // Posições Y dos textos
        int textY1 = screenHeight / 2 - 100;
        int textY2 = screenHeight / 2;
        int textY3 = screenHeight / 2 + 100;

        // Desenha três nomes na tela com cores animadas e centralizados
        DrawText(nome1, textX1, textY1, fontSize, color1);
        DrawText(nome2, textX2, textY2, fontSize, color2);
        DrawText(nome3, textX3, textY3, fontSize, color3);

        EndDrawing();
    }

    CloseWindow();

}

/// Para sair

void sair(){


    CloseWindow();  // Fecha a janela e encerra o programa

}




void novoJogo() {

    //multiplicador de resolução
    float multi_res = mult_res();

    //Inicialização do baralho inicial, antes de distribuir as cartas.
    ListaCircEnc *baralho = cria_baralho();
    /*Aqui, embaralhamos primeiro antes de distribuir entre as pilhas e filas que constituem as colunas de cartas.
    O resto das cartas são mantidas no baralho para as compras futuras*/
    ListaCircEnc *baralho_embaralhado = embaralha_baralho(baralho);


    //Setando o tamanho da tela baseado no multiplicador selecionado
    const int screenWidth = (640*multi_res);
    const int screenHeight = (400*multi_res);
    InitWindow(screenWidth, screenHeight, "Jogo Paciencia");

    //pilhas superiores (onde os naipes devem ser organizados)
    PilhaEnc *pilha_copas = criaPilhaEnc();
    PilhaEnc *pilha_ouro = criaPilhaEnc();
    PilhaEnc *pilha_paus = criaPilhaEnc();
    PilhaEnc *pilha_espadas = criaPilhaEnc();

    //colunas

    /*
    Aqui, as colunas são inicializadas baseadas em sua posição na tela. As colunas 1-7 consistem de 6 ambas filas e pilhas. Uma para as cartas
    não interagíveis (viradas para baixo) e uma para as cartas interagíveis, viradas para cima.
    */
    FilaEnc *colunas_cima[7];
    PilhaEnc *colunas_baixo[7];
    for (int i=0; i <= 6; i++) {
        colunas_cima[i] = criaFilaEnc();
        colunas_baixo[i] = criaPilhaEnc();
    }

    //monte de compras
    NodoLEnc *carta = baralho_embaralhado->prim;
    //inserindo cartas em cada coluna


    //Inserindo as cartas do baralho embaralhado diretamente em cada uma das pilhas e filas que constituem as colunas.
   for (int i =0; i<28; i++) {
        if (i == 0){
            insereFilaViradoCima(colunas_cima[0], carta->info, baralho_embaralhado, NULL, NULL);
        }
        else if (i == 1) {
            inserePilhaViradoBaixo(colunas_baixo[1], carta->info, baralho_embaralhado);
        }
        else if (i == 2) {
            insereFilaViradoCima(colunas_cima[1], carta->info, baralho_embaralhado, NULL, NULL);
        }
        else if (i <= 4) {
            inserePilhaViradoBaixo(colunas_baixo[2], carta->info, baralho_embaralhado);
        }
        else if (i == 5) {
            insereFilaViradoCima(colunas_cima[2], carta->info, baralho_embaralhado, NULL, NULL);
        }
        else if (i <= 8) {
            inserePilhaViradoBaixo(colunas_baixo[3], carta->info, baralho_embaralhado);
        }
        else if (i == 9) {
            insereFilaViradoCima(colunas_cima[3], carta->info, baralho_embaralhado, NULL, NULL);
        }
        else if (i <= 13) {
            inserePilhaViradoBaixo(colunas_baixo[4], carta->info, baralho_embaralhado);
        }
        else if (i == 14) {
            insereFilaViradoCima(colunas_cima[4], carta->info, baralho_embaralhado, NULL, NULL);
        }
        else if (i <= 19) {
            inserePilhaViradoBaixo(colunas_baixo[5], carta->info, baralho_embaralhado);
        }
        else if (i == 20) {
            insereFilaViradoCima(colunas_cima[5], carta->info, baralho_embaralhado, NULL, NULL);
        }
        else if (i <= 26) {
            inserePilhaViradoBaixo(colunas_baixo[6], carta->info, baralho_embaralhado);
        }
        else insereFilaViradoCima(colunas_cima[6], carta->info, baralho_embaralhado, NULL, NULL);

        carta = carta->prox;
    }


    //Dimensões dos botões de interação na área inferior da tela
    int botaoLargura = 150*multi_res;
    int botaoAltura = 25*multi_res;
    int botaoX = 450*multi_res;
    int botaoY = 400*multi_res - 40;

    //Filas e Cartas auxiliares usadas na transferência de uma coluna para a outra e verificação de compatibilidade

    FilaEnc *filaArraste;
    NodoFEnc *cartaAux;
    Info cartaAux2;
    NodoFEnc *cartaSelecionada;
    int k = 0;
    int col;
    FilaEnc *filaAux;

    int selectedValue = 0;
    int selectedSuit = 0;
    int selectedColumn = 0;

    const char *values[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const char *suits[4] = {"Copas", "Ouros", "Paus", "Espadas"};
    const char *columns[7] = {"Coluna 1", "Coluna 2", "Coluna 3", "Coluna 4", "Coluna 5", "Coluna 6", "Coluna 7"};


    /*Botões de interação e seleção. Eles são usados para selecionar qual carta em específico vai ser transportada para qual coluna.
    Interagindo com os botões, a seleção roda entre as cartas possíveis no jogo.
    A seleção desta forma foi implementada como alternativa à interação com mouse e hitboxes para cada carta, sendo desenvolvidas anteriormente mas
    que estavam demorando demais. (As hitboxes eram salvas em memória dinamicamente alocada e precisavam de verificação frame-a-frame)
    */
    Rectangle valueBox = {25*multi_res, 400*multi_res - 40, 75*multi_res, 20*multi_res};
    Rectangle suitBox = {125*multi_res, 400*multi_res - 40, 75*multi_res, 20*multi_res};
    Rectangle columnBox = {225*multi_res, 400*multi_res - 40, 75*multi_res, 20*multi_res};
    Rectangle confirmBox = {325*multi_res, 400*multi_res - 40, 60*multi_res, 20*multi_res};


    bool valueEdit = false;
    bool suitEdit = false;
    bool columnEdit = false;


    int numBaixo;
    int possibilidade = 0; //de mover uma carta

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GREEN);

        //desenhando cartas na tela

        numBaixo = 0; // numero de cartas virada para baixo em cada coluna

        for (int i=0; i<=6;i++) {
            if (vaziaFilaEnc(colunas_cima[i]) && !vaziaPilhaEnc(colunas_baixo[i])) {
                desviraCarta(colunas_cima[i], colunas_baixo[i]);

                //RESOLVER BUG DE MOVER MAIS DE UMA VEZ A MESMA CARTA
                //AS CARTAS DE BAIXO NÃO VÃO JUNTO
            }
        }

        //Desenhando as colunas na tela baseado no número de cartas viradas para baixo
        for (int i=0; i<=6;i++) {
            numBaixo = desenhaCartasViradoBaixo(colunas_baixo[i], i+1, multi_res);
            desenhaCartasViradoCima(colunas_cima[i], i+1, multi_res, numBaixo);
        }

        //Desenhando baralho
        desenhaBaralhoCompras(baralho_embaralhado, 0, multi_res);
        Vector2 posicaoMouse = GetMousePosition();


        /*Verificação de interação com os botões de menu durante o jogo.
        Os botões são normalmente renderizados em cinza, quando o mouse está acima deles, passam a ser renderizados em vermelho.
        */
        Color botaoCor = LIGHTGRAY;
        
        //Checando se está acima do botão de salvar e sair. Se sim, chama a função salvarJogo()
        if (CheckCollisionPointRec(posicaoMouse, (Rectangle){botaoX, botaoY, botaoLargura, botaoAltura})) {
            botaoCor = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return salvarJogo(colunas_cima, colunas_baixo, pilha_copas, pilha_ouro, pilha_paus, pilha_espadas, baralho_embaralhado);  // Retorna 1 quando "Iniciar Jogo" é clicado
            }
        }
        DrawRectangle(botaoX, botaoY, botaoLargura, botaoAltura, botaoCor);
        DrawText("Salvar Jogo e Sair", botaoX + 10, botaoY + 5, 15*multi_res, BLACK);

        /*Se o mouse for clicado acima de cada uma das caixas de seleção da carta, ele agrega em 1 ao valor da carta, naipes e colunas.
        Não há chance de sair do escopo das cartas pois é baseado no resto de divisão pelo valor máximo de cada uma.
        */
       
       //Verifica colisão com caixa de valor
        if (CheckCollisionPointRec(GetMousePosition(), valueBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            valueEdit = true;
            suitEdit = false;
            columnEdit = false;
        }
       //Verifica colisão com caixa de naipe
        if (CheckCollisionPointRec(GetMousePosition(), suitBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            suitEdit = true;
            valueEdit = false;
            columnEdit = false;
        }
       //Verifica colisão com caixa de coluna
        if (CheckCollisionPointRec(GetMousePosition(), columnBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            columnEdit = true;
            valueEdit = false;
            suitEdit = false;
        }

       //Soma ou subtrai baseado em qual botão está pressionado.
        
       //Interagindo com valor
        if (valueEdit) {
            if (IsKeyPressed(KEY_RIGHT)) selectedValue = (selectedValue + 1) % 13;
            if (IsKeyPressed(KEY_LEFT)) selectedValue = (selectedValue - 1 + 13) % 13;
        }
       
       //Interagindo com naipe
        if (suitEdit) {
            if (IsKeyPressed(KEY_RIGHT)) selectedSuit = (selectedSuit + 1) % 4;
            if (IsKeyPressed(KEY_LEFT)) selectedSuit = (selectedSuit - 1 + 4) % 4;
        }

       //Interagindo com coluna
        if (columnEdit) {
            if (IsKeyPressed(KEY_RIGHT)) selectedColumn = (selectedColumn + 1) % 7;
            if (IsKeyPressed(KEY_LEFT)) selectedColumn = (selectedColumn - 1 + 7) % 7;
        }

        
       //Interagindo com caixa de confirmação
        if (CheckCollisionPointRec(posicaoMouse, confirmBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            possibilidade = verificaPossibilidadeMudanca(selectedValue + 1, selectedSuit +1, colunas_cima[selectedColumn], colunas_cima);
            if (possibilidade != -1) {
                mudaCartaColuna(colunas_cima[possibilidade], colunas_cima[selectedColumn], selectedValue +1, selectedSuit +1);
            }
        }


        //Desenha o retângulo com a cor baseada se o mouse está hovering ou não
        DrawRectangleRec(valueBox, valueEdit ? LIGHTGRAY : GRAY);
        DrawRectangleRec(suitBox, suitEdit ? LIGHTGRAY : GRAY);
        DrawRectangleRec(columnBox, columnEdit ? LIGHTGRAY : GRAY);
        DrawRectangleRec(confirmBox, CheckCollisionPointRec(posicaoMouse, confirmBox) ? RED : LIGHTGRAY);

        DrawText(values[selectedValue], valueBox.x + 10, valueBox.y + 5, 15*multi_res, BLACK);
        DrawText(suits[selectedSuit], suitBox.x + 10, suitBox.y + 5, 15*multi_res, BLACK);
        DrawText(columns[selectedColumn], columnBox.x + 10, columnBox.y + 5, 15*multi_res, BLACK);
        DrawText("Confirmar", confirmBox.x +10, confirmBox.y+5, 10*multi_res, BLACK);

        //Texto explicativo na área inferior da tela.
        DrawText("Use as setas esquerda/direita para selecionar valor, naipe e coluna", 35*multi_res, (400 - 70)*multi_res, 15*multi_res, BLACK);
        DrawText("Clique em uma das caixas para editar", 35*multi_res, (400 - 58)*multi_res, 15*multi_res, BLACK);
        EndDrawing();
    }
    CloseWindow();

    //Destruição das estruturas após a saída do loop do jogo.
    destroiListaCircEnc(baralho);
    destroiListaCircEnc(baralho_embaralhado);
    destroiPilhaEnc(pilha_copas);
    destroiPilhaEnc(pilha_ouro);
    destroiPilhaEnc(pilha_espadas);
    destroiPilhaEnc(pilha_paus);
    for (int i=0;i<=6;i++) {
        free(colunas_baixo[i]);
        free(colunas_cima[i]);
    }
}


/*
Função que carrega o estado anterior do jogo baseado no arquivo de salvamento criado pela função salvarJogo()
Evita que o jogador tenha que jogar novamente a cada interação com o programa.
*/
void carregarJogo() {

    //Inicializa a tela da mesma forma que o novoJogo()
    float multi_res = mult_res();
    const int screenWidth = (640*multi_res);
    const int screenHeight = (400*multi_res);
    InitWindow(screenWidth, screenHeight, "Jogo Paciencia");

    ListaCircEnc *baralho = cria_baralho();

    PilhaEnc *pilha_copas = criaPilhaEnc();
    PilhaEnc *pilha_ouro = criaPilhaEnc();
    PilhaEnc *pilha_paus = criaPilhaEnc();
    PilhaEnc *pilha_espadas = criaPilhaEnc();

    //colunas
    FilaEnc *colunas_cima[7];
    PilhaEnc *colunas_baixo[7];
    for (int i=0; i <= 6; i++) {
        colunas_cima[i] = criaFilaEnc();
        colunas_baixo[i] = criaPilhaEnc();
    }

    ListaCircEnc *baralho_embaralhado = criaListaCircEnc();

    //Inicializa jogoSalvo baseado no arquivo criado anteriormente e salvo na pasta do jogo
    FILE *jogoSalvo;
    jogoSalvo = fopen("./jogoSalvo.txt", "r"); //Abrindo apenas para leitura

    //Inicializando variáveis auxiliares
    int aux;
    NodoLEnc *cartaAux;

    //Inserindo nas pilhas (viradas para baixo) em sequência baseado no arquivo em vez do baralho embaralhado
    for (int i = 0; i<=6; i++) {
        aux = 1;
        while (aux!=0){
            fscanf(jogoSalvo, "%d", &aux);
            if (aux != 0) {
                cartaAux = buscaInfoListaCircEnc(baralho, aux);
                inserePilhaViradoBaixo(colunas_baixo[i], cartaAux->info, NULL);
            }
        }
    }
    //Inserindo nas filas (viradas para cima) em sequência como anteriormente
    for (int i = 0; i<=6; i++) {
        aux = 1;
        while (aux!=0){
            fscanf(jogoSalvo, "%d", &aux);
            if (aux != 0) {
                cartaAux = buscaInfoListaCircEnc(baralho, aux);
                insereFilaViradoCima(colunas_cima[i], cartaAux->info, NULL, NULL, NULL);
            }
        }
    }

    /*
    Aqui, as pilhas de cartas já resolvidas em seus respectivos naipes são inicializados no programa baseado no arquivo.
    @TODO implementar a movimentação colunas -> naipes resolvidos.
    */

   //Carregando Copas
    aux = 1;
    while (aux!=0){
        fscanf(jogoSalvo, "%d", &aux);
        if (aux != 0) {
            cartaAux = buscaInfoListaCircEnc(baralho, aux);
            empilhaPilhaEnc(pilha_copas, cartaAux->info);
            cartaAux->info.sentido = 1;
        }
    }

    //Carregando Ouros
    aux = 1;
    while (aux!=0){
        fscanf(jogoSalvo, "%d", &aux);
        if (aux != 0) {
            cartaAux = buscaInfoListaCircEnc(baralho, aux);
            empilhaPilhaEnc(pilha_ouro, cartaAux->info);
            cartaAux->info.sentido = 1;
        }
    }

    //Carregando Paus
    aux = 1;
    while (aux!=0){
        fscanf(jogoSalvo, "%d", &aux);
        if (aux != 0) {
            cartaAux = buscaInfoListaCircEnc(baralho, aux);
            empilhaPilhaEnc(pilha_paus, cartaAux->info);
            cartaAux->info.sentido = 1;
        }
    }

    //Carregando Espadas
    aux = 1;
    while (aux!=0){
        fscanf(jogoSalvo, "%d", &aux);
        if (aux != 0) {
            cartaAux = buscaInfoListaCircEnc(baralho, aux);
            empilhaPilhaEnc(pilha_espadas, cartaAux->info);

        }
    }
    /*Carregando as restantes no baralho. (O baralho é sempre composto das cartas que não estão nas outras colunas e naipes resolvidos,
    pois isso só causaria problemas se planejássemos ter um modo com mais de um baralho).
    */
    aux = 1;
    while (aux!=0){
        fscanf(jogoSalvo, "%d", &aux);
        if (aux != 0) {
            cartaAux = buscaInfoListaCircEnc(baralho, aux);
            insereInicioListaCircEnc(baralho_embaralhado, cartaAux->info);
            cartaAux->info.sentido = 1;
        }
    }

    //Mesma setagem das variáveis do botão que ocorreu anteriormente no código
    int botaoLargura = 150*multi_res;
    int botaoAltura = 50*multi_res;
    int botaoX = 640*multi_res / 2 - botaoLargura / 2;
    int botaoY = 400*multi_res - (1.5*botaoAltura);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GREEN);

        //desenhando cartas na tela

        int numBaixo = 0; // numero de cartas virada para baixo em cada coluna

        //Desenhando das mesma forma que na função novoJogo()
        for (int i=0; i<=6;i++) {
            numBaixo = desenhaCartasColuna(NULL, colunas_baixo[i], i+1, 0, multi_res, numBaixo);
            desenhaCartasColuna(colunas_cima[i], NULL, i+1, 1, multi_res, numBaixo);
        }
        //O mouse tem sua posição supervisionada a cada frame, independente da tela.
        Vector2 posicaoMouse = GetMousePosition();

        //Botão de salvar e sair
        Color botaoCor = LIGHTGRAY;
        if (CheckCollisionPointRec(posicaoMouse, (Rectangle){botaoX, botaoY, botaoLargura, botaoAltura})) {
            botaoCor = RED;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
                return salvarJogo(colunas_cima, colunas_baixo, pilha_copas, pilha_ouro, pilha_paus, pilha_espadas, baralho_embaralhado);  // Retorna 1 quando "Iniciar Jogo" é clicado
            }
        }
        DrawRectangle(botaoX, botaoY, botaoLargura, botaoAltura, botaoCor);
        DrawText("Salvar Jogo e Sair", botaoX + (botaoLargura - MeasureText("Salvar Jogo e Sair", 20))/ 2, botaoY + (botaoAltura - 20) / 2, 20, BLACK);
        
        EndDrawing();
    }

    CloseWindow();

    //Destruição das listas e pilhas alocadas em memória ao final do looping do jogo.
    destroiListaCircEnc(baralho);
    destroiListaCircEnc(baralho_embaralhado);
    destroiPilhaEnc(pilha_copas);
    destroiPilhaEnc(pilha_ouro);
    destroiPilhaEnc(pilha_espadas);
    destroiPilhaEnc(pilha_paus);
    for (int i=0;i<=6;i++) {
        free(colunas_baixo[i]);
        free(colunas_cima[i]);
    }



}

/*
[Função de salvar o jogo]
Entradas/Inputs = Vetores dos componentes das colunas que estão virados pra cima como os virados para baixo (filas e pilhas), as pilhas de naipes resolvidas
e a lista circular que contém o resto do baralho que é usado para compra.
*/
void salvarJogo(FilaEnc *colunas_cima[7], PilhaEnc *colunas_baixo[7], PilhaEnc *pilha_copas, PilhaEnc *pilha_ouros, PilhaEnc *pilha_paus, PilhaEnc *pilha_espadas, ListaCircEnc *baralho) {
    
    //A função fopen abre o arquivo com nome "jogoSalvo.txt" para escrita. Esse arquivo é armazenado na mesma pasta do .exe.
    FILE *jogoSalvo;
    jogoSalvo = fopen("./jogoSalvo.txt", "w");
    //Inicialização dos nodos auxiliares para salvamentos
    NodoFEnc *coluna_cimaAux;
    NodoPEnc *coluna_baixoAux;
    NodoLEnc *baralhoAux;
    NodoPEnc *pilhasAux;

    //Salvando as cartas das colunas, começando pelas cartas viradas para baixo em cada coluna.
    for (int i =0; i <= 6; i++) {
        coluna_baixoAux = colunas_baixo[i]->topo;

        if (coluna_baixoAux != NULL) {
            while (coluna_baixoAux != NULL) {
                fprintf(jogoSalvo ,"%d\n", coluna_baixoAux->info.chave);
                coluna_baixoAux = coluna_baixoAux->prox;
            }
        }
        fprintf(jogoSalvo, "%d\n", 0);

    //Salvando as cartas das colunas, seguindo pelas cartas viradas para cima em cada coluna.
    }
    for (int i=0; i<=6;i++) {
        coluna_cimaAux = colunas_cima[i]->ini;

        if (coluna_cimaAux != NULL) {
            while (coluna_cimaAux != NULL) {
                fprintf(jogoSalvo ,"%d\n", coluna_cimaAux->info.chave);
                coluna_cimaAux = coluna_cimaAux->prox;
            }
        }
        fprintf(jogoSalvo, "%d\n", 0);
    }

    /*
    Salvando as cartas das pilhas de naipes resolvidos.
    Nesta ordem -> copas, ouros, paus e espadas (importante para o carregamento)
    */

   //Correndo pela pilha sempre começa pelo topo e segue enquanto o ponteiro prox não for null, que indica o final
    pilhasAux = pilha_copas->topo;
    if (pilhasAux != NULL) {
        while (pilhasAux != NULL) {
            fprintf(jogoSalvo, "%d\n", pilhasAux->info.chave);
            pilhasAux = pilhasAux->prox;
        }
    }
    fprintf(jogoSalvo, "%d\n", 0);

    pilhasAux = pilha_ouros->topo;
    if (pilhasAux != NULL) {
        while (pilhasAux != NULL) {
            fprintf(jogoSalvo, "%d\n", pilhasAux->info.chave);
            pilhasAux = pilhasAux->prox;
        }
    }
    fprintf(jogoSalvo, "%d\n", 0);

    pilhasAux = pilha_paus->topo;
    if (pilhasAux != NULL) {
        while (pilhasAux != NULL) {
            fprintf(jogoSalvo, "%d\n", pilhasAux->info.chave);
            pilhasAux = pilhasAux->prox;
        }
    }
    fprintf(jogoSalvo, "%d\n", 0);

    pilhasAux = pilha_espadas->topo;
    if (pilhasAux != NULL) {
        while (pilhasAux != NULL) {
            fprintf(jogoSalvo, "%d\n", pilhasAux->info.chave);
            pilhasAux = pilhasAux->prox;
        }
    }
    fprintf(jogoSalvo, "%d\n", 0);
    
    /*
    Salvando o baralho
    Funciona de forma similar a anterior, correndo pelo baralho enquanto o aux-> prox não for null, indicando o final da lista.*/
    baralhoAux = baralho->prim->ant;
    int c = baralhoAux->info.chave;
    if (baralhoAux != NULL) {
        do{
            baralhoAux = baralhoAux->prox;
            fprintf(jogoSalvo, "%d\n", baralhoAux->info.chave);
        } while (baralhoAux->info.chave != c);
    }
    fprintf(jogoSalvo, "%d\n", 0);
}
