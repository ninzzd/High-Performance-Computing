#include "cblas.h"
#include "lapacke.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "iter_solv.h"
#pragma once
int dot(double *a, double *b, double *res, int n);
double l2nrm(double *a, int n);
int steepestDescent(float *a, float *b, float* x_0, int n, float eta, int mode, float* result);