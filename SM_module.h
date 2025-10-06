extern const int SUCCESS;
extern const int ERR_IC_OUTSIDE_DOM;
extern const int ERR_ITER_DOES_NOT_CONVERGE;

int SM(int N, int L, double ipA[N+1][L+1], double ipB[N+1][L+1], double
		ipOmega[L], double I, double phi, double *Ip, double *phip);
/*
int damped_SM(int nfour, int ntori, double ddA[nfour][ntori], 
        double ddB[nfour][ntori], double ddOmega[ntori-1], int N, int M, double
        I, double phi, double *Ip, double *phip, double a);
		*/
