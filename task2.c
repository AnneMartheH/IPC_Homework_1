#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(){
    srand(time(NULL));
    clock_t t, t1;

    int n;
    printf("Decide the size of n: ");
    scanf("%d", &n);

    int b;
    printf("Decide the block size, b: ");
    scanf("%d", &b);

    //int matrix1[n][n], matrix2[n][n], matrix3[n][n]; 
    //__________________________________--
    int **matrix1, **matrix2, **matrix3;
    matrix1 = (int **)malloc(n * sizeof(int *));
    matrix2 = (int **)malloc(n * sizeof(int *));
    matrix3 = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix1[i] = (int *)malloc(n * sizeof(int));
        matrix2[i] = (int *)malloc(n * sizeof(int));
        matrix3[i] = (int *)malloc(n * sizeof(int));
    }
    //________________________________
    int n_b = n/b;
    int total_number_blocks = (n_b*n_b);
    printf("\ntotalt antall blokker; %d, n/b; %d \n", total_number_blocks, n_b);
    int reversed_block_number = total_number_blocks;
    
    printf("\n matrix: ");
    for (int i = 0; i<n; i++){
        for (int j=0; j<n; j++){
            matrix1[i][j]=  rand()%20;
            int b = matrix1[i][j];
            matrix2[i][j]=1;
            matrix3[i][j]=1;
            //printf(" %d", b);
        }
    } 
    //printf("\n dette er matrise blokkne: \n");

    //sequential
    /*
    _______________________________________________________________________
    routine1
    _______________________________________________________________________
    */
    t = clock();
    for (int block_number = 0; block_number < total_number_blocks; block_number++ ){
        --reversed_block_number;
        for(int row = 0; row < b; row++){
            for(int colum = 0; colum <b; colum++ ){
                //printf("dette er matrise %d, rad: %d, kolonne %d, verdi: %d \n ",block_number,row,colum,matrix1[(b*(block_number/n_b)+row)][b*(block_number%n_b)+colum]);
                matrix2[(b*(reversed_block_number/n_b)+row)][b*(reversed_block_number%n_b)+colum]=matrix1[(b*(block_number/n_b)+row)][b*(block_number%n_b)+colum];
            }
        }
    }
    t=clock()-t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n time used: %f", time_taken);
    printf("\n");

   //print 
   /*
    printf("\n matrix2: ");
    for (int i = 0; i<n; i++){
        for (int j=0; j<n; j++){
            int b = matrix2[i][j];
            printf(" %d", b);
        }
    }
    */


    //parallelised
    /*
    _______________________________________________________________________
    routine2
    _______________________________________________________________________
    */
    int reversed_block_number_half = total_number_blocks/2;
    reversed_block_number=total_number_blocks;

    t1= clock();
        for (int block_number = 0; block_number < total_number_blocks/2; block_number++ ){
        reversed_block_number-=1;
        --reversed_block_number_half;
        for(int row = 0; row < b; row++){
            for(int colum = 0; colum <b; colum++ ){
                matrix3[(b*(reversed_block_number/n_b)+row)][b*(reversed_block_number%n_b)+colum]=matrix1[(b*(block_number/n_b)+row)][b*(block_number%n_b)+colum];
                matrix3[(b*(reversed_block_number_half/n_b)+row)][b*(reversed_block_number_half%n_b)+colum]=matrix1[(b*((block_number+(total_number_blocks/2))/n_b)+row)][b*((block_number+total_number_blocks/2)%n_b)+colum];
            }
        }
    }
    t1 = clock()-t1;
    double time_taken1 = ((double)t)/CLOCKS_PER_SEC;
    printf("\n time used par: %f", time_taken1);
    printf("\n");

//print
/*
    printf("\n matrix3: ");
    for (int i = 0; i<n; i++){
        for (int j=0; j<n; j++){
            int b = matrix3[i][j];
            printf(" %d", b);
        }
    }
*/

//effective bandwith:
int br= n*n*4;
int bw = n*n*4;
int e_bw1 = ((br+bw)/pow(10,9))/time_taken;
int e_bw2 = ((br+bw)/pow(10,9))/time_taken1;

//time and bandwith prints
    printf("\n time used: %f, bandwith: %d", time_taken, e_bw1);
    printf("\n time used par: %f, bandwith: %d", time_taken1, e_bw2);

    free(matrix1);
    free(matrix2);
    free(matrix3);

    } 

