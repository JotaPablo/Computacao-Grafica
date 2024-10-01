#include <stdio.h>
#include <stdlib.h>

#define n_amostra 20 //No caso ficaria a inicial + (n_amostra - 2) + final

FILE *fpIni, *fpFim, *fpOut[n_amostra + 1]; //n_amostra + 1 para trabalharmos com o vetor começando de 1 e não de 0

int **imagemR_ini, **imagemB_ini, **imagemG_ini;
int **imagemR_fim, **imagemB_fim, **imagemG_fim;
int ncol, nlin, quantizacao;

//Matriz que vai servir pra saber a diferença entre o valor do pixel inicial e final de cada cor divido pelo numero de amostras
//Float pois a n_amostra pode ser muito grande e acabar que a divisão dê um valor decimal
float **imagemR_dif, **imagemB_dif, **imagemG_dif;

//Matriz que serve para guardar as amostras
int **imagemR_aux, **imagemB_aux, **imagemG_aux;



void abrir_arquivos(int argc, char *argv[]);
void ler_cabecalho(void);
void ler_imagem(void);
void fechar_arquivos(void);
void abrir_arquivos_de_saida(void);
void gravar_imagem(int x);
void cria_diferenca_e_aux(void);


int main(int argc, char *argv[]) {
    abrir_arquivos(argc,argv);
    ler_cabecalho();
    abrir_arquivos_de_saida();
    ler_imagem();
    cria_diferenca_e_aux();

    int lin, col;

    for(int i = 1; i <= n_amostra; i++) {

      for (lin=0;lin<nlin;lin++) {
        for (col=0;col<ncol;col++) {
            imagemR_aux[lin][col] = imagemR_ini[lin][col] + (i - 1) * imagemR_dif[lin][col];
            imagemG_aux[lin][col] = imagemG_ini[lin][col] + (i - 1) * imagemG_dif[lin][col];
            imagemB_aux[lin][col] = imagemB_ini[lin][col] + (i - 1) * imagemB_dif[lin][col];
        }
      }
      gravar_imagem(i);
    }

    fechar_arquivos();

    return 0;
}


void abrir_arquivos(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Modo correto de uso: <prog> <imagemIniciail> <imagemFinal>\n");
        exit(0);
    }

    if ((fpIni = fopen(argv[1], "r")) == NULL) {
        printf("Nao foi possivel abrir o arquivo de imagem %s\n", argv[1]);
        exit(1);
    }

    if ((fpFim = fopen(argv[2], "r")) == NULL) {
        printf("Nao foi possivel abrir o arquivo de imagem %s\n", argv[2]);
        exit(1);
    }


} // Fim: abrir_arquivos

void ler_cabecalho(void) {
     char controle[4];
     //Variaveis auxiliares para verificar se as imagens são de mesmo tamanho e tem a mesma quantização
     int ncol_ini, nlin_ini, ncol_fim, nlin_fim;
     int quantizacao_ini, quantizacao_fim;

     fscanf(fpIni,"%s\n",controle);
     fscanf(fpIni,"%d %d\n",&ncol_ini,&nlin_ini);
     fscanf(fpIni,"%d\n",&quantizacao_ini);

     fscanf(fpFim,"%s\n",controle);
     fscanf(fpFim,"%d %d\n",&ncol_fim,&nlin_fim);
     fscanf(fpFim,"%d\n",&quantizacao_fim);

     //Testa se as duas imagens tem o mesmo tamanho
     if(ncol_ini != ncol_fim || nlin_ini != nlin_fim){
        printf("As imagens precisam ser de mesmo tamanho\n");
        printf("%d x %d  e  %d x %d\n",ncol_ini, nlin_ini, ncol_fim, nlin_fim);
        exit(1);
     }

     //Testa se as duas imagens tem a mesma quantização
     //Provavelmente todas devem ter a mesma quantização pois exportamos do gimp mas colocamos isso só pelo teste.
     if(quantizacao_ini != quantizacao_fim){
        printf("A quantização precisa ser a mesma nas duas imagens\n");
        exit(1);
     }

     //Se não der erro, atribui esses valores as variaveis globais
     ncol = ncol_ini;
     nlin = nlin_ini;
     quantizacao = quantizacao_ini;


} // Fim: ler_cabecalho

//Função para abrir os arquivos de saída.
//Tem que ser depois de ler_cabeçalho pois se as imagens forem de tamanhos diferentes ou der algum erro, não criamos espaço inutil que precisa ser apagado
void abrir_arquivos_de_saida(void){

     // Loop para abrir os arquivos de saída
    for (int i = 1; i <= n_amostra; i++) {
        char nomeArquivo[20];
        sprintf(nomeArquivo, "Imagem%d.ppm", i);  // Formata o nome do arquivo

        if ((fpOut[i] = fopen(nomeArquivo, "w")) == NULL) {
            printf("Nao foi possivel abrir o arquivo de saida %s\n", nomeArquivo);
            exit(1);
        }
    }
}

