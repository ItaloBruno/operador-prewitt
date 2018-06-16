#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NOME_MAX 128
#define COLUNAS  82 //LARGURA DA IMAGEM + 2
#define LINHAS   52 //ALTURA  DA IMAGEM + 2

//STRUCT COM TODAS AS INFORMAÇÕES NECESSÁRIAS PARA A MANIPULAÇÃO DA IMAGEM
struct imagem_entrada
{
    int  largura;
    int  altura;
    int  valor_max;
    int  dados[LINHAS][COLUNAS];
    char chave[NOME_MAX];

};  typedef struct imagem_entrada Imagem;

//VARIÁVEIS QUE SERÃO USADAS NO ALGORITMO
Imagem imagem_entrada;
Imagem imagem_resultado;
char nome_arquivo_entrada[NOME_MAX];
char nome_arquivo_resultado[NOME_MAX] = "prewitt-";
FILE *arquivo_entrada;
FILE *arquivo_final;
int i;
int j;
int contador;


// FAZ A LEITURA DO ARQUIVO DETERMINADO PELO USUÁRIO E SALVA SEUS DADOS NA VARIÁVEL IMAGEM
void lerImagem()
{
    printf("Digite o nome do arquivo .pgm: ");
    scanf("%s", nome_arquivo_entrada);
    arquivo_entrada = fopen(nome_arquivo_entrada,"r");
    if(arquivo_entrada == NULL)
    {
        printf("Erro ao abrir o arquivo!!\n");
        exit(0);
    }
    // VERIFICA SE É UMA IMAGEM PGM OU NÃO
    fscanf(arquivo_entrada, "%s", imagem_entrada.chave);
    if(strcmp(imagem_entrada.chave, "P2") != 0)
    {
        printf("Arquivo nao e PGM\n");
        fclose(arquivo_entrada);
        exit(0);
    }
    // SALVANDO OS DADOS DO CABEÇALHO DA IMAGEM
    fscanf(arquivo_entrada,"%d %d %d", &imagem_entrada.largura, &imagem_entrada.altura, &imagem_entrada.valor_max);

    // ATRIBUINDO OS DADOS DE CABEÇALHO PARA A IMAGEM RESULTADO
    strcpy(imagem_resultado.chave, imagem_entrada.chave);
    imagem_resultado.largura    = imagem_entrada.largura;
    imagem_resultado.altura     = imagem_entrada.altura;
    imagem_resultado.valor_max  = imagem_entrada.valor_max;

    // PREENCHENDO A MATRIZ DE DADOS COM OS VALORES DE CADA PIXEL DA IMAGEM
    for(i = 0; i < LINHAS; i++)
    {
        for(j = 0; j < COLUNAS; j++)
        {
            if(i == 0 || j == 0 || i == LINHAS -1 || j == COLUNAS -1)
            {
                imagem_entrada.dados[i][j] = 0;
            }
            else
            {
                fscanf(arquivo_entrada,"%d ", &imagem_entrada.dados[i][j]);
            }
        }
    }
    fclose(arquivo_entrada);
    return;
}

// FUNÇÃO QUE CRIA UMA NOVA IMAGEM APÓS A APLICAÇÃO DO PREWITT
void criarImagem()
{
    strcat(nome_arquivo_resultado, nome_arquivo_entrada);
    printf("NOME DO ARQUIVO RESULTADO: %s\n", nome_arquivo_resultado);

    // ESCRITA DOS DADOS DA NOVA IMAGEM
    arquivo_final = fopen(nome_arquivo_resultado, "w");
    fprintf(arquivo_final, "%s\n",    imagem_resultado.chave);
    fprintf(arquivo_final, "%d %d\n", imagem_resultado.largura, imagem_resultado.altura);
    fprintf(arquivo_final, "%d\n",    imagem_resultado.valor_max);
    for(i = 1; i < LINHAS-1; i++)
    {
        for(j = 1; j < COLUNAS-1; j++)
        {
            fprintf(arquivo_final, "%3d ", imagem_resultado.dados[i][j]);
            if(contador >= 16)
            {
                fprintf(arquivo_final, "\n");
                contador = 0;
            }
            else
                contador++;
        }
    }
    fprintf(arquivo_final, "\n");
    fclose(arquivo_final);
    return;
}

