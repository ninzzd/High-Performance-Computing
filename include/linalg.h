#include "stdlib.h"
#include "math.h"
#pragma once
double vecl2nrm(double* a,int n);
double vecdot(double* a, double* b, int n);
double matvecdot(double** a, double* b, int n);
double matdot(double **a, double** b, int m, int n, int k);