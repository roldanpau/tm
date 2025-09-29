/** \file FP_module.h
  * \brief Functions to compute Fourier-Polynomial series and write it to file. Given \f$ (I,\phi') \f$, find \f$ pd{L^*}{\phi'} \f$.
  *
  * NOTES: 
  *		Fourier coeffs are read from files coeffs_*.res, which were generated
  *		by fft.sh
  *
  */

/** Specifies which scattering map (SM1 or SM2).
  */
typedef enum {SM1, SM2} SM_t;

void read_Fourier_coefs(size_t ntori, size_t nfour, SM_t SM,
		double A_all[ntori][nfour], double B_all[ntori][nfour]);

void compute_FP(size_t ntori, size_t nfour, double coefs_all[ntori][nfour], int
		N, int L, double C[N+1][L+1]);

void write_FP(size_t N, size_t L, SM_t SM, double ipA[N+1][L+1], double
		ipB[N+1][L+1]);
void read_FP(size_t N, size_t L, SM_t SM, double ipA[N+1][L+1], double
		ipB[N+1][L+1]);

void coefs_eval(size_t N, size_t L, double C[N+1][L+1], double I, double
		A[N+1]);

void dcoefs_eval(size_t N, size_t L, double ipA[N+1][L+1], double I, double
		Ap[N+1]);
void d2coefs_eval(size_t nfour, size_t ntori, double ipA[nfour][ntori], size_t N,
		size_t M, double I, double App[N+1]);


double dL_dphi(size_t N, double A[N+1], double B[N+1], double phi);
double dL_dI(size_t N, double Ap[N+1], double Bp[N+1], double phi);
double d2L_dI(size_t N, double App[N+1], double Bpp[N+1], double phi);
double d2L_dphidI(size_t N, double Ap[N+1], double Bp[N+1], double phi);
double widetildeL(size_t N, double A[N+1], double B[N+1], double phip);
