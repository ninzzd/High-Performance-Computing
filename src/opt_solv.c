#include <stdio.h>
#include <stdlib.h>

void steepestDescent(float *a, float *b, float* x_0, int n, float eta, int mode, float* result){
    
}
int main(){
    float** a;
    float* x_0;
    float* b;
    float eta;
    float w;
    int n;
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
    return 0;
}