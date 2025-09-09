A = readmatrix('kmat.txt');
A = reshape(A, [140,140]); % varies according to no. of points in mesh

E = -1*tril(A, -1); % lower triangle 
D = diag(diag(A)); % diagonal 
F = -1*triu(A, 1); % upper triangle

% Jacobi Iteration Matrix 
% x(k+1) = D^-1(E+F)*x(k) + D^-1*b
J_iter = D \ (E+F);

% Gauss-Siedel Iteration Matrix 
% x(k+1) = [(D-E)^-1*F]*x(k) + [(D-E)^-1]*b
G_iter = (D-E) \ F;

% Successive Over Relaxation Iteration Matrix
% x(k+1) = [(D-w*E)^-1]*[w*F+(I-w)*D]*x(k) + ([D-w*E]^-1)*w*b
omega = 1.6
SOR_iter = (D - omega*E) \ (omega*F + (1-omega)*D); 


lambda_J = eig(J_iter);
rho_j = max(abs(lambda_J))

lambda_G = eig(G_iter);
rho_G = max(abs(lambda_G))

lambda_SOR = eig(SOR_iter); 
rho_SOR = max(abs(lambda_SOR)) 