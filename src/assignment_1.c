#include "iter_solv.h"
#include "stdio.h"
int main(){
    double** a;
    double* b;
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

    // ------------------------------------------------------------------------------------
    // *** FILE-INPUTTED MATRICES FOR TESTING ***
    FILE *kmat, *fvec, *kinfo;
    fGetMat(&kmat,&fvec,&kinfo);
    getMat(&a,&b,&n,kmat,fvec,kinfo);
    fclose(kmat);
    fclose(fvec);
    fclose(kinfo);
    double *res_gs, *res_j, *res_sor1, *res_sor2, *res_sor3, *x0, w1, w2 ,w3;
    res_j = (double*)malloc(n*sizeof(double));
    res_gs = (double*)malloc(n*sizeof(double));
    res_sor1 = (double*)malloc(n*sizeof(double));
    res_sor2 = (double*)malloc(n*sizeof(double));
    res_sor3 = (double*)malloc(n*sizeof(double));
    x0 = (double*)malloc(n*sizeof(double));
    for(int i = 0;i < n;i++){
        x0[i] = 0.0;
    }
    int iter_j, iter_gs, iter_sor1, iter_sor2, iter_sor3;
    w1 = 1.2;
    w2 = 1.4;
    w3 = 1.6;
    iter_j = jacobiSolver(a,b,x0,n,0.000001,0,res_j);
    iter_gs = gaussSeidelSolver(a,b,x0,n,0.000001,0,res_gs);
    iter_sor1 = sorSolver(a,b,x0,n,0.000001,w1,0,res_sor1);
    iter_sor2 = sorSolver(a,b,x0,n,0.000001,w2,0,res_sor2);
    iter_sor3 = sorSolver(a,b,x0,n,0.000001,w3,0,res_sor3);
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
    printf("SOR Factor: %lf\n",w3);
    printf("No. of iterations: %d\n",iter_sor3);
    printf("Result:\n");
    printVect(res_sor3,n);
    printf("------------\n");
    printf("Optimal SOR factor: %lf\n",sorOpt(a,n));
    free(res_j);
    free(res_gs);
    free(res_sor1);
    free(res_sor2);
    free(res_sor3);
    // ------------------------------------------------------------------------------------
    free(x0);
    free(b);
    for(int i = 0;i < n;i++){
        free(a[i]);
    }
    free(a);
    return 0;
}