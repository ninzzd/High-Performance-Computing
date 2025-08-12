#include "math.h"
#include "stdio.h"
#include "string.h"
void printMats(float** a, float* b, float* x, int n){
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
        printf("%f\n",x[i]);
    }
}
void printVect(float* x, int n){
    printf("\n");
    for(int i = 0;i < n;i++){
        printf("%f\n",x[i]);
    }
}
int jacobiSolver(float** a, float* b, float* x_0, int n, float eta){
    float* x_k = (float*)malloc(n*sizeof(float));
    float* x_k1 = (float*)malloc(n*sizeof(float));
    int iter = 0;
    float max_err;
    do{
        if(iter == 0)
            memcpy(x_k,x_0,(size_t)n*sizeof(float));
        else
            memcpy(x_k,x_k1,(size_t)n*sizeof(float));
        for(int i = 0;i < n;i++){
            float sum = b[i];
            for(int j = 0;j < n; j++){
                if(j != i)
                    sum -= a[i][j]*x_k[j];
            }
            x_k1[i] = sum/a[i][i];
        }
        iter++;
        const char* suffix;
        switch(iter%10){
            case 1:
                suffix = "st";
                break;
            case 2:
                suffix = "nd";
                break;
            case 3:
                suffix = "rd";
                break;
            default:
                suffix = "th";
        }
        printf("%d%s iteration:\n",iter,suffix);
        printVect(x_k1,n);
        max_err = 0.0f;
        for(int i = 0;i < n;i++){
            if(fabsf(x_k1[i] - x_k[i]) > max_err)
                max_err = fabsf(x_k1[i] - x_k[i]);
        }
        printf("Max Error = %f\n",max_err);
    }while(max_err > eta);
    free(x_k);
    free(x_k1);
    return iter;
}
int main(){
    float** a;
    float* x_0;
    float* b;
    float eta;
    int n;
    printf("\nEnter the number of variables/equations: ");
    scanf("%d",&n);
    a = (float**)malloc(n*sizeof(float*));
    for(int i = 0;i < n;i++){
        a[i] = (float*)malloc(n*sizeof(float));
    }
    x_0 = (float*)malloc(n*sizeof(float));
    b = (float*)malloc(n*sizeof(float));
    printf("\nEnter the coefficients of the equations (elements of the A matrix):\n");
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            scanf("%f",&a[i][j]);
        }
    }
    printf("\nEnter the constants of the equations (elements of the B matrix):\n");
    for(int i = 0;i < n;i++){
        scanf("%f",&b[i]);
    }
    printf("\nEnter the initial guess x_0:\n");
    for(int i = 0;i < n;i++){
        scanf("%f",&x_0[i]);
    }
    printf("\nEnter the convergence threshold: ");
    scanf("%f",&eta);
    jacobiSolver(a,b,x_0,n,eta);
    return 0;
}