#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int player1 = 1;
int player2 = 2;



int jogo_terminado = 0;
int linhas, colunas;
char mapa[11][11] = //EX.: 0|-1| = 1 entao é possivel fazer a ligação, 0|-2| = 2 entao nao se pode fazer a ligação
    //nas colunas é o mesmo porem tendo 6 como resultado necessario para validar a linha
    {{*,' ',*,' ',*,' ',*, ' ',*, ' ',*, ' ',*},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {*,' ',*,' ',*,' ',*, ' ',*, ' ',*, ' ',*},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {*,' ',*,' ',*,' ',*, ' ',*, ' ',*, ' ',*},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {*,' ',*,' ',*,' ',*, ' ',*, ' ',*, ' ',*},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {*,' ',*,' ',*,' ',*, ' ',*, ' ',*, ' ',*},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {*,' ',*,' ',*,' ',*, ' ',*, ' ',*, ' ',*}};


int matriz = {0};


int main()
{
    int ponto1, ponto2;
    int vez = 1;

    while(jogo_terminado == 0) {

    printf("----------- JOGO DOS PONTINHOS ----------\n\n");
        // imprime os valores do mapa
        int i,j;
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 6; j++) {
                mapa[i][j] = "o --";//comentar de volta depois essa linha
                printf("%c ", mapa[i][j]);

        }
        printf("\n\n");
    }
    while (vez == 1){
    printf("------------- JOGADOR [%d] --------------\n",player1);
    printf("Digite o (ponto1,ponto2): ");
    scanf("%d, %d", &ponto1, &ponto2);
    if ((ponto1 - ponto2 == 1) || (ponto2 - ponto1 == 1)){
        printf ("ok linha valida\n");
        vez = 2;
        break;
    }
    if ((ponto1 - ponto2 == 6) || (ponto2 - ponto1 == 6)){
        printf ("ok coluna valida\n");
        vez = 2;
        break;
    }
    else {
        printf ("linha invalida\n");
    }

    }
    while (vez == 2){
    printf("------------- JOGADOR [%d] --------------\n",player2);
    printf("Digite o (ponto1,ponto2): ");
    scanf("%d, %d", &ponto1, &ponto2);
    if ((ponto1 - ponto2 == 1) || (ponto2 - ponto1 == 1)){
        printf ("ok linha valida\n");
        vez = 1;
        break;
    }
    if ((ponto1 - ponto2 == 6) || (ponto2 - ponto1 == 6)){
        printf ("ok coluna valida\n");
        vez = 1;
        break;
    }
    else {
        printf ("linha invalida\n");
    }



    }





}
system("PAUSE");
return (0);
}

