/** \file phase_port_SM.c
  * \brief Plot the phase portrait of the scattering map.
  *
  * Take a bunch (100) of initial conditions in the NHIM of the form (\f$
  * \phi=0, I\in[Imin,Imax] \f$) and iterate them by the SM many times (say,
  * 1000 iterations). The goal is to see if we can identify invariant tori,
  * chaotic zones, stable islands, etc.
  *
  * For each orbit 
  * \f[ (I_1, \phi_1) \to (I_2, \phi_2) \to \cdots \to (I_n, \phi_n) \f] 
  * we output the whole orbit itself, to be plotted as dots.
  *
  * \note Caller must specify which SM to use (SM1 or SM2) as a command-line
  * argument.
  *
  * USAGE:	
  *		./phase_port_SM iSM Imin Imax norb nit > file.res
  *		./phase_port_SM 1 0 7.5 100 1000 > phase_port_SM.res
  *
  * CALLED_BY: phase_port_SM.sh
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>		// M_PI
#include "FP_module.h"
#include "P_module.h"
#include "SM_module.h"

static const char ipOmega_FILE[] = "ipOmega.res";
static const char ipOmega_FILE_SM2[] = "ipOmega_SM2.res";

int
main (int argc, char *argv[])
{
	const int nfour=65; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=8;		/* Number of tori used in numerical SM */

    const int N = 8;    /* Degree of Fourier series */
    const int L = 4;    /* Degree of Taylor series */

	int norb;	/* Number of orbits */
	int nit;	/* Number of iterations of the SM */

    double ipA[N+1][L+1];   /* polyn interp of Fourier coeffs A_n(I) */
    double ipB[N+1][L+1];   /* polyn interp of Fourier coeffs B_n(I) */
    double ipOmega[L+1]; 	/* polyn interp of omega(I) */

    SM_t bSM;			/* Which SM (SM1 or SM2) */
    double I, phi;      /* (I, \phi) = Point in the domain of the SM */
    double Ip, phip;    /* (I', \phi') = Image of (I, phi) by the SM */

    double Imin, Imax;

    /* auxiliary vars */
    int iSM;
    int iErr;

    if(argc != 6)
    {
		fprintf(stderr, 
                "Num of args incorrect. \
               Usage: %s SM Imin Imax norbits niterations\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    iSM = atoi(argv[1]);
    if(iSM==1)
        bSM = SM1;
    else
        bSM = SM2;

    Imin = atof(argv[2]);
    Imax = atof(argv[3]);
	norb = atoi(argv[4]);
	nit = atoi(argv[5]);

    /* Read FP series (polyn interp) from file */
    read_FP(N,L,bSM,ipA,ipB);

    /* Read Polynomial series from file */
	if(bSM==SM1)	read_P(L,ipOmega_FILE,ipOmega);
	else			read_P(L,ipOmega_FILE_SM2,ipOmega);

	/* Iterate over all orbits */
	for(int i=0; i<= norb; i++)
	{
		/* Initialize initial condition */
		I = Imin+i*(Imax-Imin)/norb;
		//phi=0;
		for(int j=0; j< norb; j++)
		{
			phi = j*M_PI/norb;

			/* Iterate the SM nit times */
			for(int it=0; it<nit; it++)
			{
				// Skip first 10 (transient) iterates
				//if(it<10)
				//	continue;	

	/* Compute the SM: (I, phi) -> (Ip, phip) */
    iErr=SM(N, L, ipA, ipB, ipOmega, I, phi, &Ip, &phip);
    if(iErr)
    {
        fprintf(stderr, 
        "SM: Error computing the SM at I=%f, phi=%f\n", I, phi);
        continue;
    }
				I = Ip;
				phi = phip;

				/* Output iterate */
				if(Ip <= 8) printf("%f %f\n", Ip, phip);
			}
		}
	}
    return 0;
}
