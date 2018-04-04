#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COLUNAS 640
#define LINHAS  480

struct imagem
{
    int num_colunas, num_linhas, valor_max, dados[COLUNAS][LINHAS];
    char chave[128];
};  typedef struct imagem Imagem;

void lerImagem(Imagem *imagem_entrada, char *nome_arquivo)
{
    int i, j;
    //========================================================
    // Carregando a imagem a ser usada no programa
    FILE *arquivo_entrada;
    arquivo_entrada = fopen(nome_arquivo,"r");
    if(arquivo_entrada == NULL)
    {
        printf("Erro ao abrir o arquivo!!\n");
        exit(0);
    }

    // Setando os atributos da Imagem na struct
    fscanf(arquivo_entrada, "%s", imagem_entrada->chave);

    if(strcmp(imagem_entrada->chave, "P2") != 0)
    {
        printf("Arquivo nao e PGM\n");
        fclose(arquivo_entrada);
        exit(0);
    }

    fscanf(arquivo_entrada,"%d %d", &imagem_entrada->num_colunas, &imagem_entrada->num_linhas);
    fscanf(arquivo_entrada, "%d", &imagem_entrada->valor_max);


    //Setando a matriz de dados com os valores de cada pixel
    for(i = 0; i < imagem_entrada->num_colunas; i++)
    {
        for(j = 0; j < imagem_entrada->num_linhas; j++)
        {
            fscanf(arquivo_entrada, "%d ", &imagem_entrada->dados[i][j]);
        }
    }
    fclose(arquivo_entrada);
    return;
}

void criarImagem(Imagem *imagem, char *nome_arquivo_resultado)
{
    int i, j;
    FILE *arquivo_final;
    arquivo_final = fopen(nome_arquivo_resultado, "w");
    if(arquivo_final == NULL)
    {
        printf("Erro ao abrir o arquivo!!\n");
        exit(0);
    }
    fprintf(arquivo_final, "%s\n",      imagem->chave);
    fprintf(arquivo_final, "%d %d\n",   imagem->num_colunas, imagem->num_linhas);
    fprintf(arquivo_final, "%d\n",      imagem->valor_max);

    for(i = 0; i < imagem->num_colunas; i++)
    {
        for(j = 0; j < imagem->num_linhas; j++)
        {
            fprintf(arquivo_final, "%d ", imagem->dados[i][j]);
        }
    }
    fprintf(arquivo_final, "\n");
    fclose(arquivo_final);
    return;
}

//void operadorPrewitt(Imagem *imagem)
//{
//    int matrix_x[3][3];
//    int matrix_y[3][3];
//    int gx[COLUNAS][LINHAS];
//    int gy[COLUNAS][LINHAS];
//    int h[COLUNAS][LINHAS];
//    int g[COLUNAS][LINHAS];
//    int mat[COLUNAS][LINHAS];
//    int linha, coluna;
//    //Setando a matrix X (horizontal)
//    matrix_x[0][0] =  1;
//    matrix_x[0][1] =  0;
//    matrix_x[0][2] = -1;
//    matrix_x[1][0] =  1;
//    matrix_x[1][1] =  0;
//    matrix_x[1][2] = -1;
//    matrix_x[2][0] =  1;
//    matrix_x[2][1] =  0;
//    matrix_x[2][2] = -1;
//
//    //Setando a matrix Y (vertical)
//    matrix_y[0][0] = -1;
//    matrix_y[0][1] = -1;
//    matrix_y[0][2] = -1;
//    matrix_y[1][0] =  0;
//    matrix_y[1][1] =  0;
//    matrix_y[1][2] =  0;
//    matrix_y[2][0] =  1;
//    matrix_y[2][1] =  1;
//    matrix_y[2][2] =  1;
//
//    for(linha = 0; linha < LINHAS; linha++)
//    {
//        for(coluna = 0; coluna < COLUNAS; coluna++)
//        {
//            gx[linha][coluna] = ((matrix_x[0][0]) * (mat[linha][coluna])) + ((matrix_x[0][1]) * (mat[linha][coluna+1])) + ((matrix_x[0][2]) * (mat[linha][coluna+2])) + ((matrix_x[1][0]) * (mat[linha+1][coluna])) + ((matrix_x[1][1]) * (mat[linha+1][coluna+1])) + ((matrix_x[1][2]) * (mat[linha+1][coluna+2])) + ((matrix_x[2][0]) * (mat[linha+2][coluna])) + ((matrix_x[2][1]) * (mat[linha+2][coluna+1])) + ((matrix_x[2][2]) * (mat[linha+2][coluna+2]));
//            gy[linha][coluna] = ((matrix_y[0][0]) * (mat[linha][coluna])) + ((matrix_y[0][1]) * (mat[linha][coluna+1])) + ((matrix_y[0][2]) * (mat[linha][coluna+3])) + ((matrix_y[1][0]) * (mat[linha+1][coluna])) + ((matrix_y[1][1]) * (mat[linha+1][coluna+1])) + ((matrix_y[1][2]) * (mat[linha+1][coluna+2])) + ((matrix_y[2][0]) * (mat[linha+2][coluna])) + ((matrix_y[2][1]) * (mat[linha+2][coluna+1])) + ((matrix_y[2][2]) * (mat[linha+2][coluna+2]));
//            if(gx[linha][coluna] < 0)
//            {
//                gx[linha][coluna] = gx[linha][coluna] * (-1);
//            }
//            if(gy[linha][coluna] < 0)
//            {
//                gy[linha][coluna] = gy[linha][coluna] * (-1);
//            }
//            g[linha][coluna] = (gx[linha][coluna]) + (gy[linha][coluna]);
//            if (g[linha][coluna] < 0)
//            {
//                g[linha][coluna] = g[linha][coluna] * (-1);
//            }
//            if(g[linha][coluna] > 254)
//            {
//                imagem[linha][coluna] = (1);
//            }
//            else
//            {
//                imagem[linha][coluna] = (0);
//            }
//            fprintf(a, "%d ", h[linha][coluna]);
//            if (coluna == 255)
//            {
//                fprintf(a, "%s", "\n");
//            }
//        }
//}

int main()
{
    char nome_arq_entrada[]  = "totem.ascii.pgm";
    char nome_arq_result[]   = "resultado.ascii.pgm";
    Imagem imagem;
    lerImagem(&imagem, nome_arq_entrada);
//    operadorPrewitt(&imagem);
    criarImagem(&imagem, nome_arq_result);
    return 0;
}





