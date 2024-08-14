
#include "baralho.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>



#define QUANTIDADE_DE_CARTAS 52
#define TAMANHO_DO_VETOR 51


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
   pilha->topo = aux->prox;
   free(aux);
   return info;
}

// Funcao que determina se uma pilha eh vazia
int vaziaPilhaEnc(PilhaEnc *pilha){
   return (pilha->topo == NULL);
}

// Fun��o que cria uma lista
ListaCircEnc* criaListaCircEnc()
{
    ListaCircEnc *lista = (ListaCircEnc*)malloc(sizeof(ListaCircEnc));
    if (lista != NULL)
    {
        lista->prim = NULL;
    }
    return lista;
}

// Fun��o que destr�i uma lista
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

// Fun��o que imprime todos os n�s de uma lista
void imprimeListaCircEnc(ListaCircEnc *lista)
{
    if (lista->prim != NULL)
    {
        NodoLEnc *atual = lista->prim;
        do
        {
            printf("Chave: %d, Valor: %d, Naipe: %s\n", atual->info.chave, atual->info.valor, atual->info.naipe);
            atual = atual->prox;
        }
        while (atual != lista->prim);
    }
    else
    {
        printf("Lista vazia.\n");
    }
}

// Fun��o que insere um n� no in�cio de uma lista
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

// Fun��o que resgata um n� com uma informa��o de uma lista
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

ListaCircEnc* cria_baralho(){
    FILE *txtcartas;
    txtcartas = fopen("cartas.txt", "r");

    Carta carta;
    ListaCircEnc *baralho;
    baralho = criaListaCircEnc();
    for (int i=0; i<52; i++) {
        fscanf(txtcartas, " %d %s %d %s", &carta.valor, carta.naipe, &carta.chave, carta.imagemtxt);
        insereInicioListaCircEnc(baralho, carta);
    }

    return baralho;

}

ListaCircEnc* embaralha_baralho(ListaCircEnc* baralho)
{

    int cartas[TAMANHO_DO_VETOR];
    int cartas_embaralhadas[TAMANHO_DO_VETOR];
    int i, j, aux, menor_valor = 1;
    ListaCircEnc *baralho_embaralhado = criaListaCircEnc();
    NodoLEnc *nodoAux;

    srand(time(NULL));

    //preenchendo o vetor de 1 a 52
    for(i = 0; i <= QUANTIDADE_DE_CARTAS; i++)
    {
        cartas[i] = i + 1;
    }
    //algoritimo de Fisher-Yates para embaralhar os valores no vetor
    for(i = TAMANHO_DO_VETOR; i >= 0 ; i--)
    {
        j = rand() % (i + 1);
        aux = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = aux;
    }

    //passando os valores embaralhados para o novo vetor
    for (int k=0;k<TAMANHO_DO_VETOR; k++) {
        nodoAux = buscaInfoListaCircEnc(baralho, cartas[k]);
        insereInicioListaCircEnc(baralho_embaralhado, nodoAux->info);
    }

    return baralho_embaralhado;
}


int insereFilaViradoCima(FilaEnc *fila, Info info){
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
}

int inserePilhaViradoBaixo(PilhaEnc *pilha, Info info) {
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
    if (sentido == 0) {
        i = 0;
        carta = pilha->topo;
        while(carta->prox != NULL) {
            carta = carta->prox;
        }
        while(carta != NULL) {
            Image cartaImagem = LoadImage("cartas/card_back_red.png");
            ImageResize(&cartaImagem, 50*multi_res, 70*multi_res);
            carta->info.imagem = LoadTextureFromImage(cartaImagem);
            UnloadImage(cartaImagem);
            DrawTexture(carta->info.imagem,(100 + (coluna-1)*65)*multi_res, (10+ i*20*multi_res), WHITE);

            carta = carta->ant;
            i++;
        }
        return i;
    }
    else if (sentido == 1) {
        carta = fila->ini;
        while(carta != NULL) {
            Image cartaImagem = LoadImage(carta->info.imagemtxt);
            ImageResize(&cartaImagem, 50*multi_res, 70*multi_res);
            carta->info.imagem = LoadTextureFromImage(cartaImagem);
            UnloadImage(cartaImagem);

            DrawTexture(carta->info.imagem,(100 + (coluna-1)*65)*multi_res, (10+ (numBaixo+i)*20*multi_res), WHITE);

            carta = carta->prox;
            i++;
        }
        return 0;
    }
    return -1;
}


