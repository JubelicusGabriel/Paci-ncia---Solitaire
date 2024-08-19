#include "baralho.h"
#include "raylib.h"
#include "opcoes.h"


int main(void)
{
    int opcao = iniciaMenu();

    if (opcao == 1) {
        novoJogo();
    }
    else if (opcao == 2) {
        carregarJogo();
    }
    else if (opcao == 3) {
        creditos();
    }
    else if (opcao == 4) {
        sair();
    }
    return 0;
}
