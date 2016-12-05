#include <stdio.h>

#define BOARD_SIDE 6

/*
 * Representa o estado de uma linha do jogo. 
 * Uma linha é a ligação entre dois pontos.
 *
 *   EMPTY: A linha ainda não foi traçada
 *   FULL:  A linha já foi traçada
 */
typedef enum {
    EMPTY, FULL
} LineState;


/*
 * Representa os pontos do 'tabuleiro'
 * Cada ponto irá saber se a linha da direita e de 
 *     baixo já foi traçada ou não
 * Cada ponto contém o ID do jogador que preencheu o quadrado na sua diagonal inferior-direita
 */
typedef struct {
    LineState rightLine, bottomLine;
    int owner;
} Dot;


/*
 * Cria e inicializa os campos de um novo ponto
 */
Dot createDot() {
    Dot d;
    d.rightLine = EMPTY; 
    d.bottomLine = EMPTY;
    d.owner = -1;
    return d; 
}

/*
 * Inicializa os pontos de um 'tabuleiro' quadrado
 *     sideSize - Número de linhas(ou colunas) no tabuleiro
 *     board    - Ponteiro para um array bidimensional de Dot com dimensões sideSize X sideSize
 */
void initBoard(int sideSize, Dot board[][sideSize]) {
    for (int i = 0; i < BOARD_SIDE; i++) {
        for (int j = 0; j < BOARD_SIDE; j++) {
            board[i][j] = createDot();    
        }        
    }    
}


/*
 * Imprime na tela um 'tabuleiro' quadrado
 *     sideSize - Número de linhas(ou colunas) no tabuleiro
 *     board    - Ponteiro para um array bidimensional de Dot com dimensões sideSize X sideSize
 *     scores   - Array com 2 elementos: pontuação do jogador 1 e 2
 */
void displayBoard(int sideSize, Dot board[][sideSize], int* scores) {
    printf("\n-------------\n");
    printf("Jogador 1: %d\n", scores[0]);
    printf("Jogador 2: %d\n\n", scores[1]);
    
    for (int i = 0; i < BOARD_SIDE; i++) {
        for (int j = 0; j < BOARD_SIDE; j++) {
            if (board[i][j].rightLine == EMPTY) {
                printf("o ");
            }
            else {
                printf("o-");
            }
        }
        printf("\n");
        for (int j = 0; j < BOARD_SIDE; j++) {
            if (board[i][j].bottomLine == EMPTY) {
                printf("  ");
            }
            else if (board[i][j].owner == -1) {
                printf("| ");
            }
            else {
                printf("|%d", board[i][j].owner + 1);
            }
        }        
        printf("\n");
    }
    printf("\n-------------\n");
}

/*
 * Verifica se as coordenadas passadas correspondem a um possível traço no tabuleiro
 *     sideSize - Número de linhas(ou colunas) no tabuleiro
 *     board    - Ponteiro para um array bidimensional de Dot com dimensões sideSize X sideSize
 *     x1       - Coordenada X do primeiro ponto
 *     y1       - Coordenada Y do primeiro ponto
 *     x2       - Coordenada X do segundo ponto
 *     y2       - Coordenada Y do segundo ponto
 *
 *     retorno  - 1 caso sim, 0 caso contrário
 */
int validateCoords(int *x1, int *y1, int *x2, int *y2, int sideSize) {
    //Checa limites do tabuleiro
    if (*x1 < 0 || *y1 < 0 || *x2 < 0 || *y2 < 0 ||
      *x1 >= sideSize || *y1 >= sideSize ||
      *x2 >= sideSize || *y2 >= sideSize) {
        return 0; //Pontos fora do limite - COORDENADAS INVÁLIDAS
    }

    // faz com que (x1, y1) seja o elemento mais ao topo e esquerda, 
    // para que se opere apenas sobre ele posteriormente
    if ((*x1 == *x2 && *y1 > *y2) || (*y1 == *y2 && *x1 > *x2)) {
        int x3, y3; //variaveis auxiliares para fazer a troca;
        x3 = *x1; y3 = *y1;
        *x1 = *x2; *y1 = *y2;
        *x2 = x3; *y2 = y3;
    }

    //checa se os pontos sao adjacentes
    if( !( (*x1 == *x2 && *y2-*y1==1 ) || (*y1 == *y2 && *x2 - *x1 == 1 ) ) ) {
        return 0; //Pontos não adjacentes - COORDENADAS INVÁLIDAS
    }
}

/*
 * Verifica se possível e traça uma linha entre dois pontos do tabuleiro
 *     sideSize - Número de linhas(ou colunas) no tabuleiro
 *     board    - Ponteiro para um array bidimensional de Dot com dimensões sideSize X sideSize
 *     x1       - Coordenada X do primeiro ponto
 *     y1       - Coordenada Y do primeiro ponto
 *     x2       - Coordenada X do segundo ponto
 *     y2       - Coordenada Y do segundo ponto
 *
 *     retorno  - 1 caso movimento bem sucedido, 0 caso contrário
 */
