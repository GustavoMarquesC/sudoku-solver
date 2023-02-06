#include <stdio.h>

int mat[9][9];

//função que lê um arquivo txt
void le_arquivo(char *nome, int mat[][9]){
    FILE *arq = fopen("sudoku.txt","r");
    if(arq == NULL){
        printf("Erro de leitura\n");
        system("pause");
        exit(1);
    }

    int p, n;
    for(p = 0; p < 9; p ++)
        for(n = 0; n < 9; n++)
            fscanf(arq,"%d",&mat[p][n]);

    fclose(arq);
}

//função que irá imprimir a tabela do sudoku
void lersudoku(){
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j++){
            printf(" %d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

//função que irá analisar as colunas da tabela
int coluna(int x, int y, int num){
    for (int i = 0; i < 9; i++){
        if (mat[x][i] == num){
            return 1;
        }
    }

    return 0;
}

//função que irá analisar as linhas da tabela
int linha (int x, int y, int num){

    for (int i = 0; i < 9; i++){
        if (mat[i][y] == num){
            return 1;
        }
    }
    return 0;
}

//função que irá analisar o quadrado 3x3
int quadrado (int x, int y, int num){

    if (x < 3){
        x = 0;
    } else if (x < 6){
        x = 3;
    } else {
        x = 6;
    }

    if (y < 3){
        y = 0;
    } else if (y < 6){
        y = 3;
    } else {
        y = 6;
    }

    for (int i = x; i < x + 3; i++){
        for (int j = y; j < y + 3; j++){
            if (mat[i][j] == num){
                return 1;
            }
        }
    }

    return 0;
}

//função que irá resolver a tabela
int resolucao(int x, int y){
    int num = 1;
    int auxX = 0;
    int auxY = 0;
    if (mat[x][y] != 0){
        if (x == 8 && y == 8){
            return 1;
        }

        if (x < 8) {
            x++;
        } else {
            x = 0;
            y++;
        }

        if (resolucao(x, y)){
            return 1;
        } else {
            return 0;
        }
    }

    if (mat[x][y] == 0){
        while (num < 10){
                //se o número não for o mesmo na linha, coluna e quadrante, a tabela recebe um número
            if (!quadrado(x, y, num) && !linha(x, y, num) && !coluna(x, y, num)){
                mat[x][y] = num;
                if (x == 8 && y == 8){
                    return 1;
                }

                if (x < 8) {
                    auxX = x + 1;
                } else {
                    auxY = 0;
                    auxY = y + 1;
                }

                if (resolucao(auxX, auxY)){
                    return 1;
                }
                }
            num++;
            }
            mat[x][y] = 0;
            return 0;
        }

}

//função principal que irá rodar as funções
int main()
{
    int x = 0;
    int y = 0;

    le_arquivo("sudoku.txt", mat);
    lersudoku();
    resolucao(x, y);
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    lersudoku();

    return 0;
}