void operadorPrewitt()
{
    // MASCARAS DE PREWITT
    int mascara_x[3][3] = {{1, 0, -1},{1, 0, -1},{1, 0, -1}};
    int mascara_y[3][3] = {{-1, -1, -1},{0, 0, 0},{1, 1, 1}};
    int resultado_mascara_x = 0;
    int resultado_mascara_y = 0;
    int resultado_final     = 0;
    int linha   = 0;
    int coluna  = 0;

    for(linha = 1; linha < LINHAS-1; linha++)
    {
        for(coluna = 1; coluna < COLUNAS-1; coluna++)
        {
            /*
             * Matriz 3x3 que pegará os pixels ao redor do qual estamos operando
             * |---|---|---|
             * | 1 | 2 | 3 |
             * |---|---|---|
             * | 4 | 5 | 6 |
             * |---|---|---|
             * | 7 | 8 | 9 |
             * |---|---|---|
             */
            resultado_mascara_x   = ((mascara_x[0][0]) * imagem_entrada.dados[linha - 1][coluna - 1]) +
                                    ((mascara_x[0][1]) * imagem_entrada.dados[linha - 1][coluna])     +
                                    ((mascara_x[0][2]) * imagem_entrada.dados[linha - 1][coluna + 1]) +
                                    ((mascara_x[1][0]) * imagem_entrada.dados[linha][coluna - 1])     +
                                    ((mascara_x[1][1]) * imagem_entrada.dados[linha][coluna])         +
                                    ((mascara_x[1][2]) * imagem_entrada.dados[linha][coluna + 1])     +
                                    ((mascara_x[2][0]) * imagem_entrada.dados[linha + 1][coluna - 1]) +
                                    ((mascara_x[2][1]) * imagem_entrada.dados[linha + 1][coluna])     +
                                    ((mascara_x[2][2]) * imagem_entrada.dados[linha + 1][coluna + 1]);

            resultado_mascara_y   = ((mascara_y[0][0]) * imagem_entrada.dados[linha - 1][coluna - 1]) +
                                    ((mascara_y[0][1]) * imagem_entrada.dados[linha - 1][coluna])     +
                                    ((mascara_y[0][2]) * imagem_entrada.dados[linha - 1][coluna + 1]) +
                                    ((mascara_y[1][0]) * imagem_entrada.dados[linha][coluna - 1])     +
                                    ((mascara_y[1][1]) * imagem_entrada.dados[linha][coluna])         +
                                    ((mascara_y[1][2]) * imagem_entrada.dados[linha][coluna + 1])     +
                                    ((mascara_y[2][0]) * imagem_entrada.dados[linha + 1][coluna - 1]) +
                                    ((mascara_y[2][1]) * imagem_entrada.dados[linha + 1][coluna])     +
                                    ((mascara_y[2][2]) * imagem_entrada.dados[linha + 1][coluna + 1]);

            if(resultado_mascara_x < 0)
                resultado_mascara_x = resultado_mascara_x * (-1);
            if(resultado_mascara_y < 0)
                resultado_mascara_y = resultado_mascara_y * (-1);
            resultado_final  = resultado_mascara_x + resultado_mascara_y;

            if(resultado_final > 255) imagem_resultado.dados[linha][coluna] = 255;
            else imagem_resultado.dados[linha][coluna] = resultado_final;
        }
    }
}

int main()
{
    //==============================
    lerImagem();
    //==============================
    while(1)
    {
        operadorPrewitt();
    }
    //===============================
    criarImagem();
    //==============================
    return 0;
}
