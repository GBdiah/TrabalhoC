#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int jogo_terminado = 0;
int linhas, colunas;
int mapa[6][6] = //EX.: 0|-1| = 1 entao é possivel fazer a ligação, 0|-2| = 2 entao nao se pode fazer a ligação
    //nas colunas é o mesmo porem tendo 6 como resultado necessario para validar a linha
    {{0, 1 , 2, 3 ,4, 5},
    {6, 7, 8 ,9, 10,11},
    {12,13,14,15,16,17},
    {18,19,20,21,22,23},
    {24,25,26,27,28,29},
    {30,31,32,33,34,35}};

int player1 = 1;
int player2 = 2;



int main()
{
    while(jogo_terminado == 0) {
    printf("----------- JOGO DOS PONTINHOS ----------\n");

        int i,j;

        for (i = 0; i < 6; i++) {
            for (j = 0; j < 6; j++) {

                printf("%d ", mapa[i][j]);
        }
        printf("\n");
    }

    printf("------------- JOGADOR [%d] --------------\n",player1);
    return 0;
    }
}
