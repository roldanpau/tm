/** \file P_module.h
  * \brief Functions to compute Polynomial series of \f$\omega(I)\f$ and write it to file.
  */

double constrainAngle(double x);

void read_omegas(size_t ntori, const char *fn, double omega_all[ntori]);

void compute_P(size_t ntori, double omega_all[ntori], int L, double ip[L+1]);

void write_P(size_t L, double ip[L+1], const char *fn);
void read_P(size_t L, const char *fn, double ip[L+1]);

void omega_eval(size_t L, double ip[L+1], double I, double *omega_p); 
void domega_eval(size_t ntori, double dd[ntori], size_t M, double I, double
        *domega_p); 
