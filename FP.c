/** \file FP.c
  * \brief Compute Fourier-Polynomial series and write it to file. Given \f$ (I,\phi') \f$, find \f$ pd{L^*}{\phi'} \f$.
  *
  * First and foremost, compute the coefficients of the Fourier-Polynomial
  * series, in the form of polynomial interpolation ipA and ipB. Write them
  * to file ipA.res and ipB.res. 
  *
  * Given \f$ (I,\phi') \f$, find the value of the Fourier-Polynomial series at
  * that point: 
  * \f\[ pd{L^*}{\phi'} = \sum_{n=1}^{N} (B_n(I) \sin{n\phi'} + A_n(I)
  * \cos{n\phi'}). \f\]
  *
  *	The degree (N,L) of the Fourier-Polynomial series can be modified in the code.
  *
  * This function is used to approximate the transition map, because
  * \f\[ I'    = I + pd{L^*}{\phi'}. \f\]
  *
  * NOTES: 
  *		Fourier coeffs are read from files coeffs_*.res, which were generated
  *		by fft.sh. 
  *
  *		Do the same for the second scattering map, reading coeffs from files
  *     coeffs_*_SM2.res, and writing coeffs to ipA_SM2.res and ipB_SM2.res.
  *
  *		For now, we use the same degree (N,L) of FP expansion for both SM1 and
  *		SM2.
  *
  * USAGE:	./FP I phi', for example
  *			./FP 2 0
  *
  * CALLED BY:	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "FP_module.h"

int
main (int argc, char *argv[])
{
	const int nfour=65; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=8;		/* Number of tori used in numerical SM */

	/* Table containing for all tori, their Fourier coeffs */
	double A_all[ntori][nfour];	
	double B_all[ntori][nfour];	

	const int N=4;	/* Degree of Fourier expansion */
	const int L=7;	/* Degree of Polynomial expansion */

	double A[N+1];	/* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double B[N+1];	/* Fourier coefficients B_0(I), B_1(I), ..., B_N(I) */

	double Ap[N+1];	/* Derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Bp[N+1];	/* Derivative of Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

	double ipA[N+1][L+1];	/* polyn interp of Fourier coeffs A_n(I) */
	double ipB[N+1][L+1];	/* polyn interp of Fourier coeffs B_n(I) */

    double I, phip;

    if(argc != 3)
    {
        fprintf(stderr, "Num of args incorrect. Usage: %s scaled_I phip\n",
              argv[0]);
        exit(EXIT_FAILURE);
    }

    I = atof(argv[1]);	/* scaled action level, e.g. I=2 */
	assert(I==4);
    phip = atof(argv[2]);	/* \phi' */


	/*** Compute coefs of FP series for SM1 ***/

    /* Read table A_all, B_all with F. coefs of all tori */
    read_Fourier_coefs(ntori, nfour, SM1, A_all, B_all);

    /* Compute FP series (polyn interp) */
    compute_FP(ntori,nfour,A_all,N,L,ipA);	
    compute_FP(ntori,nfour,B_all,N,L,ipB);

    /* Write FP series to file */
    write_FP(N,L,SM1,ipA,ipB);


	/*** Evaluate FP series of SM1 at (I, phip) ***/

    /* Read FP series (divided differences) from file */
    read_FP(N,L,SM1,ipA,ipB);

	/* Find the image I' of (I,phi) by the transition map. */
    coefs_eval(N,L,ipA,I,A);	/* Compute F. coefs A_n(I) for action value I */
    coefs_eval(N,L,ipB,I,B);	/* Compute F. coefs B_n(I) for action value I */

	printf("I: %f, Numerical B1(I=4): %.15e, Approx B1(I=4): %.15e\n", I,
			B_all[4][1], B[1]);
    printf("(I,phip)=(%f,%f)\t Ip=%f\n", I, phip, I + dL_dphi(N, A, B, phip));

	/* Find dL_dphi(I,phi'). */
    dcoefs_eval(N,L,ipA,I,Ap);	/* Compute F. coefs A_n(I) for action value I */
    dcoefs_eval(N,L,ipB,I,Bp);	/* Compute F. coefs B_n(I) for action value I */

    printf("%f %f %f\n", I, phip, dL_dI(N, Ap, Bp, phip));
	

	/*** Compute coefs of FP series for SM2 ***/

    /* Read table A_all, B_all with F. coefs of all tori */
    read_Fourier_coefs(ntori, nfour, SM2, A_all, B_all);

    /* Compute FP series (polyn interp) */
    compute_FP(ntori,nfour,A_all,N,L,ipA);	
    compute_FP(ntori,nfour,B_all,N,L,ipB);

    /* Write FP series to file */
    write_FP(N,L,SM2,ipA,ipB);

    return 0;
}
