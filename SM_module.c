/** \file SM_module.c
  * \brief Functions to compute the scattering map \f$ (I', \phi') = \sigma(I,\phi) \f$.
  *
  *	The degree (N,M) of the Fourier-Polynomial series are provided as
  *	parameters to functions SM, damped_SM.
  *
  * CALLED BY: SM, SM_given_I, P_error
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>       // M_PI
#include "FP_module.h"
#include "P_module.h"

const int SUCCESS = 0;
const int ERR_IC_OUTSIDE_DOM = 1;
const int ERR_ITER_DOES_NOT_CONVERGE = 2;

/** \brief Iteratively find \f$ \phi' = F(\phi'; I, \phi) \f$.
 *
 *  Variable \f$ \phi' \f$ is defined implicitly by equation
 *  \f\[ \phi' = \phi - \omega(I) - \pd{\gft}{I}(I, \phi'). \f\]
 *  Iterate the right hand side, starting with 
 *  \f\[ \phi'_0 = \phi - \omega(I), \f\]
 *  until \f$ \phi' \f$ converges.
 *
 * \return SUCCESS or ERR_ITER_DOES_NOT_CONVERGE.
 */
int iteration(size_t N, double Ap[N+1], double Bp[N+1], double omega, 
        double phi, double *phip)
{
    double phip_cur, phip_old;
    int iter;

    const int max_iter = 1000;

    phip_old = 4*M_PI;
    phip_cur = phi - omega;
    //printf("phip: %f\n", phip);
    iter=0;
    while(fabs(phip_cur - phip_old)>1.e-5 && iter<max_iter)
    {
        phip_old = phip_cur;
        phip_cur = phi - omega - dL_dI(N, Ap, Bp, phip_cur);
        //printf("phip: %f\n", phip);
        iter++;
    } 
    if(iter==max_iter) return(ERR_ITER_DOES_NOT_CONVERGE);

    *phip = constrainAngle(phip_cur);
    return(SUCCESS);
}

/** \brief Iteratively find \f$ \phi' = F(\phi'; I, \phi) \f$.
 *
 *  Variable \f$ \phi' \f$ is defined implicitly by equation
 *  \f\[ \phi' = \phi - \omega(I) - \pd{\gft}{I}(I, \phi'). \f\]
 *  Iterate the right hand side, starting with 
 *  \f\[ \phi'_0 = \phi - \omega(I), \f\]
 *  until \f$ \phi' \f$ converges.
 */
double damped_iteration(size_t N, double Ap[N+1], double Bp[N+1], double omega,
		double phi, double a)
{
    double phip, phip_old;

    phip_old = 4*M_PI;
    phip = phi - omega;
    //printf("phip: %f\n", phip);
    while(fabs(phip - phip_old)>1.e-10)
    {
        phip_old = phip;
        phip = phi - omega - a*dL_dI(N, Ap, Bp, phip);
        //printf("phip: %f\n", phip);
    } 
    return constrainAngle(phip);
}

/**
  * \brief Compute the scattering map \f$ (I', \phi') = \sigma(I,\phi) \f$.
  *
  * \note The degree of the Fourier-Polynomial expansion used is \f$N, L\f$
  * (provided as parameters to this function).
  *
  * \note If the initial condition \f$ (I, \phi) \f$ is outside the known
  * domain of the SM, we don't iterate. In that case, the function silently
  * returns \f$ (I, \phi) \f$ as the final condition.
  *
  * \note The angle \f$ \phi' \f$ is returned in [0,\pi), since the SM is
  * \pi-periodic.
  *
  * \retval SUCCESS success.
  * \retval ERR_IC_OUTSIDE_DOM when IC is outside domain of SM.
  * \retval ERR_ITER_DOES_NOT_CONVERGE when iteration does not converge.
  */