int trace(int sideSize, Dot board[][sideSize], int x1, int y1, int x2, int y2) {

  if (!validateCoords(&x1, &y1, &x2, &y2, sideSize)) {
  	  return 0; //Coordenadas inválidas - MOVIMENTO INVÁLIDO
  }

    //se a linha for horizontal
    if (x1 == x2) {
        if (board[x1][y1].rightLine == FULL) {
            return 0; //A linha já estava traçada - MOVIMENTO INVÁLIDO
        }
        else {
            board[x1][y1].rightLine = FULL; // trace a linha
        }
    }

    //se a linha for vertical
    else if (y1 == y2) {
        if (board[x1][y1].bottomLine == FULL) {
            return 0; //A linha já estava traçada - MOVIMENTO INVÁLIDO
        }
        else {
            board[x1][y1].bottomLine = FULL; // trace a linha
        }
    }
    return 1; //MOVIMENTO VÁLIDO
}

/*
 * Verifica se um traço faz parte de um quadrado (pontuou) ou não
 *     sideSize - Número de linhas(ou colunas) no tabuleiro
 *     board    - Ponteiro para um array bidimensional de Dot com dimensões sideSize X sideSize
 *     x1       - Coordenada X do primeiro ponto
 *     y1       - Coordenada Y do primeiro ponto
 *     x2       - Coordenada X do segundo ponto
 *     y2       - Coordenada Y do segundo ponto
 *     player   - Jogador que efetuou a jogada
 *
 *     retorno  - A pontuação que esse traço gerou (0, 1 ou 2)
 */
int score(int sideSize, Dot board[][sideSize], int x1, int y1, int x2, int y2, int player) {
  int ret = 0;

  if (!validateCoords(&x1, &y1, &x2, &y2, sideSize)) {
  	  return 0; //Coordenadas inválidas
  }

  if (x1 == x2) { //linha horizontal
    //testar caixa abaixo
      if ( x1 + 1 < sideSize &&
      	board[x1][y1].owner == -1 && 
      	board[x1][y1].rightLine == FULL && 
      	board[x1][y1].bottomLine == FULL &&
      	board[x2][y2].bottomLine == FULL &&
      	board[x1 + 1][y1].rightLine == FULL) {
          board[x1][y1].owner = player;
          ret++;
      }

      //testar caixa acima
      if ( x1 - 1 >= 0 &&
      	board[x1 - 1][y1].owner == -1 &&
      	board[x1][y1].rightLine == FULL && 
      	board[x1 - 1][y1].rightLine == FULL && 
      	board[x1 - 1][y1].bottomLine == FULL && 
      	board[x2 - 1][y2].bottomLine == FULL) {
          board[x1 - 1][y1].owner = player;
          ret++;
      }
  }

  if (y1 == y2) { //linha horizontal
    //testar caixa a direita
      if ( y1 + 1 < sideSize &&
      	board[x1][y1].owner == -1 && 
      	board[x1][y1].rightLine == FULL && 
      	board[x1][y1].bottomLine == FULL &&
      	board[x2][y2].rightLine == FULL &&
      	board[x1][y1 + 1].bottomLine == FULL) {
          board[x1][y1].owner = player;
          ret++;
      }

      //testar caixa a esquerda
      if ( y1 - 1 >= 0 &&
      	board[x1][y1 - 1].owner == -1 &&
      	board[x1][y1].bottomLine == FULL && 
      	board[x1][y1 - 1].rightLine == FULL && 
      	board[x1][y1 - 1].bottomLine == FULL && 
      	board[x2][y2 - 1].rightLine == FULL) {
          board[x1][y1 - 1].owner = player;
          ret++;
      }
  }
  return ret;
}


int main() {

    int currentPlayer = 0;
    int scores[] = {0, 0};
    int winner = -1;
    char buffer[100];
    FILE *pFile;


    Dot board[BOARD_SIDE][BOARD_SIDE];

    initBoard(BOARD_SIDE, board);

    //Loop do Jogo
    while(scores[0] + scores[1] < (BOARD_SIDE - 1) * (BOARD_SIDE - 1)) { //Enquanto ainda falatarem caixas vazias
        int x1, x2, y1, y2;

        displayBoard(BOARD_SIDE, board, scores);
        printf("Jogador %d, digite dois pares de coordenadas (Ex.: 0 0 0 1):\n", currentPlayer + 1);
        scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
        if (!trace(BOARD_SIDE, board, x1, x2, y1, y2)) {
            printf("MOVIMENTO INVALIDO, TENTE NOVAMENTE");
            continue;
        }  
        else {
          int i = score(BOARD_SIDE, board, x1, x2, y1, y2, currentPlayer); 
            if (!i) { //nao pontuou
                currentPlayer = (currentPlayer + 1) % 2; //vez do próximo jogador
            }
            else { //pontuou
  	            printf("JOGADOR %d GANHOU %d PONTOS\n", currentPlayer + 1, i);
                scores[currentPlayer] += i; //aumentar o score
            }
        }
    }

    //decidir quem é o vencedor
    if (scores[0] > scores[1]) {
        winner = 0;
    }
    else {
        winner = 1;
    }

    printf("O vencedor e o jogador %d com %d pontos!\n", winner + 1, scores[winner]);
    displayBoard(BOARD_SIDE, board, scores);

    
    //requisita o nome do vencedor
    printf("Digite suas iniciais:\n");
    scanf("%s", buffer);

    //salva em arquivo
    pFile = fopen("vencedores.txt", "a");
    fprintf(pFile, "%s\n", buffer);
    fclose(pFile);

    return 0;
}