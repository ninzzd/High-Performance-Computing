#include "iter_solv.h"
#include "opt_solv.h"
#include "fdm.h"
#include "time.h"
int main(){
    char sel;
    printf("Do you want to generate new FDM matrices? (yY/nN): \n");
    scanf(" %c",&sel);
    switch(sel){
        case 'y':
        case 'Y':
            generateFDM();
            break;
        case 'n':
        case 'N':
            break;
        default:
            printf("Invalid Input. Exiting.\n");
            return 0;
    }
    // generateFDM();
    // ------------------------------------------------------------------------------------
    double **a, *b, *x0, *x;
    int n;
    FILE *kmat, *fvec, *kinfo;
    fGetMat(&kmat,&fvec,&kinfo);
    getMat(&a,&b,&n,kmat,fvec,kinfo);
    fclose(kmat);
    fclose(fvec);
    fclose(kinfo);
    // ------------------------------------------------------------------------------------
    int sym = 1;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(a[i][j] != a[j][i])
                sym = 0;
        }
    }
    if(!sym){
        printf("A is not symmetric\n");
        printf("Assuming A <- 0.5(A+A^T)\n");
        for(int i = 0;i < n;i++){
            for(int j = 0;j < i;j++){
                double temp = 0.5*(a[i][j] + a[j][i]);
                a[i][j] = temp;
                a[j][i] = temp;
            }
        }
    }
    else{
        printf("A is symmetric\n");
        printf("Continuing with the same A\n");
    }
    double w_opt = sorOpt(a,n);
    x0 = (double*)malloc(n*sizeof(double));
    x = (double*)malloc(n*sizeof(double));
    for(int i = 0;i < n;i++){
        x0[i] = 0.0;
    }
    printf(" ---- Bauss-Seidel SOR with Optimal w ----\n");
    long long int iter_sor_opt = sorSolver(a,b,x0,n,0.000001,w_opt,0,x);
    printf("Optimal w = %lf\n",w_opt);
    printf("No. of iterations = %lld\n",iter_sor_opt);
    printf("Final solution:\n");
    printVect(x,n);
    printf(" ---- Steepest Gradient Descent ----\n");
    int iter_sd = steepestDescent(a,b,x0,n,0.000001,0,x);
    printf("No. of iterations = %d\n",iter_sd);
    // printf("Final solution:\n");
    // printVect(x,n);
    printf(" ---- Minimal Residual Gradient Descent ----\n");
    int iter_mr = minimalResidual(a,b,x0,n,0.000001,0,x);
    printf("No. of iterations = %d\n",iter_mr);
    // printf("Final solution:\n");
    // printVect(x,n);
    printf(" ---- Conjugate Gradient Descent ----\n");
    int iter_cg = conjugateGradient(a,b,x0,n,0.000001,0,x);
    printf("No. of iterations = %d\n",iter_cg);
    // printf("Final solution:\n");
    // printVect(x,n);
    printf(" ---- BICGSTAB ----\n");
    int iter_bicgstab = bicgstab(a,b,x0,n,0.000001,0,x);
    printf("No. of iterations = %d\n",iter_bicgstab);
    printf("Final solution:\n");
    printVect(x,n);
    // ------------------------------------------------------------------------------------
    free(b);
    free(x0);
    for(int i = 0;i < n;i++){
        free(a[i]);
    }
    free(a);
    return 0;
}