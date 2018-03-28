//Inclusão de bibliotecas
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Variáveis que serão usadas no programa
    FILE *p;
    FILE *a;
    int matrix_x[3][3];
    int matrix_y[3][3];
    char i[256];
    int gx[256][256];
    int gy[256][256];
    int h[256][256];
    int g[256][256];
    int n;
    int mat[256][256];
    int linha, coluna;

    //Setando a matrix X (horizontal)
    matrix_x[0][0] =  1;
    matrix_x[0][1] =  0;
    matrix_x[0][2] = -1;
    matrix_x[1][0] =  1;
    matrix_x[1][1] =  0;
    matrix_x[1][2] = -1;
    matrix_x[2][0] =  1;
    matrix_x[2][1] =  0;
    matrix_x[2][2] = -1;
    
    //Setando a matrix Y (vertical)
    matrix_y[0][0] = -1;
    matrix_y[0][1] = -1;
    matrix_y[0][2] = -1;
    matrix_y[1][0] =  0;
    matrix_y[1][1] =  0;
    matrix_y[1][2] =  0;
    matrix_y[2][0] =  1;
    matrix_y[2][1] =  1;
    matrix_y[2][2] =  1;
    //===========================================================================
    if((p = fopen("imagem2.txt","read")) == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    if((a = fopen("arq1.txt","write")) == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    //===========================================================================
    for(linha = 0; linha < 256; linha++)
    {
        for(coluna = 0; coluna < 256; coluna++)
        {
            fscanf(p,"%s",&i);
            n = atol(i);
            mat[linha][coluna] = n;
        }
    }
    //===========================================================================
    for(linha = 0; linha < 256;linha++)
    {
        for(coluna = 0; coluna < 256;coluna++)
        {
            gx[linha][coluna] = ((matrix_x[0][0]) * (mat[linha][coluna])) + ((matrix_x[0][1]) * (mat[linha][coluna+1])) + ((matrix_x[0][2]) * (mat[linha][coluna+2])) + ((matrix_x[1][0]) * (mat[linha+1][coluna])) + ((matrix_x[1][1]) * (mat[linha+1][coluna+1])) + ((matrix_x[1][2]) * (mat[linha+1][coluna+2])) + ((matrix_x[2][0]) * (mat[linha+2][coluna])) + ((matrix_x[2][1]) * (mat[linha+2][coluna+1])) + ((matrix_x[2][2]) * (mat[linha+2][coluna+2]));
            gy[linha][coluna] = ((matrix_y[0][0]) * (mat[linha][coluna])) + ((matrix_y[0][1]) * (mat[linha][coluna+1])) + ((matrix_y[0][2]) * (mat[linha][coluna+3])) + ((matrix_y[1][0]) * (mat[linha+1][coluna])) + ((matrix_y[1][1]) * (mat[linha+1][coluna+1])) + ((matrix_y[1][2]) * (mat[linha+1][coluna+2])) + ((matrix_y[2][0]) * (mat[linha+2][coluna])) + ((matrix_y[2][1]) * (mat[linha+2][coluna+1])) + ((matrix_y[2][2]) * (mat[linha+2][coluna+2]));
            if(gx[linha][coluna] < 0)
            {
                gx[linha][coluna] = gx[linha][coluna] * (-1);
            }
            if(gy[linha][coluna] < 0)
            {
                gy[linha][coluna] = gy[linha][coluna] * (-1);
            }
            g[linha][coluna] = (gx[linha][coluna]) + (gy[linha][coluna]);
            if (g[linha][coluna] < 0)
            {
                g[linha][coluna] = g[linha][coluna] * (-1);
            }
            if(g[linha][coluna] > 254)
            {
                h[linha][coluna] = (1);
            }
            else
            {
                h[linha][coluna] = (0);
            }
            fprintf(a, "%d ", h[linha][coluna]);
            if (coluna == 255)
            {
                fprintf(a, "%s", "\n");
            }
        }
    }
    //===========================================================================
    fclose(p);
    fclose(a);
    return 0;
}
