#include "math.h"
#include "stdio.h"

int main(){
    float** a;
    float* x;
    float* b;
    int n;
    printf("\nEnter the number of variables/equations: ");
    scanf("%d",&n);
    a = (float**)malloc(n*sizeof(float*));
    for(int i = 0;i < n;i++){
        a[i] = (float*)malloc(n*sizeof(float));
    }
    x = (float*)malloc(n*sizeof(float));
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
    return 0;
}