/*NOTE:
[DONE] Modo de verificar a compatibilidade das cartas na coluna e criar uma flag se é interagível ou não.
[DONE] Fazer cartas anteriores incompatíveis quando há incompatibilidade anterior
	e evitando que a primeira carta fique não interágivel numa fila tamanho 1.
[DONE] Descobrir como fazer uma hitbox atrelada à área da carta desenhada na tela.

// TODO: 
[1]
Achar uma forma de armazenar as hitboxes criadas de forma que eu possa verificar o mouse frame a frame durante o jogo.



[2]
Depois disso, criar uma função que cria uma fila com uma duplicata das cartas e usa para desenhar elas no lugar do cursor
enquanto o mouse estiver pressionado


[3]
Depois, fazer uma verificação que, ao largar o mouse, identifica acima de qual coluna foi feito isso (através de hitbox simplificada,
1 para cada coluna) e verifica se a primeira carta das fila duplicada é compatível, se sim, adiciona as cartas à outra fila.Se não,
de momento não faz nada. (Som depois).

*/ 
void verificaCompatibilidade(FilaEnc *fila) { 
    // Isso aqui foi pensado pra rodar a cada frame do jogo, mas acho que n fica pesado demais. 
    // Daria pra pensar numa implementação que só rodaria quando uma "flag" improvisada
    // que faria com que rodasse apenas se ouve alguma alteração na disposicao das filas, 
    // mas acho que com o tempo limitado n é boa ideia

    if (fila == NULL || vaziaFilaEnc(fila)){
        return;
    }

    NodoFEnc *atual = fila->fim;
    
    int compatibilidadeAnterior = 1; 
    // Se alguma carta anterior não for compatível, esse contador se torna 0 e deve fazer todas as anteriores nao serem mais "compativeis"
    // é basicamente uma forma de garantir que não serão movidas sem a vontade do jogador ou com cartas nao compatíveis na frente.

    while(atual != NULL){
        if (atual->ant == NULL) {
            // Se não tem carta anterior, a carta atual é automaticamente compatível
            // Antes fiz sem essa verificação mas acho que aí bugaria e travaria as filas com 1 carta só, fazendo impossíveis de mexer e de terminar o jogo
            atual->info.seq_compat = 1;

        } else if (compatibilidadeAnterior == 0) {
            // Anteriormente (na verificação) já teve incompatibilidade
            atual->info.seq_compat = 0; // marcando como incomp

        } else {
            // Verifica a compatibilidade com base nos naipes
            // Spades e clubs tem que ser 1 com diamonds e hearts
            if ((strcmp(atual->info.naipe, "spades") == 0 || strcmp(atual->info.naipe, "clubs") == 0) &&
                (strcmp(atual->ant->info.naipe, "diamonds") == 0 || strcmp(atual->ant->info.naipe, "hearts") == 0)) {
                atual->info.seq_compat = 1;

                // Hearts e diamonds tem que ser 1 com spades e clubs
            } else if ((strcmp(atual->info.naipe, "diamonds") == 0 || strcmp(atual->info.naipe, "hearts") == 0) &&
                       (strcmp(atual->ant->info.naipe, "spades") == 0 || strcmp(atual->ant->info.naipe, "clubs") == 0)) {
                atual->info.seq_compat = 1;

            } else { 
                // Aqui é se ela for incompatível mesmo, aí se já for, nas próximas n vai precisar 
                // de tanta verificacao e fica menos custoso
                atual->info.seq_compat = 0;
                compatibilidadeAnterior = 0;  // Marca que ja teve incompatibliidade
            }
        }

        // Vai pra carta anterior na fila
        atual = atual->ant;
    }
}



//Tentativa de fazer uma função que cria um retângulo pra interação (hitbox) com cada carta compatível
void criaHitboxColunas(FilaEnc *fila, int coluna, float multi_res){ 
    
    if (fila == NULL || vaziaFilaEnc(fila)){ //se a fila estiver vazia ou n for valida, sai da func
        return;
    }

    NodoFEnc *atual = fila->ini;
    while(atual!=NULL){
        if(atual->info.seq_compat == 1){
            //Esse retângulo vai ser usado pra identificar que o mouse tá sobre a carta
            int i = 0; //Contador de qual carta na fila é

            Rectangle hitbox;
            hitbox.x = (100 + (coluna-1)*65)*multi_res;
            hitbox.y = (10+ i*20*multi_res);
            hitbox.width = 50*multi_res;
            if(atual->prox == NULL){
                hitbox.height = 70*multi_res; //Se a cata for a da frente, a hitbox fica da carta toda
            }else{
                hitbox.height = 20*multi_res; //Se a carta for uma das de trás, a hitbox fica só no pedaço que n tem overlap
            }

            i++;//Aumenta o contador pra dar displacement(espaçamento) na carta
            
        }
    }

}
