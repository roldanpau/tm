/** \file P_error.c
  * \brief Find the error of the Polynomial approximation.
  *
  * Find the error of the Polynomial approximation over the domain \f$
  * I\in[I_\min, I_\max] \f$. The local domain is chosen to be [0,3], while
  * the global domain is chosen [0,7].
  *
  * The error depends on the degree N of the Fourier expansion, and degree L of
  * the Polynomial expansion. Thus for each pair (N,L) we compute the error, and
  * print it to stdout.
  *
  * NOTES: 
  *		We measure only the error in the \f$ \phi \f$ component, not in
  *		\f$ I \f$. The error in \f$ I \f$ is measured in FP_error.c
  *
  *		Caller must specify which SM to use (SM1 or SM2) as a command-line
  *		argument.
  *
  * USAGE:	./P_error SM Imax > P_error.res, for example
  *			./P_error 1 7 > P_error.res
  *
  * CALLED BY: P_error.sh	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>		// fabs
#include "FP_module.h"
#include "P_module.h"
#include "SM_module.h"

static const char omega_FILE[] = "omega_all.res";
static const char omega_FILE_SM2[] = "omega_all_SM2.res";

static const char ipOmega_FILE[] = "ipOmega.res";
static const char ipOmega_FILE_SM2[] = "ipOmega_SM2.res";

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

int
main (int argc, char *argv[])
{
	const int nfour=65; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=8;		/* Number of tori used in numerical SM */

    /* For local SM, the max error is computed up to torus Imax only */
    int Imax;               

    /* Table containing for all tori, their Fourier coeffs */
    double A_all[ntori][nfour];
    double B_all[ntori][nfour];

    /* Table containing for all tori, their omega values */
    double omega_all[ntori-1];

	SM_t bSM;		/* Which SM (SM1 or SM2) */
    double I, phi;  /* (I, \phi) = Point in the domain of the SM */

    /* (I', \phi') = Image of (I, phi) by the NUMERICAL SM */
    double Ip, phip;    

    /* (\tilde I', \tilde \phi') = Image of (I, phi) by the SM SERIES */
    double tIp, tphip;

	double error; 
	double max_error_tor;	/* max approx. error over all points on torus I */
	double max_error;

	/* auxiliary vars */
	int iSM;
	char filename_dom[100];
	char filename_rng[100];
	FILE *fp_dom;
	FILE *fp_rng;
	double Itor, t;

	if(argc != 3)
	{
		fprintf(stderr, "Num of args incorrect. Usage: %s SM Imax\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	iSM = atoi(argv[1]);
	if(iSM==1)
		bSM = SM1;
	else
		bSM = SM2;

    Imax = atoi(argv[2]);
  
    /* Read table A_all, B_all with F. coefs of all tori */
    read_Fourier_coefs(ntori, nfour, bSM, A_all, B_all);

    /* Read table omega_all with omegas of all tori */
	if(bSM==SM1)	read_omegas(ntori-1,omega_FILE,omega_all); 
	else			read_omegas(ntori-1,omega_FILE_SM2,omega_all); 

	for(int N=2; N<nfour; N+=2)	/* N = Degree of Fourier expansion */
    {
        /* L = Degree of Polynomial expansion */
        for(int L=0; L<min(ntori-1, Imax); L++)	
        {
            /*** Compute coefs of FP series for SM ***/

            double ipA[N+1][L+1];   /* polyn interp of Fourier coeffs A_n(I) */
            double ipB[N+1][L+1];   /* polyn interp of Fourier coeffs B_n(I) */

            /* Compute FP series (polyn interp) */
            compute_FP(ntori,nfour,A_all,N,L,ipA);
            compute_FP(ntori,nfour,B_all,N,L,ipB);

            /*** Compute coefs of P series for Omega ***/

			double ipOmega[L+1]; 	/* polyn interp of omega(I) */

            /* Compute P series  */
            compute_P(ntori-1,omega_all,L,ipOmega);

            max_error = 0.0;
			/* We skip torus I=0, since error is 0 for that one */
            for(Itor=1; Itor<=Imax; Itor++)
            {
				if(bSM==SM1)
				{
					sprintf(filename_dom, "curve1_%d_%d_dom_0.res", 
							(int)Itor+1, (int)Itor+1);
					sprintf(filename_rng, "curve1_%d_%d_rng_0.res", 
							(int)Itor+1, (int)Itor+1);
				}
				else // SM==SM2
				{
					sprintf(filename_dom, "curve2_%d_%d_dom_0.res", 
							(int)Itor+1, (int)Itor+1);
					sprintf(filename_rng, "curve2_%d_%d_rng_0.res", 
							(int)Itor+1, (int)Itor+1);
				}

                fp_dom = fopen(filename_dom, "r");
                fp_rng = fopen(filename_rng, "r");

                max_error_tor = 0.0;

                /* For each numerical value of the transition map (I,\phi) ->
                 * (I',\phi'), 
                 */
                /* (1) Read I,\phi,I',\phi'. */
                while((fscanf(fp_dom,"%le %le %le", &I, &phi, &t) != EOF) && 
                        (fscanf(fp_rng,"%le %le %le", &Ip, &phip, &t) != EOF))	
                {
                    /* Scale I (I's are not scaled in curve1_%d_%d_dom_0.res) */
                    I = I*1000;
                    Ip = Ip*1000;

					/* Take angle mod \pi, due to periodicity */
					phip = constrainAngle(phip);
                
                    /* (2) Compute approximate SM using FT model. */
					SM(N, L, ipA, ipB, ipOmega, I, phi, &tIp, &tphip);

					/*
                    printf("Num. SM: (%f %f) -> %f \t Approx. SM: (%f %f) -> %f\n", 
                            I, phi, phip, 
                            I, phi, tphip);
							*/

                    /* (3) Find max approximation error over all points on
                     * torus I */
					error = constrainAngle(tphip - phip);
					error = (error<M_PI/2 ? error : M_PI - error);
                    if(error>max_error_tor) max_error_tor = error;
                    //printf("%f\n", error);
                }
                fclose(fp_dom);
                fclose(fp_rng);
                fprintf(stderr, "Max error for torus %d is: %f\n", (int)Itor, max_error_tor);
                if(max_error_tor>max_error) max_error = max_error_tor;
            }
            printf("%d %d %f\n", N, L, max_error);
        }
		printf("\n");
	}
	return 0;
}
