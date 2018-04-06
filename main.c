#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NOME_MAX 512
#define COLUNAS 512 //LARGURA DA IMAGEM
#define LINHAS  512 //ALTURA DA IMAGEM

//STRUCT COM TODAS AS INFORMAÇÕES NECESSÁRIAS PARA A MANIPULAÇÃO DA IMAGEM
struct imagem
{
    int  largura,
         altura,
         valor_max,
         dados[LINHAS][COLUNAS];
    char chave[128];

};  typedef struct imagem Imagem;

//VARIÁVEIS QUE SERÃO USADAS NO ALGORITMO
Imagem imagem;
char nome_arquivo_entrada[NOME_MAX],
     nome_arquivo_resultado[NOME_MAX] = "prewitt.";
FILE *arquivo_entrada,
     *arquivo_final;

// FAZ A LEITURA DO ARQUIVO DETERMINADO PELO USUÁRIO E SALVA SEUS DADOS NA VARIÁVEL IMAGEM
void lerImagem()
{
    int i, j;
    printf("Digite o nome do arquivo .pgm: ");
    scanf("%s", nome_arquivo_entrada);
    arquivo_entrada = fopen(nome_arquivo_entrada,"r");
    if(arquivo_entrada == NULL)
    {
        printf("Erro ao abrir o arquivo!!\n");
        exit(0);
    }
    // VERIFICA SE É UMA IMAGEM PGM OU NÃO
    fscanf(arquivo_entrada, "%s", imagem.chave);
    if(strcmp(imagem.chave, "P2") != 0)
    {
        printf("Arquivo nao e PGM\n");
        fclose(arquivo_entrada);
        exit(0);
    }
    // SALVANDO OS DADOS DO CABEÇALHO DA IMAGEM
    fscanf(arquivo_entrada,"%d %d %d", &imagem.largura, &imagem.altura, &imagem.valor_max);

    // PREENCHENDO A MATRIZ DE DADOS COM OS VALORES DE CADA PIXEL DA IMAGEM
    for(i = 0; i < LINHAS; i++)
    {
        for(j = 0; j < COLUNAS; j++)
        {
            fscanf(arquivo_entrada,"%d ", &imagem.dados[i][j]);
        }
    }
    fclose(arquivo_entrada);
    return;
}

// FUNÇÃO QUE CRIA UMA NOVA IMAGEM APÓS A APLICAÇÃO DO PREWITT
void criarImagem()
{
    int i, j;
    strcat(nome_arquivo_resultado, nome_arquivo_entrada);
    printf("NOME DO ARQUIVO RESULTADO: %s", nome_arquivo_resultado);

    // ESCRITA DOS DADOS DA NOVA IMAGEM
    arquivo_final = fopen(nome_arquivo_resultado, "w");
    fprintf(arquivo_final, "%s\n",    imagem.chave);
    fprintf(arquivo_final, "%d %d\n", imagem.largura, imagem.altura);
    fprintf(arquivo_final, "%d\n",    imagem.altura);
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
    // MASCARAS DE PREWITT
    int mascara_x[3][3] = {{1, 0, -1},{1, 0, -1},{1, 0, -1}};
    int mascara_y[3][3] = {{-1, -1, -1},{0, 0, 0},{1, 1, 1}};
    int resultado_mascara_x = 0;
    int resultado_mascara_y = 0;
    int resultado_final     = 0;
    int linha, coluna;

    // PERCORRE CADA PIXEL DA IMAGEM E APLICA AS MASCARAS X E Y NELE E EM SUA VIZINHANÇA
    // APÓS ISSO, O RESULTADO DE AMBAS AS OPERAÇÕES SÃO ELEVADAS AO QUADRADO E SOMADAS
    // POR FIM, É FEITA A RAIZ QUADRADA DESSA SOMA E ATRIBUÍDA AO PIXEL EM QUE ESTAMOS NO MOMENTO.
    for(linha = 0; linha < LINHAS; linha++)
    {
        for(coluna = 0; coluna < COLUNAS; coluna++)
        {
            resultado_mascara_x   = ((mascara_x[0][0]) * (imagem.dados[linha][coluna])) +
                                    ((mascara_x[0][1]) * (imagem.dados[linha][coluna+1])) +
                                    ((mascara_x[0][2]) * (imagem.dados[linha][coluna+2])) +
                                    ((mascara_x[1][0]) * (imagem.dados[linha+1][coluna])) +
                                    ((mascara_x[1][1]) * (imagem.dados[linha+1][coluna+1])) +
                                    ((mascara_x[1][2]) * (imagem.dados[linha+1][coluna+2])) +
                                    ((mascara_x[2][0]) * (imagem.dados[linha+2][coluna])) +
                                    ((mascara_x[2][1]) * (imagem.dados[linha+2][coluna+1])) +
                                    ((mascara_x[2][2]) * (imagem.dados[linha+2][coluna+2]));

            resultado_mascara_y =   ((mascara_y[0][0]) * (imagem.dados[linha][coluna])) +
                                    ((mascara_y[0][1]) * (imagem.dados[linha][coluna+1])) +
                                    ((mascara_y[0][2]) * (imagem.dados[linha][coluna+3])) +
                                    ((mascara_y[1][0]) * (imagem.dados[linha+1][coluna])) +
                                    ((mascara_y[1][1]) * (imagem.dados[linha+1][coluna+1])) +
                                    ((mascara_y[1][2]) * (imagem.dados[linha+1][coluna+2])) +
                                    ((mascara_y[2][0]) * (imagem.dados[linha+2][coluna])) +
                                    ((mascara_y[2][1]) * (imagem.dados[linha+2][coluna+1])) +
                                    ((mascara_y[2][2]) * (imagem.dados[linha+2][coluna+2]));

             resultado_mascara_x *= resultado_mascara_x;
             resultado_mascara_y *= resultado_mascara_y;
             resultado_final  = resultado_mascara_x + resultado_mascara_y;
             resultado_final  = sqrt(resultado_final);
             imagem.dados[linha][coluna] = resultado_final;
        }
    }
    return;
}

int main()
{
    lerImagem();

    operadorPrewitt();

    criarImagem();

    return 0;
}
