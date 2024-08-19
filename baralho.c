
#include "baralho.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include "cartas.h"



#define QUANTIDADE_DE_CARTAS 52
#define TAMANHO_DO_VETOR 51

/*
[TADS PADRÕES]
Código necessário para as TADS introduzidas neste curso
*/

// Funcao que cria uma fila
FilaEnc* criaFilaEnc(){
   FilaEnc *fila = (FilaEnc*)malloc(sizeof(FilaEnc));
   if (fila != NULL){ // Idealmente, sempre checar!
      fila->ini = NULL;
      fila->fim = NULL;
   }
   return fila;
}

// Funcao que destroi uma fila
void destroiFilaEnc(FilaEnc *fila){
   NodoFEnc *aux = fila->ini;
   while(aux != NULL){
       NodoFEnc *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(fila);
}

// Funcao que insere um elemento na fila
void enfileiraFilaEnc(FilaEnc *fila, Info info){
   NodoFEnc *novo = (NodoFEnc*)malloc(sizeof(NodoFEnc));
   if (fila != NULL){
      novo->info = info;
      novo->prox = NULL;
      if (fila->fim != NULL)
         fila->fim->prox = novo;
      else
         fila->ini = novo;
      fila->fim = novo;
   }
}


// Funcao que remove um elemento da fila
Info desenfileiraFilaEnc(FilaEnc *fila){
   NodoFEnc *aux = fila->ini; 
   Info info = aux->info;
   fila->ini = aux->prox;
   if (fila->ini == NULL)
      fila->fim = NULL;
   free(aux);
   return info;
}

// Funcao que determina se uma fila eh vazia
int vaziaFilaEnc(FilaEnc *fila){
   return (fila->ini == NULL);
}
// Funcao que cria uma pilha
PilhaEnc* criaPilhaEnc(){
   PilhaEnc *pilha = (PilhaEnc*)malloc(sizeof(PilhaEnc));
   if (pilha != NULL) // Idealmente, sempre checar!
      pilha->topo = NULL;
   return pilha;
}

// Funcao que destroi uma pilha
void destroiPilhaEnc(PilhaEnc *pilha){
   NodoPEnc *aux = pilha->topo;
   while(aux != NULL){
       NodoPEnc *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(pilha);
}

// Funcao que insere um elemento na pilha
void empilhaPilhaEnc(PilhaEnc *pilha, Info info){
   NodoPEnc *novo = (NodoPEnc*)malloc(sizeof(NodoPEnc));
   if (novo != NULL){ // Idealmente, sempre checar!
      novo->info = info;
      novo->prox = pilha->topo;
      pilha->topo = novo;
   }
}



// Funcao que remove um elemento da pilha
Info desempilhaPilhaEnc(PilhaEnc* pilha){
   NodoPEnc *aux = pilha->topo; 
   /* Aqui assumimos que desempilha eh 
   chamada apenas se a pilha nao eh vazia */
   Info info = aux->info;
   if (aux->prox != NULL) 
    aux->prox->ant = NULL;
   pilha->topo = aux->prox;
   free(aux);
   return info;
}

// Funcao que determina se uma pilha eh vazia
int vaziaPilhaEnc(PilhaEnc *pilha){
   return (pilha->topo == NULL);
}

// Funcao que cria uma lista
ListaCircEnc* criaListaCircEnc()
{
    ListaCircEnc *lista = (ListaCircEnc*)malloc(sizeof(ListaCircEnc));
    if (lista != NULL)
    {
        lista->prim = NULL;
    }
    return lista;
}

// Funcao que destroi uma lista
void destroiListaCircEnc(ListaCircEnc *lista)
{
    if (lista->prim != NULL)
    {
        NodoLEnc *atual = lista->prim;
        do
        {
            NodoLEnc *prox = atual->prox;
            free(atual);
            atual = prox;
        }
        while (atual != lista->prim);
    }
    free(lista);
}

// Funcao que imprime todos os nodes de uma lista
void imprimeListaCircEnc(ListaCircEnc *lista)
{
    if (lista->prim != NULL)
    {
        NodoLEnc *atual = lista->prim;
        do
        {
            printf("Chave: %d, Valor: %d, Naipe: %d\n", atual->info.chave, atual->info.valor, atual->info.naipe);
            atual = atual->prox;
        }
        while (atual != lista->prim);
    }
    else
    {
        printf("Lista vazia.\n");
    }
}

// Funcao que insere um node no inocio de uma lista
int insereInicioListaCircEnc(ListaCircEnc *lista, Info info)
{
    NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
    if (novo == NULL) return 0;
    novo->info = info;

    if (lista->prim == NULL)
    {
        novo->prox = novo;
        novo->ant = novo;
        lista->prim = novo;
    }
    else
    {
        NodoLEnc *ultimo = lista->prim->ant;
        novo->prox = lista->prim;
        novo->ant = ultimo;
        lista->prim->ant = novo;
        ultimo->prox = novo;
        lista->prim = novo;
    }
    return 1;
}

// Funcao que insere um node no fim de uma lista
int insereFimListaCircEnc(ListaCircEnc *lista, Info info) {
    NodoLEnc *novoNodo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
    if (!novoNodo) {
        return 0;
    }

    novoNodo->info = info;

    if (lista->prim == NULL) {
        lista->prim = novoNodo;
        novoNodo->prox = novoNodo;
        novoNodo->ant = novoNodo;
    } else {
        NodoLEnc *ultimo = lista->prim->ant;
        novoNodo->prox = lista->prim;
        novoNodo->ant = ultimo;
        ultimo->prox = novoNodo;
        lista->prim->ant = novoNodo;
    }

    return 1;
}

// Funcao que remove um nodo de uma lista circular
int removeInfoListaCircEnc(ListaCircEnc *lista, int chave) {
    if (lista->prim != NULL) {
        NodoLEnc *aux = lista->prim;

        //caso nodo seja o primeiro da lista
        if (lista->prim->info.chave == chave) {
            NodoLEnc *primeiro = lista->prim;
            primeiro->prox->ant = primeiro->ant;
            primeiro->ant->prox = primeiro->prox;
            lista->prim = lista->prim->prox; 
            free(primeiro);
        }
        else {
            NodoLEnc *aux = lista->prim;
            while(aux->info.chave != chave) {
                aux = aux->prox;
            }
            aux->prox->ant = aux->ant;
            aux->ant->prox = aux->prox;
            free(aux);
        }
    }
}

// Funcao que resgata um node com uma informacao de uma lista
NodoLEnc* buscaInfoListaCircEnc(ListaCircEnc* lista, int chave)
{
    if (lista->prim != NULL)
    {
        NodoLEnc *atual = lista->prim;
        do
        {
            if (atual->info.chave == chave) return atual;
            atual = atual->prox;
        }
        while (atual != lista->prim);
    }
    return NULL;
}


/*
                                [FUNÇÕES BARALHO]
Funções relacionadas à qualquer interação relacionada ao baralho inicial, explicação mais detalhada é agregada a cada função.
*/

//A função cria_baralho() é responsável por pegar o arquivo cartas.txt que armazena as informações fundamentais das cartas e usá-las para criar o baralho inicial
ListaCircEnc* cria_baralho(){

    //Abre o arquivo para leitura
    FILE *txtcartas;
    txtcartas = fopen("cartas.txt", "r");
    
    //Para cada uma das cartas do baralho, atribui naipe, valor, chave e imagem equivalente.
    Carta carta;
    ListaCircEnc *baralho;
    baralho = criaListaCircEnc();
    for (int i=0; i<52; i++) {
        fscanf(txtcartas, " %d %d %d %s", &carta.valor, &carta.naipe, &carta.chave, carta.imagemtxt);
        insereInicioListaCircEnc(baralho, carta);
    }
    //Retorna o identificador do baralho
    return baralho;

}
//A função responsável por pegar o identificador do baralho e embaralhá-lo para que cada jogo seja único.
ListaCircEnc* embaralha_baralho(ListaCircEnc* baralho)
{

    //Cria um vetor para armazenar as cartas e outro para armazenar as cartas embaralhadas
    int cartas[TAMANHO_DO_VETOR];
    int cartas_embaralhadas[TAMANHO_DO_VETOR];
    int i, j, aux, menor_valor = 1;
    ListaCircEnc *baralho_embaralhado = criaListaCircEnc();
    NodoLEnc *nodoAux;

    srand(time(NULL));

    //preenchendo o vetor de 1 a 52
    for(i = 0; i < QUANTIDADE_DE_CARTAS; i++)
    {
        cartas[i] = i + 1;
    }
    //algoritimo de Fisher-Yates para embaralhar os valores no vetor
    for(i = QUANTIDADE_DE_CARTAS - 1; i > 0 ; i--)
    {
        j = rand() % (i + 1);
        aux = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = aux;
    }

    //passando os valores embaralhados para o novo vetor
    for (int k=0;k<QUANTIDADE_DE_CARTAS; k++) {
        nodoAux = buscaInfoListaCircEnc(baralho, cartas[k]);
        insereInicioListaCircEnc(baralho_embaralhado, nodoAux->info);
    }

    return baralho_embaralhado;
}

/*      [FUNÇÕES DAS COLUNAS]

As funções responsáveis por interações e inicializações relacionadas às colunas se encontram aqui.
*/

/*Tanto a função insereFilaViradoCima como a função insereFilaViradoBaixo tem objetivos similares.
A função insereFilaViradoCima é responsável por inserir cartas na parte interagível das colunas, ela pode receber um baralho, pilha ou fila de origem.
Como só um pode ser a origem por vez, os outros argumentos devem receber NULL.
*/
int insereFilaViradoCima(FilaEnc *fila, Info info, ListaCircEnc *baralhoOrigem, PilhaEnc *pilhaOrigem, FilaEnc *filaOrigem){
    //Os parâmetros <tipo>Origem representam o lugar de onde a carta a ser adiocionada veio
    //Obviamente só um poderá ser escolhido, para os outros deve ser passado NULL;
    
    NodoFEnc *novo = (NodoFEnc*)malloc(sizeof(NodoFEnc));
   if (fila != NULL){
      novo->info = info;
      novo->prox = NULL;
      if (fila->fim != NULL)
         fila->fim->prox = novo;
      else
         fila->ini = novo;
      fila->fim = novo;
   }

   novo->info.sentido = 1;

   if (baralhoOrigem) removeInfoListaCircEnc(baralhoOrigem, info.chave);

   //ATENCAO: falta implementar para pilhaOrigem != NULL e filaOrigem != NULL
}

/*
A função insereFilaViradoBaixo é responsável por inserir cartas na parte *NÃO* interagível das colunas.
Como no jogo o único momento em que ela pode receber é no início, ela só pode receber de um baralho de origem, o inicial.
*/
int inserePilhaViradoBaixo(PilhaEnc *pilha, Info info, ListaCircEnc *baralhoOrigem) {
    NodoPEnc *novo = (NodoPEnc*)malloc(sizeof(NodoPEnc));
   if (novo != NULL){ // Idealmente, sempre checar!
      novo->info = info;
      if (pilha->topo) {
        pilha->topo->ant = novo;
      }
      novo->ant = NULL;
      novo->prox = pilha->topo;
      pilha->topo = novo;
   }
    novo->info.sentido = 0;

   if (baralhoOrigem) removeInfoListaCircEnc(baralhoOrigem, info.chave);

}

int desenhaCartasColuna(FilaEnc *fila, PilhaEnc *pilha, int coluna, int sentido, float multi_res, int numBaixo) {
    /* Essa funcao desenha as cartas das colunas superiores
    Quando for usada para desenhar as cartas de cabeça para baixo (pilhas), o argumento fila deve receber NULL, e vice-versa;
    O argumento coluna é referente à qual coluna estas cartas pertencem;
    O argumento sentido é referente ao sentido da carta (virado para cima ou para baixo);
    O argumento numBaixo, é o número de cartas daquela coluna que estão de cabeça para baixo (é importante apenas quando
esta funcao for usada para plotar as cartas viradas para cima, caso contrario deve receber 0)
    */ 
    NodoLEnc *carta;
    int i = 0;
    float largura = 50*multi_res;
    float altura = 70*multi_res;
    if (sentido == 0 && pilha->topo != NULL) {
        i = 0;
        carta = pilha->topo;
        while(carta->prox != NULL) {
            carta = carta->prox;
        }
        while(carta != NULL) {
            Image cartaImagem = LoadImage("cartas/card_back_red.png");
            float posX = (100 + (coluna-1)*65)*multi_res;
            float posY = 10+ i*20*multi_res;
            ImageResize(&cartaImagem, largura, altura);
            Texture2D imagem = LoadTextureFromImage(cartaImagem);
            UnloadImage(cartaImagem);

            DrawTexture(imagem,(100 + (coluna-1)*65)*multi_res, (10+ i*20*multi_res), WHITE);


            carta->info.hitBox = (Rectangle){posX, posY, largura, altura};
            carta = carta->ant;
            i++;
        }
        return i;
    }
    else if (sentido == 1 && fila->ini != NULL) {
        carta = fila->ini;
        i=0;
        while(carta != NULL) {
            float posX = (100 + (coluna-1)*65)*multi_res;
            float posY = (10+ (numBaixo+i)*20*multi_res);
            Image cartaImagem = LoadImage(carta->info.imagemtxt);
            ImageResize(&cartaImagem, 50*multi_res, 70*multi_res);
            carta->info.imagem = LoadTextureFromImage(cartaImagem);
            UnloadImage(cartaImagem);

            DrawTexture(carta->info.imagem,(100 + (coluna-1)*65)*multi_res, (10+ (numBaixo+i)*20*multi_res), WHITE);

            carta->info.hitBox = (Rectangle){posX, posY, largura, altura};
            carta = carta->prox;
            i++;
        }
        return 0;
    }
    return 0;
}


/*Função que desenha as cartas da parte não interagível (topo, cartas viradas) da coluna.
Recebe a pilha à ser desenhada, a posição (n° de coluna) para ser posicionada e o float multi_res para escaloná-la.
Retorna um inteiro que identifica quantas cartas foram desenhadas na parte não interagível para que a parte interagível
seja desenhada com um offset correspondente
*/
int desenhaCartasViradoBaixo(PilhaEnc *pilha, int coluna, float multi_res) {
    NodoLEnc *carta;
    int i = 0;
    float largura = 50*multi_res;
    float altura = 70*multi_res;
    if (pilha->topo != NULL) {
        i = 0;
        carta = pilha->topo;
        while(carta->prox != NULL) {
            carta = carta->prox;
        }
        while(carta != NULL) {
            Image cartaImagem = LoadImage("cartas/card_back_red.png");
            //Offset relacionado à posição da coluna no campo de jogo
            float posX = (100 + (coluna-1)*65)*multi_res;
            //20 é o valor de offset entre cada uma das cartas para que a de trás ainda seja visível.
            float posY = 10+ i*20*multi_res;
            ImageResize(&cartaImagem, largura, altura);
            Texture2D imagem = LoadTextureFromImage(cartaImagem);
            UnloadImage(cartaImagem);

            DrawTexture(imagem,(100 + (coluna-1)*65)*multi_res, (10+ i*20*multi_res), WHITE);


            carta->info.hitBox = (Rectangle){posX, posY, largura, altura};
            carta = carta->ant;
            i++;
        }
        return i;
    }
    return 0;
}

/*Função que desenha as cartas da parte interagível (topo, cartas de frente) da coluna.
Recebe a fila à ser desenhada, a posição (n° de coluna) para ser posicionada, o float multi_res para escaloná-la e
o número de cartas não interagíveis da coluna para que possa receber um offset compatível.
*/
void desenhaCartasViradoCima(FilaEnc *fila, int coluna, float multi_res, int numBaixo) {
    NodoLEnc *carta;
    float largura = 50*multi_res;
    float altura = 70*multi_res;
    int i = 0;
    if (fila->ini != NULL) {
        carta = fila->ini;
        while(carta != NULL) {
            float posX = (100 + (coluna-1)*65)*multi_res;
            float posY = (10+ (numBaixo+i)*20*multi_res);
            Image cartaImagem = LoadImage(carta->info.imagemtxt);
            ImageResize(&cartaImagem, 50*multi_res, 70*multi_res);
            carta->info.imagem = LoadTextureFromImage(cartaImagem);
            UnloadImage(cartaImagem);

            DrawTexture(carta->info.imagem,(100 + (coluna-1)*65)*multi_res, (10+ (numBaixo+i)*20*multi_res), WHITE);

            carta->info.hitBox = (Rectangle){posX, posY, largura, altura};
            carta = carta->prox;
            i++;
        }
    }
}

/*Função que verifica se é possível realizar a mudança de carta de uma coluna para outra.
Recebe a carta que será movida(valor e naipe), a coluna de destino e um vetor de filas de cartas para verificar
possibilidade. Retorna o índice da coluna_cima onde a carta pode ser movida.
Implementada dessa forma como alternativa a função ~void verificaCompatibilidade(FilaEnc *fila)~ que criava um marcador na carta que era mudado à cada
verificação.
*/
int verificaPossibilidadeMudanca(int valor, int naipe, FilaEnc *colunaDestino, FilaEnc *colunas_cima[7]) {
    //naipes:
    // 1 -> Copas; 2 -> Ouros; 3 -> Paus; 4 -> Espadas;

    NodoLEnc *cartaBaixo = colunaDestino->fim;
    FilaEnc *filaAux;
    NodoLEnc *cartaAux;

    //verifica se uma das colunas_cima contém a carta, se sim, retorna o index da coluna
    for (int i=0;i<=6;i++) {
        filaAux = colunas_cima[i];
        cartaAux = filaAux->ini;
        while (cartaAux != NULL) {
            if (cartaAux->info.valor == valor && cartaAux->info.naipe == naipe) {
                if (cartaBaixo->info.valor == (valor + 1)) {
                    if (cartaBaixo->info.naipe <= 2 && naipe > 2) {
                        return i; //Se for, manda o index
                    }
                    else if (cartaBaixo->info.naipe > 2 && naipe <= 2) {
                        return i; //Se for, manda o index
                    }
                }

            }
            //Movendo pela fila
            cartaAux = cartaAux->prox;
        }
    }
    return -1; //Se *NÃO* for, manda um index inválido
    }

/*
Função que factualmente muda a carta de uma coluna para outra.
Recebe a coluna de origem e coluna de destino, valor e naipe da carta.
*/
void mudaCartaColuna(FilaEnc *colunaOrigem, FilaEnc *colunaDestino, int valor, int naipe) {
    FilaEnc *filaAux = criaFilaEnc();
    NodoFEnc *cartaAux;
    Info cartaRemov;

    /*
    Checa uma a uma as cartas da coluna de origem pelo correto valor e naipe enviados. Quando encontra, remove ela e coloca na fila auxiliar.

    */
    cartaAux = colunaOrigem->ini;
    if (cartaAux->info.valor != valor && cartaAux->info.naipe != naipe) {
        while(cartaAux->info.valor != valor && cartaAux->info.naipe != naipe) {
            cartaRemov = desenfileiraFilaEnc(colunaOrigem);
            enfileiraFilaEnc(filaAux,cartaRemov);

            cartaAux = colunaOrigem->ini;
        }
    }

    //move as cartas da coluna de origem para a coluna de destino
    cartaAux = colunaOrigem->ini;
    while (cartaAux != NULL) {
        cartaRemov = desenfileiraFilaEnc(colunaOrigem);
        enfileiraFilaEnc(colunaDestino, cartaRemov);

        cartaAux = colunaOrigem->ini;
    }
    //Move as cartas de fila aux de volta para a coluna de origem
    cartaAux = filaAux->ini;
    while (cartaAux != NULL) {
        cartaRemov = desenfileiraFilaEnc(filaAux);
        enfileiraFilaEnc(colunaOrigem, cartaRemov);
        cartaAux = filaAux->ini;
    }
    //Destroi a fila aux, liberando a memória no final do loop
    destroiFilaEnc(filaAux);
}


//Função que desvira uma carta, trazendo ela da área não interagível para a interagível.
void desviraCarta(FilaEnc *coluna_cima, PilhaEnc *coluna_baixo) {
    if (coluna_baixo->topo != NULL) {
        Info cartaRemov = desempilhaPilhaEnc(coluna_baixo); //Desempilha da parte não interagível para uma info auxiliar
        enfileiraFilaEnc(coluna_cima, cartaRemov); //Enfileira da info auxiliar para a fila da parte interagível
    }
}

/*
[BARALHO DE COMPRAS]

Função que desenha o baralho de compras na tela

Recebe um ponteiro para a lista encadeada do baralho de compras, um inteiro clicado que representa se o mouse está pressionado
e o float multi_res que é responsável por escalonar a textura à resolução da tela.
*/
void desenhaBaralhoCompras(ListaCircEnc *baralho, int clicado, float multi_res) {
    //Verifica se a lista de cartas tá vazia
    if (baralho->prim == NULL) return;

    //Largura, altura e coordenadas da carta que representa o baralho
    float largura = 50 * multi_res;
    float altura = 70 * multi_res;
    float posX = 20 * multi_res;
    float posY = 20 * multi_res;

    // Desenha a carta virada, que é a imagem padrão do baralho
    Image cartaVirada = LoadImage("cartas/card_back_red.png");
    ImageResize(&cartaVirada, largura, altura);
    Texture2D imagemVirada = LoadTextureFromImage(cartaVirada);
    UnloadImage(cartaVirada); //Unload na imagem pq n é mais necessária
    DrawTexture(imagemVirada, posX, posY, WHITE);

    //Se o jogador clicou na tela, leva a carta atual pra proxima na lista
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, (Rectangle){posX, posY, largura, altura})) {
            // Move a carta atual para o fim da lista
            baralho->prim = baralho->prim->prox; 
        }
    }

    // Desenha a carta atual logo abaixo do monte, se houver cartas na lista
    if (baralho->prim != NULL) {
        Image cartaAtualImagem = LoadImage(baralho->prim->info.imagemtxt); // Assumindo que `imagemtxt` é o caminho da imagem
        ImageResize(&cartaAtualImagem, largura, altura);
        Texture2D imagemAtual = LoadTextureFromImage(cartaAtualImagem);
        UnloadImage(cartaAtualImagem);
        DrawTexture(imagemAtual, posX, posY + altura + 10, WHITE); // Desenha um pouco abaixo do monte
    }


}