#include "math.h"
#include "stdio.h"

int main(){
    float** a;
    float* x_k;
    float* b;
    int n;
    printf("\nEnter the number of variables/equations: ");
    scanf("%d",&n);
    a = (float**)malloc(n*sizeof(float*));
    for(int i = 0;i < n;i++){
        a[i] = (float*)malloc(n*sizeof(float));
    }
    x_k = (float*)malloc(n*sizeof(float));
    b = (float*)malloc(n*sizeof(float));
    printf("\nEnter the coefficients of the equations (elements of the A matrix): ");
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            scanf("%f",&a[i][j]);
        }
    }
    printf("\nEnter the constants of the equations (elements of the B matrix): ");
    for(int i = 0;i < n;i++){
        scanf("%f",&b[i]);
    }
    printf("\nEnter the initial guess x_0: ");
    for(int i = 0;i < n;i++){
        scanf("%f",&x_k[i]);
    }
    printf("\nMatrix A:\n");
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            printf("%f ",a[i][j]);
        }
        printf("\n");
    }
    printf("\nMatrix B:\n");
    for(int i = 0;i < n;i++){
        printf("%f\n",b[i]);
    }
    printf("\nMatrix X:\n");
    for(int i = 0;i < n;i++){
        printf("%f\n",x_k[i]);
    }
    return 0;
}