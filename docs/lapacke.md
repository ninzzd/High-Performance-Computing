## LAPACKE (Linear Algebra PACKage Extension)
Here's a list of functions from LAPACKE used in the source code of libhpsc:

---
`int LAPACKE_dgeev(int matrix_layout, char jobvl, char jobvr, int n, double *a, int lda, double *wr, double *wi, double *vl, int ldvl, double *vr, int ldvr)`

*Purpose*: To find the complex eigenvalues and eigenvectors of matrix A

$\lambda$ $\in$ $\Complex$ is said to be an eigenvalue of $A$ $\in$ $\real^{n \times n}$ if $\exist$ $v$ $\in$ $\real^n$ s.t. $A.v = \lambda.v$

$v$ $\in$ $\real^n$ is said to be a right eigenvector of $A$ $\in$ $\real^{n \times n}$ if $\exist$ $\lambda$ $\in$ $\Complex$ s.t. $A.v = \lambda.v$

$v$ $\in$ $\real^n$ is said to be a left eigenvector of $A$ $\in$ $\real^{n \times n}$ if $\exist$ $\lambda$ $\in$ $\Complex$ s.t. $v.A = \lambda.v$

*Parameters:*
  
- `matrix_layout` : Identifies the matrix layout of $A$, i.e. if it is a row-major or a column-major matrix.
- `jobvl`: 
