#include <stdio.h>
#include <stdlib.h>
#define TAMANHO_MAPA 6
/*TRABALHO FINAL DE C
PROFESSOR: THIAGO JACOB
GRUPO: JOSÉ LUCAS CAVALCANTI QUINHO 1610013520
GABRIEL DA SILVA COSTA VASCONCELOS DE ARAÚJO/1610013277
CAIO MARTINS LEMOS DE SOUZA 1610014084
HUDSON RANGEL AZEVEDO/1410110273

*/
// ir em projeto >> project build options >> other options e preencher o campo com -std=c99
//Estado da linha, full ocupado e empty livre
typedef enum {
    EMPTY, FULL
} situacao_linha;


// sao os pontinhos do tabuleiro
typedef struct {
    situacao_linha linhaDireita, linha_baixo;
    int dono;
} Ponto;


// inicializa os campos de um novo ponto
Ponto criaPonto() {
    Ponto d;
    d.linhaDireita = EMPTY;
    d.linha_baixo = EMPTY;
    d.dono = -1;
    return d;
}

//inicia a matriz, nLinhas sendo as linhas e colunas e mapa um array nlinha X nlinhas



// faz o print do tabuleiro na tela
void desenha_mapa(int nLinhas, Ponto mapa[][nLinhas], int* scores) {
    printf("========== JOGO DOS PONTINHOS ==========\n\n");
    printf("0 1 2 3 4 5\n\n");

    for (int i = 0; i < TAMANHO_MAPA; i++) {
        for (int j = 0; j < TAMANHO_MAPA; j++) {
            if (mapa[i][j].linhaDireita == EMPTY) {
                printf(". ");
            }
            else {
                printf("._");
            }
        }
        printf("\n");
        for (int j = 0; j < TAMANHO_MAPA; j++) {
            if (mapa[i][j].linha_baixo == EMPTY) {
                printf("  ");
            }
            else if (mapa[i][j].dono == -1) {
                printf("| ");
            }
            else {
                printf("|%d", mapa[i][j].dono + 1);
            }
        }
        printf("\n");
    }
    printf("\n===============================\n");
    printf("    SCORE PLAYER 1: %d\n", scores[0]);
    printf("    SCORE PLAYER 2: %d", scores[1]);
    printf("\n===============================\n\n");


}

void initMatriz(int nLinhas, Ponto mapa[][nLinhas]) {
    for (int i = 0; i < TAMANHO_MAPA; i++) {
        for (int j = 0; j < TAMANHO_MAPA; j++) {
            mapa[i][j] = criaPonto();
        }
    }
}


// h1 e h2, sao as posicções no eixo X e v1 e v2 no eixo Y

int checarPosicoes(int *h1, int *v1, int *h2, int *v2, int nLinhas) {

    //chega se os pontos sao validos
    if( !( (*h1 == *h2 && *v2-*v1==1 ) || (*v1 == *v2 && *h2 - *h1 == 1 ) ) ) {
        return 0;
    }
    if ((*h1 == *h2 && *v1 > *v2) || (*v1 == *v2 && *h1 > *h2)) {
        int x3, y3;
        x3 = *h1; y3 = *v1;
        *h1 = *h2; *v1 = *v2;
        *h2 = x3; *v2 = y3;
    }
    //Checa limites do tabuleiro
    if (*h1 < 0 || *v1 < 0 || *h2 < 0 || *v2 < 0 ||
      *h1 >= nLinhas || *v1 >= nLinhas ||
      *h2 >= nLinhas || *v2 >= nLinhas) {
        return 0;
    }


}

// verifica se a linha existe
int desenhe(int nLinhas, Ponto mapa[][nLinhas], int h1, int v1, int h2, int v2) {

  if (!checarPosicoes(&h1, &v1, &h2, &v2, nLinhas)) {
      return 0; // nao vale o movimento, cordenadas erradas
  }

    //se a linha estiver na horizontal
    if (h1 == h2) {
        if (mapa[h1][v1].linhaDireita == FULL) {
            return 0;
            //ja tinha linha
        }
        else {
            mapa[h1][v1].linhaDireita = FULL;
            // desenha a linha
        }
    }

    //se a linha for vertical
    else if (v1 == v2) {
        if (mapa[h1][v1].linha_baixo == FULL) {
            return 0;
            //ja tinha linha movimento nao vale
        }
        else {
            mapa[h1][v1].linha_baixo = FULL; // desenhe a linha
        }
    }
    return 1; //MOVIMENTO VÁLIDO
}

