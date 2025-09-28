#include "opt_solv.h"
int steepestDescent(double **a, double *b, double* x0, int n, double eta, int mode, double* result){
    double *xk = (double*)malloc(n*sizeof(double));
    double *xk1 = (double*)malloc(n*sizeof(double));
    double *rk = (double*)malloc(n*sizeof(double));
    double rkl2nrm;
    int iter = 0;
    do{
        iter++;
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
        double rl2sq = 0.0;
        double rtar = 0.0;
        for(int i = 0;i < n;i++){
            rl2sq += rk[i]*rk[i];
        }
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                rtar += rk[i]*a[i][j]*rk[j];
            }
        }
        alpha = rl2sq/rtar;
        for(int i = 0;i < n;i++){
            xk1[i] = xk[i] + alpha*rk[i];
        }   
        rkl2nrm = cblas_dnrm2(n,rk,1);
        if(mode){
            printIter(iter);
            printf("x(%d) = ",iter);
            printVect(xk1,n);
            printf("L2 Norm of r(k) = %lf\n",rkl2nrm);
        }
        iter++;
    }while(rkl2nrm > eta);
    memcpy(result,xk1,n*sizeof(double));
    free(xk);
    free(xk1);
    free(rk);
    return iter;
}
int minimalResidual(double **a, double *b, double* x0, int n, double eta, int mode, double* result){
    double *xk = (double*)malloc(n*sizeof(double));
    double *rk = (double*)malloc(n*sizeof(double));
    double *pk = (double*)malloc(n*sizeof(double));
    double err;
    int iter = 0;
    for(int i = 0;i < n;i++){
        double ax = 0.0;
        for(int j = 0;j < n;j++){
            ax += a[i][j]*x0[j];
        }
        rk[i] = b[i] - ax;
    }
    do{
        iter++;
        if(iter == 1){
            memcpy(xk,x0,n*sizeof(double));
        }
        for(int i = 0;i < n;i++){
            double row = 0.0;
            for(int j = 0;j < n;j++){
                row += a[i][j]*rk[j];
            }
            pk[i] = row;
        }
        double alpha = cblas_ddot(n,rk,1,pk,1)/pow(cblas_dnrm2(n,pk,1),2.0);
        for(int i = 0;i < n;i++){
            xk[i] += alpha*rk[i];
        }
        for(int i = 0;i < n;i++){
            rk[i] -= alpha*pk[i];
        }
        err = cblas_dnrm2(n,rk,1);
    }while(err > eta);
    memcpy(result,xk,n*sizeof(double));
    return iter;
    free(xk);
    free(rk);
    free(pk);
    return 0;
}
int conjugateGradient(double **a, double *b, double *x0, int n, double eta, int mode, double *result){
    double *xk = (double*)malloc(n*sizeof(double));
    double *rk = (double*)malloc(n*sizeof(double));
    double *pk = (double*)malloc(n*sizeof(double));
    double *apk = (double*)malloc(n*sizeof(double));
    double err;
    int iter = 0;
    for(int i = 0;i < n;i++){
        double ax = 0.0;
        for(int j = 0;j < n;j++){
            ax += a[i][j]*x0[j];
        }
        rk[i] = b[i] - ax;
        pk[i] = rk[i];
    }
    do{
        iter++;
        if(iter == 1){
            memcpy(xk,x0,n*sizeof(double));
        }
        double *apk = (double*)malloc(n*sizeof(double));
        for(int i = 0;i < n;i++){
            double row = 0.0;
            for(int j = 0;j < n;j++){
                row += a[i][j]*pk[j];
            }
            apk[i] = row;
        }
        double alpha = cblas_ddot(n,rk,1,rk,1)/cblas_ddot(n,pk,1,apk,1);
        for(int i = 0;i < n;i++){
            xk[i] += alpha*pk[i];
        }
        double rt_dot_r = cblas_ddot(n,rk,1,rk,1);
        for(int i = 0;i < n;i++){
            rk[i] -= alpha*apk[i];
        }
        double beta = cblas_ddot(n,rk,1,rk,1)/rt_dot_r;
        for(int i = 0;i < n;i++){
            pk[i] = rk[i] + beta*pk[i];
        }
        err = cblas_dnrm2(n,rk,1);
        free(apk);
    }while(err > eta);
    memcpy(result,xk,n*sizeof(double));
    free(xk);
    free(rk);
    free(pk);
    free(apk);
    return iter;
}