int SM(int N, int L, double ipA[N+1][L+1], double ipB[N+1][L+1], double
		ipOmega[L+1], double I, double phi, double *Ip, double *phip)
{
	double A[N+1];	/* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double B[N+1];	/* Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

    /* Derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Ap[N+1];	
	double Bp[N+1];	

    double omega;   /* Interpolated omega value at I */

    /* auxiliary variables */
    int iErr;

	if(I<=0 || I>8)	/* Initial condition is outside known domain of SM */
	//if(I<=0)	/* Initial condition is outside known domain of SM */
	{
		fprintf(stderr, "I.C. outside known domain of SM\n");
		*Ip = I;
		*phip = phi;
		return ERR_IC_OUTSIDE_DOM;
	}

    /* Compute Fourier coefs A_n(I), B_n(I) for action value I */
    coefs_eval(N,L,ipA,I,A);
    coefs_eval(N,L,ipB,I,B);

    /* Compute derivative of F. coefs A_n(I), B_n(I) for action value I */
    dcoefs_eval(N,L,ipA,I,Ap);
    dcoefs_eval(N,L,ipB,I,Bp);

    /* Compute omega(I) for action value I */
    omega_eval(L,ipOmega,I,&omega);

	/* Find the image (I', \phi') of (I,phi) by the transition map. */
    iErr = iteration(N, Ap, Bp, omega, phi, phip);
    if(iErr)
    {
        fprintf(stderr, "Iteration does not converge\n");
        return(ERR_ITER_DOES_NOT_CONVERGE);
    }

    *Ip = I + dL_dphi(N, A, B, *phip);
	return SUCCESS;
}


/**
  * \brief Compute the damped scattering map, damped by non-integrability
  * parameter \f$a\f$.
  *
  * NOTE:
  *		The degree of the Fourier-Polynomial expansion used is \f$N, M\f$ (provided
  *		as parameters to this function).
  *
  *		If the initial condition \f$ (I, \phi) \f$ is outside the known domain
  *		of the SM, we DO iterate. (To see what happens above/below tori [2,4].)
  *
  *		The angle \f$ \phi' \f$ is returned in [0,\pi), since the SM is
  *		\pi-periodic.
  *
  * \return SUCCESS or ERR_IC_OUTSIDE_DOM when IC is outside domain of SM.
  */
//int damped_SM(int nfour, int ntori, double ddA[nfour][ntori], 
//        double ddB[nfour][ntori], double ddOmega[ntori-1], int N, int M, double
//        I, double phi, double *Ip, double *phip, double a)
//{
//	double A[N+1];	/* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
//	double B[N+1];	/* Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */
//
//    /* Derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
//	double Ap[N+1];	
//	double Bp[N+1];	
//
//    double omega;   /* Interpolated omega value at I */
//
//	if(I<=0 || I>8)	/* Initial condition is outside known domain of SM */
//	//if(I<=0)	/* Initial condition is outside known domain of SM */
//	{
//		fprintf(stderr, "I.C. outside known domain of SM\n");
//		*Ip = I;
//		*phip = phi;
//		return ERR_IC_OUTSIDE_DOM;
//	}
//
//    /* Compute Fourier coefs A_n(I), B_n(I) for action value I */
//    coefs_eval(nfour,ntori,ddA,N,M,I,A);
//    coefs_eval(nfour,ntori,ddB,N,M,I,B);
//
//    /* Compute derivative of F. coefs A_n(I), B_n(I) for action value I */
//    dcoefs_eval(nfour,ntori,ddA,N,M,I,Ap);
//    dcoefs_eval(nfour,ntori,ddB,N,M,I,Bp);
//
//    /* Compute omega(I) for action value I */
//    omega_eval(ntori-1,ddOmega,M,I,&omega);
//
//	/* Find the image (I', \phi') of (I,phi) by the transition map. */
//    *phip = damped_iteration(N, Ap, Bp, omega, phi, a);
//    *Ip = I + a*dL_dphi(N, A, B, *phip);
//	return SUCCESS;
//}