void ler_imagem(void){
  int cont, col, lin;

  //Lê imagem inicial
  imagemR_ini= (int **)malloc((nlin+1)*sizeof(int *));
  imagemG_ini= (int **)malloc((nlin+1)*sizeof(int *));
  imagemB_ini= (int **)malloc((nlin+1)*sizeof(int *));
  for (cont=0;cont<nlin;cont++) {
    imagemR_ini[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemR_ini[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemG_ini[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemG_ini[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemB_ini[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemR_ini[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
  }
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      fscanf(fpIni,"%d ",&imagemR_ini[lin][col]);
      fscanf(fpIni,"%d ",&imagemG_ini[lin][col]);
      fscanf(fpIni,"%d ",&imagemB_ini[lin][col]);
    }
  }


  //Lê imagem final
  imagemR_fim= (int **)malloc((nlin+1)*sizeof(int *));
  imagemG_fim= (int **)malloc((nlin+1)*sizeof(int *));
  imagemB_fim= (int **)malloc((nlin+1)*sizeof(int *));
  for (cont=0;cont<nlin;cont++) {
    imagemR_fim[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemR_fim[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemG_fim[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemG_fim[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemB_fim[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemR_fim[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
  }
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      fscanf(fpFim,"%d ",&imagemR_fim[lin][col]);
      fscanf(fpFim,"%d ",&imagemG_fim[lin][col]);
      fscanf(fpFim,"%d ",&imagemB_fim[lin][col]);
    }
  }
}

//Função pra criar 3 matrizes R G B que representa a diferença entre o pixel inicial e o final dividido pelo numero de amostras.
//E outra para criar uma matriz auxiliar que vai armazenar uma amostra de cada vez
void cria_diferenca_e_aux(void){

  int cont, col, lin;

  imagemR_dif= (float **)malloc((nlin+1)*sizeof(float *));
  imagemG_dif= (float **)malloc((nlin+1)*sizeof(float *));
  imagemB_dif= (float **)malloc((nlin+1)*sizeof(float *));
  for (cont=0;cont<nlin;cont++) {
    imagemR_dif[cont]=(float *)malloc(ncol*sizeof(float));
    if (imagemR_dif[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemG_dif[cont]=(float *)malloc(ncol*sizeof(float));
    if (imagemG_dif[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemB_dif[cont]=(float *)malloc(ncol*sizeof(float));
    if (imagemR_dif[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
  }
  //Preenche com a diferença
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      imagemR_dif[lin][col] = (imagemR_fim[lin][col] - imagemR_ini[lin][col]) / (float) n_amostra - 1;
      imagemG_dif[lin][col] = (imagemG_fim[lin][col] - imagemG_ini[lin][col]) / (float) n_amostra - 1;
      imagemB_dif[lin][col] = (imagemB_fim[lin][col] - imagemB_ini[lin][col]) / (float) n_amostra - 1;
    }
  }

  //Aloca espaço para matriz auxiliar
  imagemR_aux= (int **)malloc((nlin+1)*sizeof(int *));
  imagemG_aux= (int **)malloc((nlin+1)*sizeof(int *));
  imagemB_aux= (int **)malloc((nlin+1)*sizeof(int *));
  for (cont=0;cont<nlin;cont++) {
    imagemR_aux[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemR_aux[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemG_aux[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemG_aux[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
    imagemB_aux[cont]=(int *)malloc(ncol*sizeof(int));
    if (imagemR_aux[cont]==NULL) { /* Alocar memoria para a matriz de pixels */
      printf("Falha na alocacao de memoria - 1\n");
      exit(1);
    }
  }



}

//Vai gravar uma imagem X, tal que a imagem_X = imagem_ini + diferença * (X-1)
void gravar_imagem(int x){

  int lin, col;
  fprintf(fpOut[x],"P3\n");
  fprintf(fpOut[x],"%d %d\n",ncol,nlin);
  fprintf(fpOut[x],"%d\n",quantizacao);
  for (lin=0;lin<nlin;lin++) {
    for (col=0;col<ncol;col++) {
      fprintf(fpOut[x],"%d ",imagemR_aux[lin][col]);
      fprintf(fpOut[x],"%d ",imagemG_aux[lin][col]);
      fprintf(fpOut[x],"%d ",imagemB_aux[lin][col]);
    }
    fprintf(fpOut[x],"\n");
  }
  fclose(fpOut[x]);

}

void fechar_arquivos(){
    fclose(fpIni);
    fclose(fpFim);
}
