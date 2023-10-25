#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <math.h>

void routine1(float* array1, float* array2, float* result, int n) {
    for (int i = 0; i < n; ++i) {
        result[i] = array1[i] + array2[i];
    }
}

void routine2(float* array1, float* array2, float* result, int n) {
    for (int i = 0; i < n/8; ++i) {
        result[i] = array1[i] + array2[i];
        result[i+((n/8))]=array1[1*8]+array2[1+8];
        result[i+((n/8)*2)]=array1[1+((n/8)*2)]+array2[1+((n/8)*2)];
        result[i+((n/8)*3)]=array1[1+((n/8)*3)]+array2[1+((n/8)*3)];
        result[i+((n/8)*4)]=array1[1+((n/8)*4)]+array2[1+((n/8)*4)];
        result[i+((n/8)*5)]=array1[1+((n/8)*5)]+array2[1+((n/8)*5)];
        result[i+((n/8)*6)]=array1[1+((n/8)*6)]+array2[1+((n/8)*6)];
        result[i+((n/8)*7)]=array1[1+((n/8)*7)]+array2[1+((n/8)*7)];
    }
}

int main() {
    int n;
    clock_t t1, t2;
    
    printf("Enter the value of n: ");
    scanf("%d", &n);

    float* A = (float*)malloc(n * sizeof(float));
    float* B = (float*)malloc(n * sizeof(float));
    float* C = (float*)malloc(n * sizeof(float));

    srand((unsigned)time(NULL));

    for (int i = 0; i < n; ++i) {
        A[i] = (float)(rand()%1000000);
        B[i] = (float)(rand()%1000000);
    }

    t1 = clock();
    routine1(A,B,C, n);
    t1= clock() - t1;
    double time_taken1 = ((double)t1)/CLOCKS_PER_SEC;

    t2 = clock();
    routine2(A,B,C, n);
    t2= clock() - t2;
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC;

    // Print the results (for testing purposes)
    /*
    for (int i = 0; i < n; ++i) {
        printf("array1[%d] = %f\n", i, array1[i]);
        printf("array2[%d] = %f\n", i, array2[i]);
        printf("array3[%d] = %f\n", i, array3[i]);
    } 
    */
    
    printf("\n time used routine 1: %f \n", time_taken1);
    printf("\n time used routine2: %f \n", time_taken2);

    int benchmark[21]={pow(2,4),pow(2,5),pow(2,6),pow(2,7),pow(2,8),pow(2,9),pow(2,10),pow(2,11),pow(2,12),pow(2,13),pow(2,14),pow(2,15),pow(2,16),pow(2,17),pow(2,18),pow(2,19),pow(2,20),pow(2,21),pow(2,22)};
    double time_routine1[19];
    double time_routine2[19];

    free(A);
    free(B);
    free(C);


    
    //for benchmarking
    
    for(int i=0; i<19; i++){
        n = benchmark[i];
        float* array4 = (float*)malloc(n * sizeof(float));
        float* array5 = (float*)malloc(n * sizeof(float));
        float* array6 = (float*)malloc(n * sizeof(float));

        for (int i = 0; i < n; ++i) {
        array4[i] = (float)(rand()%1000000);
        array5[i] = (float)(rand()%1000000);
        }

        t1 = clock();
        routine1(array4, array5, array6, n);
        t1= clock() - t1;
        double time_taken1 = ((double)t1)/CLOCKS_PER_SEC;
        time_routine1[i]=time_taken1;

        t2 = clock();
        routine2(array4, array5, array6, n);
        t2= clock() - t2;
        double time_taken2 = ((double)t2)/CLOCKS_PER_SEC;
        time_routine2[i]=time_taken2;

        free(array4);
        free(array5);
        free(array6);
    }

    // Free dynamically allocated memory
    printf("\n time routine 1: \n");
    for(int i = 0; i <19; i++){
        printf("%f, ",time_routine1[i]);
    }

    printf("\n time routine 2: \n");
    for(int i = 0; i <19; i++){
        printf("%f, ",time_routine2[i]);
    }
    

    return 0;
}
