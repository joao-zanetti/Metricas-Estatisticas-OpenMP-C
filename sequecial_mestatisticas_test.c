/*
    Devolep by João Zanetti
    https://github.com/joao-zanetti
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//gcc sequecial_t1.c -o sequencial -lm
//./sequencial


//MATRIZ É APENAS UM VETOR
//CADA A ELEMENTOS(A=ALUNOS) CONSECUTIVOS DO VETOR REPRESENTA UMA CIDADE 
//CADA A*C ELEMENTOS (C=NCIDADES) CONSECUTIOS DO VETOR REPRESENTA UMA REGIAO
//CADA A*C*R ELEMENTOS (R=NREGIOES) VETOR INTEIRO

void swap(double* a, double* b) { 
    double t = *a; 
    *a = *b; 
    *b = t; 
} 

double partition (double *arr, int low, int high) { 
    double pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
void quickSort(double *arr, double low, double high) 
{ 
    if (low < high) { 
        double pi = partition(arr, low, high); 
  
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

void calcula_media(double *matriz,double *media,double *mediaregiao,double *mediabrasil,
                     int lin, int col,int r,int c){
    int i,j;
    double soma,somabrasil;

    //calcula media cidades
    for(i=0;i<lin;i++){
        soma=0;
        for(j=0;j<col;j++){
            soma+=matriz[i*col+j];
        }
        media[i]=soma/j; 
    }   

    //calcula media regiao e brasil
    //cada i é uma regiao, cada j uma cidade
    soma=0;
    somabrasil=0;
    for(i=0;i<r;i++){
        soma=0;
        //calcula media por regiao
        for(j=0;j<c;j++){
            soma+=media[i*c+j];
        }
        mediaregiao[i]=soma/c;
        somabrasil+=mediaregiao[i];
    }
    //media brasil
    mediabrasil[0]=somabrasil/r;

}

void ordena_linhas(double *matrix,int lin,int col,int r,int c){
    int i,j;
    for(i=0; i<lin; i++){
        quickSort(matrix,(i*col),((i*col)+col)-1);
    }
}

void calcula_mediana(double *matriz, double *mediana,double *medianaregiao, double *medianabrasil,
                     int lin, int col,int r,int c) {  
    int i,j,init,end;

    ordena_linhas(matriz,lin,col,r,c);

    if(col%2==0){
      for (i=0;i<lin;i++) {
        mediana[i]+=matriz[(i*col)+(col/2)];
        mediana[i]+=matriz[((i*col)+(col/2)-1)];
        mediana[i]*=0.5;
        }
    }
    else{
      for (i=0;i<lin;i++) {
       mediana[i]=matriz[((i*col)+(col/2))];
      }
    }

    if((c*col)%2==0){
        for(j=0;j<r;j++){
            init=j*c*col;
            end=(init+(c*col))-1;
            //ordenaporregioes
            quickSort(matriz,init,end);
            medianaregiao[j]+=matriz[(init+((c*col)/2))];
            medianaregiao[j]+=matriz[(init+(((c*col)/2)-1))];
            medianaregiao[j]*=0.5;
        }
    }
    else{
        for(j=0;j<r;j++){
            init=j*c*col;
            end=(init+(c*col))-1;
            //ordenaporregioes
            quickSort(matriz,init,end);
            medianaregiao[j]=matriz[(init+((c*col)/2))];
        }
       
    }

    medianabrasil[0]=0;
    if((lin*col)%2==0){
        //ordenabrasil
        quickSort(matriz,0,((lin*col)-1));
        medianabrasil[0]+=matriz[((lin*col)/2)];
        medianabrasil[0]+=matriz[(((lin*col)/2)-1)];
        medianabrasil[0]*=0.5;
    }
    else{
        //ordenabrasil
        quickSort(matriz,0,((lin*col)-1));
        medianabrasil[0]=matriz[((lin*col)/2)];  
    } 
} 

void calcula_variancia(double *matriz, double *media,double *mediaregiao,double *mediabrasil,
                        double *variancia,double *varianciaregiao,
                        double *varianciabrasil, int lin, int col,int r,int c)
{
    int i,j,k,init,aux;
    double soma,somabrasil;

    //calcula variancia das cidades
    for(i=0;i<lin;i++){
        soma=0;
        for(j=0;j<col;j++){
            soma+=pow((matriz[i*col+j]-media[i]),2);
        }
        variancia[i]=soma/(col-1); 
    } 

    //calcula variancia das regioes e do brasil
    //cada i é uma regiao, cada j uma cidade
    somabrasil=0;
    soma=0;
    for(k=0;k<r;k++){
        soma=0;
        init=k*c*col;
        for(i=init;i<(init+(c*col));i++){
                soma+=pow((matriz[i]-mediaregiao[k]),2);
                somabrasil+=pow((matriz[i]-mediabrasil[0]),2);
        }
        varianciaregiao[k]=soma/((c*col)-1);
    }
    varianciabrasil[0]=somabrasil/((col*lin)-1);
}

void calcula_desvio_padrao(double *variancia,double *varianciaregiao,double *varianciabrasil
                            ,double *dp,double *dpregiao
                            ,double *dpbrasil,
                            int lin,int r)
{
    int i;
    //calcula desvio padrao por cidade
    for(i=0;i<lin;i++){
        dp[i]=sqrt(variancia[i]);
    }  
    //calcula desvio padrao por regiao
    for(i=0;i<r;i++){
        dpregiao[i]=sqrt(varianciaregiao[i]);
    }
    //calcula desvio padrao do brasil
    dpbrasil[0]=sqrt(varianciabrasil[0]);
}


void calcula_menor(double *matriz,double *menor,double *menorregiao,double *menorbrasil, 
                    int lin, int col,int r,int c){
    int i,j;
    //calcula menores cidades
    for(i=0;i<lin;i++){
        menor[i]=matriz[i*col];
        for(j=1;j<col;j++){
            if(matriz[i*col+j]<menor[i])
                menor[i]=matriz[i*col+j];
        }
    }
    
    //calcula menores regiao e brasil
    //cada i é uma regiao, cada j uma cidade
    menorregiao[0]=menor[0];
    menorbrasil[0]=menorregiao[0];
    for(i=0;i<r;i++){
        menorregiao[i]=menor[i*c];
        //calcula menor por regiao
        for(j=1;j<c;j++){
            if(menor[i*c+j]<menorregiao[i])
                menorregiao[i]=menor[i*c+j];
        }
        if(menorregiao[i]<menorbrasil[0])
            menorbrasil[0]=menorregiao[i];
    }

}


void calcula_maior(double *matriz,double *maior,double *maiorregiao,double *maiorbrasil,
                    int lin, int col,int r,int c){
    int i,j;

    //calcula maior cidades
    for(i=0;i<lin;i++){
        maior[i]=matriz[i*col];
        for(j=1;j<col;j++){
            if(matriz[i*col+j]>maior[i])
                maior[i]=matriz[i*col+j];
        }
    }

    //calcula maiores regiao e brasil
    //cada i é uma regiao, cada j uma cidade
    maiorregiao[0]=maior[0];
    maiorbrasil[0]=maiorregiao[0];
    for(i=0;i<r;i++){
        maiorregiao[i]=maior[i*c];
        //calcula maior por regiao
        for(j=1;j<c;j++){
            if(maior[i*c+j]>maiorregiao[i])
                maiorregiao[i]=maior[i*c+j];
        }
        if(maiorregiao[i]>maiorbrasil[0])
            maiorbrasil[0]=maiorregiao[i];
        
    }

}


//SE UTILIZAR A LEITURA DA MATRIZ POR .TXT a matriz deverá ser inicializada 
//COM ESTA FUNÇÃO
void inicializa_matriz(double *matriz,double *matrizordenada,int lin, int col,int s){
    int i,j;

    for(i=0;i<lin*col;i++){
        matriz[i]=rand()%s;
        matrizordenada[i]=matriz[i];
        //printf("%.1lf ",matriz[i]);
    }
}


void calcular_melhores(double *mediaregiao,double *media,int *melhorreg,int *melhorregcid,int *melhorcid,
                    int r,int c){
    int i,j,auxreg,auxcid;

    auxreg=mediaregiao[0];
    auxcid=media[0];
    for (i=0;i<r;i++){
        if(mediaregiao[i]>auxreg){
            auxreg=mediaregiao[i];
            melhorreg[0]=i;
        }   
        for(j=i*c;j<((i*c)+c);j++){
            if(media[j]>auxcid){
                auxcid=media[j];
                melhorregcid[0]=i;
                melhorcid[0]=j%c;
            }
        }
    }
}



int main(int argc,char **argv){

    int r,c,a,s,i,j,lin,col,melhorreg,melhorregcid,melhorcid; 
    double *matriz,*mediana,*media,*menor,*variancia,*dp,*maior,*maiorregiao,
            *menorregiao,menorbrasil,maiorbrasil,*mediaregiao,mediabrasil,dpbrasil,
            *varianciaregiao,varianciabrasil,*dpregiao,*medianaregiao,*matrizordenada,
            medianabrasil; 

    //LEITURA ARQUIVO
    /*
    fscanf(stdin, "%d\n", &r); //regiões
    fscanf(stdin, "%d\n", &c); //número de cidades
    fscanf(stdin, "%d\n", &a); //número de alunos por cidade
    fscanf(stdin, "%d", &s); //semente usada antes de gerar os nrs aleatórios
    //TESTE: INPUT EXEMPLO DO PDF
    */
    r=3;
    c=4;
    a=6;
    s=7;

    lin=r*c;
    col=a;

    //---ALOCAÇÕES:

    //TESTE:ALOCANDO MATRIZ ESTATICAMENTE
    double matrix[72]= {30,40,20,80,85,10,
                    10,20,30,40,50,60,
                    60,50,40,30,20,10,
                    70,55,35,80,95,27,
                    35,45,25,85,90,15,
                    15,25,35,45,55,65,
                    65,55,45,35,25,15,
                    75,60,40,85,100,32,
                    20,30,10,70,75,0,
                    0,10,20,30,40,50,
                    50,40,30,20,10,0,
                    60,45,25,70,85,17};
    matriz=matrix;

    //Matriz utilizada na funcao mediana
    //No calculo das medianas, achei melhor fazer uma copia da matriz original
    //Pois na funcao que calcula as medianas, a matriz original tem que ser alterada 3 vezes
    double matrixordenada[72]= {30,40,20,80,85,10,
                    10,20,30,40,50,60,
                    60,50,40,30,20,10,
                    70,55,35,80,95,27,
                    35,45,25,85,90,15,
                    15,25,35,45,55,65,
                    65,55,45,35,25,15,
                    75,60,40,85,100,32,
                    20,30,10,70,75,0,
                    0,10,20,30,40,50,
                    50,40,30,20,10,0,
                    60,45,25,70,85,17};
    matrizordenada=matrixordenada;


    //aloca matriz 
    //matriz=(double *)malloc(lin*col*sizeof(double)); //Aloca a matriz
    //copia da matriz que sera utilizada na mediana, pois a mediana altera a matriz 3 vezes
    //matrizordenada=(double *)malloc(lin*col*sizeof(double));

    // aloca vetores de cidades
    media=(double *)malloc(lin* sizeof(double)); //Aloca o vetor de media de Cidades
    mediana=(double *)malloc(lin* sizeof(double)); //Aloca o vetor de mediana de Cidades
    variancia=(double *)malloc(lin * sizeof(double)); //Aloca o vetor de variancia de Cidades
    dp=(double *)malloc(lin * sizeof(double)); //Aloca o vetor de desvio padrão de Cidades
    menor=(double *)malloc(lin * sizeof(double)); //Aloca o vetor de menor de Cidades
    maior=(double *)malloc(lin * sizeof(double)); //Aloca o vetor de maior de Cidades

    //aloca vetores de regiões
    menorregiao=(double *)malloc(r * sizeof(double)); //Aloca o vetor de menor de regioes
    maiorregiao=(double *)malloc(r * sizeof(double)); //Aloca o vetor de maior de regioes
    mediaregiao=(double *)malloc(r * sizeof(double)); //Aloca o vetor de media de regioes
    medianaregiao=(double *)malloc(r * sizeof(double)); //Aloca o vetor de media de regioes
    varianciaregiao=(double *)malloc(r * sizeof(double)); //Aloca o vetor de variancia de regioes
    dpregiao=(double *)malloc(r * sizeof(double)); //Aloca o vetor de desvio padrao de regioes  

    //---FUNÇÕES

    //inicializa matriz com a determinada seed
    //inicializa_matriz(matriz,matrizordenada,lin,col,s); 

    calcula_media(matriz,media,mediaregiao,&mediabrasil,lin,col,r,c);

    calcula_mediana(matrizordenada,mediana,medianaregiao,&medianabrasil,lin,col,r,c);

    calcula_variancia(matriz,media,mediaregiao,&mediabrasil,variancia,varianciaregiao,&varianciabrasil,lin,col,r,c);
    calcula_desvio_padrao(variancia,varianciaregiao,&varianciabrasil,dp,dpregiao,&dpbrasil,lin,r);

    calcula_menor(matriz,menor,menorregiao,&menorbrasil,lin,col,r,c); 

    calcula_maior(matriz,maior,maiorregiao,&maiorbrasil,lin,col,r,c); 

    calcular_melhores(mediaregiao,media,&melhorreg,&melhorregcid,&melhorcid,r,c);

    printf("\n");
    for(i= 0; i <r; i++){
        for ( j = 0; j<c; j++){
            printf("Reg: %d - Cid %d:menor: %.0lf, maior:%.0lf, mediana:%.2lf, media%.2lf e DP:%.2lf\n"
            ,i,j,menor[((i*c)+j)],maior[((i*c)+j)],mediana[((i*c)+j)],media[((i*c)+j)],dp[((i*c)+j)]);
        }
        printf("\n");
    }

    for(i= 0; i <r; i++){
        printf("Reg: %d:menor: %.0lf, maior:%.0lf, mediana:%.2lf, media%.2lf e DP:%.2lf\n"
        ,i,menorregiao[i],maiorregiao[i],medianaregiao[i],mediaregiao[i],dpregiao[i]);
    }
    printf("\n");

    printf("Brasil:menor: %.0lf, maior:%.0lf, mediana:%.2lf, media%.2lf e DP:%.2lf\n"
        ,menorbrasil,maiorbrasil,medianabrasil,mediabrasil,dpbrasil);
    printf("\n");

    printf("Melhor regiao: %d\n",melhorreg);
    printf("Melhor cidade: Regiao %d, Cidade %d\n",melhorregcid,melhorcid);
    printf("\n");
    
    //FREE
    //free(matriz); //Desaloca a matriz
    free(media); //Desaloca o vetor de media
    free(maior); //Desaloca o vetor de maior
    free(mediana); //Desaloca vetor de mediana
    free(menor); //Desaloca vetor de menor
    free(variancia);  //Desaloca vetor de variância
    free(dp); //Desaloca vetor de desvio padrão
    free(mediaregiao); //Desaloca o vetor de media
    free(maiorregiao); //Desaloca o vetor de maior
    free(medianaregiao); //Desaloca vetor de mediana
    free(menorregiao); //Desaloca vetor de menor
    free(varianciaregiao);  //Desaloca vetor de variância
    free(dpregiao); //Desaloca vetor de desvio padrão
}   