//verifica se fecha um quadrante
int score(int nLinhas, Ponto mapa[][nLinhas], int h1, int v1, int h2, int v2, int player) {
  int ret = 0;

  if (!checarPosicoes(&h1, &v1, &h2, &v2, nLinhas)) {
      return 0; //Coordenadas inválidas
  }

  if (h1 == h2) { //linha horizontal
      //o quadrado de cima
      if ( h1 - 1 >= 0 &&
        mapa[h1 - 1][v1].dono == -1 &&
        mapa[h1][v1].linhaDireita == FULL &&
        mapa[h1 - 1][v1].linhaDireita == FULL &&
        mapa[h1 - 1][v1].linha_baixo == FULL &&
        mapa[h2 - 1][v2].linha_baixo == FULL) {
          mapa[h1 - 1][v1].dono = player;
          ret++;
      }
      //testa o quadrante de baixo
      if ( h1 + 1 < nLinhas &&
        mapa[h1][v1].dono == -1 &&
        mapa[h1][v1].linhaDireita == FULL &&
        mapa[h1][v1].linha_baixo == FULL &&
        mapa[h2][v2].linha_baixo == FULL &&
        mapa[h1 + 1][v1].linhaDireita == FULL) {
          mapa[h1][v1].dono = player;
          ret++;
      }
  }

  if (v1 == v2) {
        //linha horizontal
    //testar caixa a direita
      if ( v1 + 1 < nLinhas &&
        mapa[h1][v1].dono == -1 &&
        mapa[h1][v1].linhaDireita == FULL &&
        mapa[h1][v1].linha_baixo == FULL &&
        mapa[h2][v2].linhaDireita == FULL &&
        mapa[h1][v1 + 1].linha_baixo == FULL) {
          mapa[h1][v1].dono = player;
          ret++;
      }

      //testar caixa a esquerda
      if ( v1 - 1 >= 0 &&
        mapa[h1][v1 - 1].dono == -1 &&
        mapa[h1][v1].linha_baixo == FULL &&
        mapa[h1][v1 - 1].linhaDireita == FULL &&
        mapa[h1][v1 - 1].linha_baixo == FULL &&
        mapa[h2][v2 - 1].linhaDireita == FULL) {
          mapa[h1][v1 - 1].dono = player;
          ret++;
      }
  }
  return ret;
}


int main() {
    // jogo principal
    int vezJogador = 0;
    int scores[] = {0, 0};
    int ganhador = -1;
    char buffer[100];
    FILE *pFile;


    Ponto mapa[TAMANHO_MAPA][TAMANHO_MAPA];

    initMatriz(TAMANHO_MAPA, mapa);

    //jogo principal while faz o loop necessario até a partida acabar
    while(scores[0] + scores[1] < (TAMANHO_MAPA - 1) * (TAMANHO_MAPA - 1)) {
        int h1, h2, v1, v2;

        desenha_mapa(TAMANHO_MAPA, mapa, scores);
        printf("Player %d, digite as cordenadas dos dois pontos (X Y X Y):", vezJogador + 1);
        scanf("%d %d %d %d", &h1, &h2, &v1, &v2);
        if (!desenhe(TAMANHO_MAPA, mapa, h1, h2, v1, v2)) {
            printf("\n TENTE DE NOVO, JOGADA INVALIDA\n");
            continue;
        }
        else {
          int i = score(TAMANHO_MAPA, mapa, h1, h2, v1, v2, vezJogador);
            if (!i) { //nao marcou  o ponto
                vezJogador = (vezJogador + 1) % 2; //outro player
            }
            else { //marcou ponto
                printf("JOGADOR %d GANHOU %d PONTOS\n", vezJogador + 1, i);
                scores[vezJogador] += i; //aumentar o score
            }
        }
    }
// condição para ganhar a partida

    if (scores[1] < scores[0]) {
        ganhador = 0;
    }
    else {
        ganhador = 1;
    }
    printf("PARABÉNS !!!!\n");
    printf("Player %d ganhou com %d pontos!\n", ganhador + 1, scores[ganhador]);
    desenha_mapa(TAMANHO_MAPA, mapa, scores);


    //requisita o nome do vencedor
    printf("Digite um Apelido:\n");
    scanf("%s", buffer);

    //salva o arquivo
    pFile = fopen("winners.txt", "a");
    fprintf(pFile, "%s\n", buffer);
    fclose(pFile);

    return 0;
}
