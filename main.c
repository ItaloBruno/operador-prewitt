#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LINHAS 246
#define COLUNAS 300

struct imagem
{
    int num_colunas, num_linhas, valor_max, dados[LINHAS][COLUNAS];
    char chave[128];
};  typedef struct imagem Imagem;

Imagem imagem;

void lerImagem(char *nome_arquivo)
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
    fscanf(arquivo_entrada, "%s", imagem.chave);

    if(strcmp(imagem.chave, "P2") != 0)
    {
        printf("Arquivo nao e PGM\n");
        fclose(arquivo_entrada);
        exit(0);
    }

    fscanf(arquivo_entrada,"%d %d", &imagem.num_linhas, &imagem.num_colunas);
    fscanf(arquivo_entrada, "%d", &imagem.valor_max);

    //Setando a matriz de dados com os valores de cada pixel
    for(i = 0; i < LINHAS; i++)
    {
        for(j = 0; j < COLUNAS; j++)
        {
            fscanf(arquivo_entrada,"%d ", &imagem.dados[i][j]);
        }
    }
    fclose(arquivo_entrada);
}

void criarImagem(char *nome_arquivo_resultado)
{
    int i, j;
    FILE *arquivo_final;
    arquivo_final = fopen(nome_arquivo_resultado, "w");

    fprintf(arquivo_final, "%s\n",      imagem.chave);
    fprintf(arquivo_final, "%d %d\n",   imagem.num_linhas, imagem.num_colunas);
    fprintf(arquivo_final, "%d\n",      imagem.valor_max);

    for(i = 0; i < LINHAS; i++)
    {
        for(j = 0; j < COLUNAS; j++)
        {
            fprintf(arquivo_final, "%d ", imagem.dados[i][j]);
        }
    }
    fprintf(arquivo_final, "\n");
    fclose(arquivo_final);
    return;
}

void operadorPrewitt()
{
    // Mascaras de Prewitt
    int mascara_x[3][3];
    int mascara_y[3][3];
    int gx[LINHAS][COLUNAS];
    int gy[LINHAS][COLUNAS];
    int g[LINHAS][COLUNAS];
    int linha, coluna;

    // Setando a mascara X
    mascara_x[0][0] =  1;
    mascara_x[0][1] =  0;
    mascara_x[0][2] = -1;
    mascara_x[1][0] =  1;
    mascara_x[1][1] =  0;
    mascara_x[1][2] = -1;
    mascara_x[2][0] =  1;
    mascara_x[2][1] =  0;
    mascara_x[2][2] = -1;

    // Setando a mascara Y
    mascara_y[0][0] = -1;
    mascara_y[0][1] = -1;
    mascara_y[0][2] = -1;
    mascara_y[1][0] =  0;
    mascara_y[1][1] =  0;
    mascara_y[1][2] =  0;
    mascara_y[2][0] =  1;
    mascara_y[2][1] =  1;
    mascara_y[2][2] =  1;

    for(linha = 0; linha < LINHAS; linha++)
    {
        for(coluna = 0; coluna < COLUNAS; coluna++)
        {
            gx[linha][coluna]   =   ((mascara_x[0][0]) * (imagem.dados[linha][coluna])) +
                                    ((mascara_x[0][1]) * (imagem.dados[linha][coluna+1])) +
                                    ((mascara_x[0][2]) * (imagem.dados[linha][coluna+2])) +
                                    ((mascara_x[1][0]) * (imagem.dados[linha+1][coluna])) +
                                    ((mascara_x[1][1]) * (imagem.dados[linha+1][coluna+1])) +
                                    ((mascara_x[1][2]) * (imagem.dados[linha+1][coluna+2])) +
                                    ((mascara_x[2][0]) * (imagem.dados[linha+2][coluna])) +
                                    ((mascara_x[2][1]) * (imagem.dados[linha+2][coluna+1])) +
                                    ((mascara_x[2][2]) * (imagem.dados[linha+2][coluna+2]));

            gy[linha][coluna] =   ((mascara_y[0][0]) * (imagem.dados[linha][coluna])) +
                                    ((mascara_y[0][1]) * (imagem.dados[linha][coluna+1])) +
                                    ((mascara_y[0][2]) * (imagem.dados[linha][coluna+3])) +
                                    ((mascara_y[1][0]) * (imagem.dados[linha+1][coluna])) +
                                    ((mascara_y[1][1]) * (imagem.dados[linha+1][coluna+1])) +
                                    ((mascara_y[1][2]) * (imagem.dados[linha+1][coluna+2])) +
                                    ((mascara_y[2][0]) * (imagem.dados[linha+2][coluna])) +
                                    ((mascara_y[2][1]) * (imagem.dados[linha+2][coluna+1])) +
                                    ((mascara_y[2][2]) * (imagem.dados[linha+2][coluna+2]));

           if(gx[linha][coluna] < 0)
           {
               gx[linha][coluna] = gx[linha][coluna] * (-1);
           }
           if(gy[linha][coluna] < 0)
           {
               gy[linha][coluna] = gy[linha][coluna] * (-1);
           }

           g[linha][coluna] = (gx[linha][coluna])  + (gy[linha][coluna]);

           if (g[linha][coluna] < 0)
           {
               g[linha][coluna] = g[linha][coluna] * (-1);
           }
           if(g[linha][coluna] > 254)
           {
               imagem.dados[linha][coluna] = 255;
           }
           else
           {
               imagem.dados[linha][coluna] = 0;
           }

            // gx[linha][coluna] = pow(gx[linha][coluna], 2);
            // gy[linha][coluna] = pow(gy[linha][coluna], 2);
            // g[linha][coluna]  = gx[linha][coluna] + gy[linha][coluna];
            // g[linha][coluna]  = sqrt(g[linha][coluna]);
            // imagem.dados[linha][coluna] = g[linha][coluna];
        }
    }
}

int main()
{
    char nome_arq_entrada[]  = "coins.ascii.pgm";
    char nome_arq_result[]   = "resultado.ascii.pgm";
    lerImagem(nome_arq_entrada);
    operadorPrewitt(imagem);
    criarImagem(nome_arq_result);
    return 0;
}





