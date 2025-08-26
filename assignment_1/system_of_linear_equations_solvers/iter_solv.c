#include "math.h"
#include "stdio.h"
#include "string.h"
void printMat(float** a, float* b, float* x, int n){
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
void printIter(int iter){
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
    printf("\n%d%s iteration:\n",iter,suffix);
}
// mode = 0 : Non-verbose, mode = 1 : Verbose
int jacobiSolver(float** a, float* b, float* x_0, int n, float eta, int mode, float* result){
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
        max_err = 0.0f;
        for(int i = 0;i < n;i++){
            if(fabsf(x_k1[i] - x_k[i]) > max_err)
                max_err = fabsf(x_k1[i] - x_k[i]);
        }
        if(mode){
            printIter(iter);
            printVect(x_k1,n);
            printf("Max Error = %f\n",max_err);
        }
    }while(max_err > eta);
    memcpy(result,x_k1,(size_t)n*sizeof(float));
    free(x_k);
    free(x_k1);
    return iter;
}
int gaussSeidelSolver(float** a, float* b, float* x_0, int n, float eta, int mode, float* result){
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
                if(j < i)
                    sum -= a[i][j]*x_k1[j];
                else if(j > i)
                    sum -= a[i][j]*x_k[j];
            }
            x_k1[i] = sum/a[i][i];
        }
        iter++;
        max_err = 0.0f;
        for(int i = 0;i < n;i++){
            if(fabsf(x_k1[i] - x_k[i]) > max_err)
                max_err = fabsf(x_k1[i] - x_k[i]);
        }
        if(mode){
            printIter(iter);
            printVect(x_k1,n);
            printf("Max Error = %f\n",max_err);
        }
    }while(max_err > eta);
    memcpy(result,x_k1,(size_t)n*sizeof(float));
    free(x_k);
    free(x_k1);
    return iter;
}
int sorGaussSeidelSolver(float** a, float* b, float* x_0, int n, float eta, float w, int mode, float* result){
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
                if(j < i)
                    sum -= a[i][j]*x_k1[j];
                else if(j > i)
                    sum -= a[i][j]*x_k[j];
            }
            x_k1[i] = sum/a[i][i];
            x_k1[i] = x_k[i] + w*(x_k1[i] - x_k[i]);
        }
        iter++;
        max_err = 0.0f;
        for(int i = 0;i < n;i++){
            if(fabsf(x_k1[i] - x_k[i]) > max_err)
                max_err = fabsf(x_k1[i] - x_k[i]);
        }
        if(mode){
            printIter(iter);
            printVect(x_k1,n);
            printf("Max Error = %f\n",max_err);
        }
    }while(max_err > eta);
    memcpy(result,x_k1,(size_t)n*sizeof(float));
    free(x_k);
    free(x_k1);
    return iter;
}
int main(){
    float** a;
    float* x_0;
    float* b;
    float eta;
    float w;
    int n;
    // ------------------------------------------------------------------------------------
    // *** USER-INPUTTED MATRICES FOR TESTING ***
    // printf("\nEnter the number of variables/equations: ");
    // scanf("%d",&n);
    // a = (float**)malloc(n*sizeof(float*));
    // for(int i = 0;i < n;i++){
    //     a[i] = (float*)malloc(n*sizeof(float));
    // }
    // x_0 = (float*)malloc(n*sizeof(float));
    // b = (float*)malloc(n*sizeof(float));
    // printf("\nEnter the coefficients of the equations (elements of the A matrix):\n");
    // for(int i = 0;i < n;i++){
    //     for(int j = 0;j < n;j++){
    //         scanf("%f",&a[i][j]);
    //     }
    // }
    // printf("\nEnter the constants of the equations (elements of the B matrix):\n");
    // for(int i = 0;i < n;i++){
    //     scanf("%f",&b[i]);
    // }
    // printf("\nEnter the initial guess x_0:\n");
    // for(int i = 0;i < n;i++){
    //     scanf("%f",&x_0[i]);
    // }
    // printf("\nEnter the convergence threshold: ");
    // scanf("%f",&eta);
    // printf("\nEnter the SoR factor: ");
    // scanf("%f",&w);
    // sorGaussSeidelSolver(a,b,x_0,n,eta,w);
    // ------------------------------------------------------------------------------------
    FILE *kmat, *fvec, *kinfo;
    char dir[255];
    char kmat_path[255];
    char kinfo_path[255];
    char fvec_path[255];
    printf("Enter the directory (absolute path) containing the files: 1) kinfo.txt 2) kmat.txt 3) fvec.txt:\n");
    scanf("%s",&dir);
    strcpy(kmat_path,dir);
    strcpy(kinfo_path,dir);
    strcpy(fvec_path,dir);
    strcat(kmat_path,"kmat.txt");
    strcat(kinfo_path,"kinfo.txt");
    strcat(fvec_path,"Fvec.txt");
    kmat = fopen(kmat_path, "r");
    kinfo = fopen(kinfo_path, "r");
    fvec = fopen(fvec_path, "r");
    int tempn;
    float tempf;
    fscanf(kinfo,"%d",&n);
    a = (float**)malloc(n*sizeof(float*));
    for(int i = 0;i < n;i++){
        a[i] = (float*)malloc(n*sizeof(float));
    }
    for(int i = 0;i < n*n;i++){
        fscanf(kmat,"%f",&a[i/n][i%n]);
    }
    b = (float*)malloc(n*sizeof(float));
    for(int i = 0;i < n;i++){
        fscanf(fvec,"%f",&b[i]);
    }
    float *res_gs, *res_j, *res_sor1, *res_sor2, *res_sor3, *x0, w1, w2 ,w3;
    res_j = (float*)malloc(n*sizeof(float));
    res_gs = (float*)malloc(n*sizeof(float));
    res_sor1 = (float*)malloc(n*sizeof(float));
    res_sor2 = (float*)malloc(n*sizeof(float));
    res_sor3 = (float*)malloc(n*sizeof(float));
    x0 = (float*)malloc(n*sizeof(float));
    for(int i = 0;i < n;i++){
        x0[i] = 0.0f;
    }
    int iter_j, iter_gs, iter_sor1, iter_sor2, iter_sor3;
    w1 = 1.2;
    w2 = 1.4;
    w3 = 1.6;
    iter_j = jacobiSolver(a,b,x0,n,0.000001,0,res_j);
    iter_gs = gaussSeidelSolver(a,b,x0,n,0.000001,0,res_gs);
    iter_sor1 = sorGaussSeidelSolver(a,b,x0,n,0.000001,w1,0,res_sor1);
    iter_sor2 = sorGaussSeidelSolver(a,b,x0,n,0.000001,w2,0,res_sor2);
    iter_sor3 = sorGaussSeidelSolver(a,b,x0,n,0.000001,w3,0,res_sor3);
    printf("------------\n");
    printf("Jacobi:\n");
    printf("No. of iterations: %d\n",iter_j);
    printf("Result:\n");
    printVect(res_j,n);
    printf("------------\n");

    printf("------------\n");
    printf("Gauss-Seidel:\n");
    printf("No. of iterations: %d\n",iter_gs);
    printf("Result:\n");
    printVect(res_gs,n);
    printf("------------\n");

    printf("------------\n");
    printf("SOR:\n");
    printf("SOR Factor: %f\n",w1);
    printf("No. of iterations: %d\n",iter_sor1);
    printf("Result:\n");
    printVect(res_sor1,n);
    printf("------------\n");

    printf("------------\n");
    printf("SOR:\n");
    printf("SOR Factor: %f\n",w2);
    printf("No. of iterations: %d\n",iter_sor2);
    printf("Result:\n");
    printVect(res_sor2,n);
    printf("------------\n");

    printf("------------\n");
    printf("SOR:\n");
    printf("SOR Factor: %f\n",w3);
    printf("No. of iterations: %d\n",iter_sor3);
    printf("Result:\n");
    printVect(res_sor3,n);
    printf("------------\n");
    free(res_j);
    free(res_gs);
    free(res_sor1);
    free(res_sor2);
    free(res_sor3);
    free(x0);
    free(b);
    for(int i = 0;i < n;i++){
        free(a[i]);
    }
    free(a);
    return 0;
}