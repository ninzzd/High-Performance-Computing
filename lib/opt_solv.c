#include "opt_solv.h"
int steepestDescent(double **a, double *b, double* x0, int n, double eta, int mode, double* result){
    double *xk = (double*)malloc(n*sizeof(double));
    double *xk1 = (double*)malloc(n*sizeof(double));
    double *rk = (double*)malloc(n*sizeof(double));
    double max_err;
    int iter = 1;
    do{
        if(iter == 1)
            memcpy(xk,x0,n*sizeof(double));
        else
            memcpy(xk,xk1,n*sizeof(double));
        for(int i = 0;i < n;i++){
            double ax = 0.0;
            for(int j = 0;j < n;j++){
                ax += a[i][j]*xk[j];
            }
            rk[i] = b[i] - ax;
        }
        double alpha = 0.0;
        double rl2 = 0.0;
        for(int i = 0;i < n;i++){
            rl2 += rk[i]*rk[i];
        }
        rl2 = sqrt(rl2);
        
    }while(max_err > eta);
}