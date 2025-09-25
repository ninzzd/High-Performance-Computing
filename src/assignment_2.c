#include "iter_solv.h"
#include "opt_solv.h"
int main(){
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
    int iter_sor_opt = sorSolver(a,b,x0,n,0.000001,w_opt,0,x);
    printf("Optimal w = %lf\n",w_opt);
    printf("No. of iterations = %d\n",iter_sor_opt);
    // ------------------------------------------------------------------------------------
    free(b);
    for(int i = 0;i < n;i++){
        free(a[i]);
    }
    free(a);
    return 0;
}