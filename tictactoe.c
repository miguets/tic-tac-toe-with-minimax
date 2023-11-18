#include <stdio.h>
#include <stdlib.h>
//detectar si es un sitema unix || windows 
#if defined __linux__
#define IS_LINUX 1
#elif defined _WIN32
#define IS_LINUX 0
#endif
//colores para sistemas unix
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define DEFAULT "\033[0m"
//valores de retorno por jugador
#define PLAYER -1
#define BLANK 0
#define AI 1
//estructura del tablero
typedef struct List{
    int x;
    struct List *next;
}list;

//posicion mas optimar en cordenadas para que tire la AI
int optimalX,
    optimalY;
//tablero
int arr[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
//funciones
void printBoard(int board[3][3]);

//funciones para AI
int hardmode();
int estimateBoard(int board[3][3]);
int minimax(int board[3][3], int player);
void getMove(int board[3][3]);
int hardmode();

//funcion principal
int main()
{
    hardmode();
    return 0;
}
/*
        **                                                  **
        **Desde aqui empieza el codigo vs AI en modo dificil**
        **                                                  **
*/

void printBoard(int board[3][3])//solo imprime el tablero
{
    int i, j;
    if (IS_LINUX)
        system("clear"); // para Unix(linux)
    else
        system("cls"); // para Windows 
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf(" ");
            if (board[i][j] == AI && IS_LINUX)
            {
                printf(RED);
            }
            else if (board[i][j] == PLAYER && IS_LINUX)
            {
                printf(GREEN);
            }
            printf("%c ", board[i][j] == BLANK ? (3 * i) + j + 1 + '0' : (board[i][j] == PLAYER ? 'o' : 'x'));//condicional, si está vacio va a evaluar si esta opcupado por el player y sino por la AI
            if (IS_LINUX)
                printf(DEFAULT);
            if (j != 2)
                printf("|");
        }
        if (i != 2)
            printf("\n---+---+---\n");
    }
    printf("\n");
}


int estimateBoard(int board[3][3])
{
    if (
        (board[0][0] == PLAYER && board[0][1] == PLAYER && board[0][2] == PLAYER) ||//primera fila
        (board[1][0] == PLAYER && board[1][1] == PLAYER && board[1][2] == PLAYER) ||//segunda fila
        (board[2][0] == PLAYER && board[2][1] == PLAYER && board[2][2] == PLAYER) ||//tercera fila
        (board[0][0] == PLAYER && board[1][0] == PLAYER && board[2][0] == PLAYER) ||//primera columna
        (board[0][1] == PLAYER && board[1][1] == PLAYER && board[2][1] == PLAYER) ||//segunda columna
        (board[0][2] == PLAYER && board[1][2] == PLAYER && board[2][2] == PLAYER) ||//tercera columna
        (board[0][0] == PLAYER && board[1][1] == PLAYER && board[2][2] == PLAYER) ||//diagonal principal
        (board[0][2] == PLAYER && board[1][1] == PLAYER && board[2][0] == PLAYER))//diagonal inversa
        return PLAYER;
    else if (
        (board[0][0] == AI && board[0][1] == AI && board[0][2] == AI) ||//primera fila
        (board[1][0] == AI && board[1][1] == AI && board[1][2] == AI) ||//segunda fila
        (board[2][0] == AI && board[2][1] == AI && board[2][2] == AI) ||//tercera fila
        (board[0][0] == AI && board[1][0] == AI && board[2][0] == AI) ||//primera columna
        (board[0][1] == AI && board[1][1] == AI && board[2][1] == AI) ||//segunda columna
        (board[0][2] == AI && board[1][2] == AI && board[2][2] == AI) ||//tercera columna
        (board[0][0] == AI && board[1][1] == AI && board[2][2] == AI) ||//diagonal principal
        (board[0][2] == AI && board[1][1] == AI && board[2][0] == AI))//diagonal inversa
        return AI;
    else
        return BLANK;
}

int minimax(int board[3][3], int player)//funcion recursiva para calcular el mejor tiro
{
    int x, y;
    if (estimateBoard(board) != BLANK)//solo pasa cuando 
    {
        return estimateBoard(board) * player; // -1 * -1 || 1 * 1 
    }

    int localX = -1;
    int localY = -1;
    int score = -2;//cuando player(-1) tira primero -1 = -2

    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            if (board[x][y] == BLANK)
            {
                board[x][y] = player;
                int scoreForTheMove = -minimax(board, player == PLAYER ? AI : PLAYER); //se llama a ella misma para poner el tiro de -1 y 1 (intercambiando jugadores)
                if (scoreForTheMove > score)//buscar la mejor hoja
                {
                    score = scoreForTheMove;
                    localX = x;
                    localY = y;
                    //printf("%d", score);
                    //scanf("%d", &a);
                }
                board[x][y] = BLANK;//regresar el tablero a su lugar
            }
        }
    }
    optimalX = localX;//mejor posicion x
    optimalY = localY;//mejor posicion y
    if (optimalX == -1 && optimalY == -1)
    {
        return 0; // sin movimientos - es un empate
    }
    return score;
}

//getmove && main no son recursivas
void getMove(int board[3][3])//getmove es solo usada vs AI 
{
    int position = 0;
    printf("Indtroduce el numero de casilla donde introducir tu tiro \n");
    scanf("%d", &position);
    if (position >= 1 && position <= 9)
    {
        int x = (position - 1) / 3;
        int y = (position - 1) % 3;
        if (board[x][y] == BLANK)
        {
            board[x][y] = PLAYER;
        }
        else
        {
            printBoard(board);
            if (IS_LINUX)
                printf(RED);
            printf("Esta casilla esta ocupada");
            if (IS_LINUX)
                printf(DEFAULT);
            printf("\n");
            getMove(board);
        }
    }
    else
    {
        printBoard(board);
        if (IS_LINUX)
            printf(RED);
        printf("valor invalido");
        if (IS_LINUX)
            printf(DEFAULT);
        printf("\n");
        getMove(board);
    }
}

int hardmode(){//solo si se escoge el modo dificil vs IA
    int end = 0, i , j;
    printBoard(arr);
    while (!end)
    {
        getMove(arr);
        printBoard(arr);

        if (estimateBoard(arr) == PLAYER)
        {
            printf("Ganaste!\n");
            return 0;
        }

        printf("calculando tiro...\n");
        minimax(arr, AI);
        arr[optimalX][optimalY] = AI;
        printBoard(arr);

        if (estimateBoard(arr) == AI)
        {
            printf("Perdiste\n");
            return 0;
        }

        end = 1;
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                if (arr[i][j] == BLANK)
                    end = 0;
    }
    printf("Empate\n");
    return 0;
}
