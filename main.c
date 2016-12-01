#include <stdio.h>
#include <stdlib.h>

int jogo_terminado = FALSE;

int mapa[6][6] = {//EX.: 0|-1| = 1 entao é possivel fazer a ligação, 0|-2| = 2 entao nao se pode fazer a ligação
    //nas colunas é o mesmo porem tendo 6 como resultado necessario para validar a linha
    {0, 1 , 2, 3 ,4, 5},
    {6, 7, 8 ,9, 10,11},
    {12,13,14,15,16,17},
    {18,19,20,21,22,23},
    {24,25,26,27,28,29},
    {30,31,32,33,34,35},



}


int main()
{
    while(jogo_terminado == FALSE) {
    printf("----------- JOGO DOS PONTINHOS ----------");
    printf(mapa);
    printf("------------- JOGADOR [%d] --------------");
    return 0;
    }
}
