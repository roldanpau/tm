progs = lin_interp spline_interp fft fdd Fourier_coefs_given_I \
		dLstar_dI Lstar dL_dphip omega \
		FP FP_error_given_I FP_error FT_newerror \
		interp_coef interp_omega interp_domega\
		P P_error T_newerror\
		SM SM_given_I \
		explore \
		phase_port_SM \
		IM \
		diffusion diffusion_greedy diffusion_triple_greedy \
		dijkstra diffusion_shortest_path diffusion_shortest_path_TM \
		diffusion_stoch \
		max_dLtilde_dI max_d2Ltilde_dI twist \
		orbit_error \
        diffusion_shortest_path_Iini_Ifin

objects = FP.o FP_module.o \
		  FP_error.o FT_newerror.o \
		  interp_coef.o interp_omega.o interp_domega.o \
		  dLstar_dI.o \
		  Lstar.o \
		  dL_dphip.o \
		  omega.o \
		  P.o P_module.o \
		  P_error.o T_newerror.o \
		  SM.o SM_module.o \
		  TM_module.o \
		  SM_given_I.o \
		  explore.o \
		  phase_port_SM.o \
		  IM.o IM_module.o \
		  diffusion.o diffusion_greedy.o diffusion_triple_greedy.o \
		  dijkstra.o dijkstra_module.o diffusion_shortest_path.o \
		  diffusion_shortest_path_TM.o \
		  diffusion_stoch.o \
		  max_dLtilde_dI.o max_d2Ltilde_dI.o twist.o \
		  orbit_error.o \
          diffusion_shortest_path_Iini_Ifin.o 

CFLAGS = -O3 #-g
LDFLAGS = -O3 #-g
LDLIBS = -lm -lgsl -lgslcblas

all: $(progs)

#	gcc -o lin_interp -ggdb lin_interp.c -lgsl
lin_interp: lin_interp.c
	gcc -o lin_interp lin_interp.c -lgsl

spline_interp: spline_interp.c
	gcc -o spline_interp spline_interp.c -lgsl

#ndft: ndft.c
#	gcc -o ndft ndft.c -lnfft3

fft: fft.c
	gcc -o fft fft.c -lgsl -lm

fdd: fdd.c
	gcc -o fdd fdd.c -lm

Fourier_coefs_given_I: Fourier_coefs_given_I.c
	gcc -o Fourier_coefs_given_I Fourier_coefs_given_I.c -lgsl

dLstar_dI: dLstar_dI.o FP_module.o

Lstar: Lstar.o FP_module.o

dL_dphip: dL_dphip.o FP_module.o

omega: omega.o FP_module.o

FP: FP.o FP_module.o 

FP_error_given_I: FP_error_given_I.c
	gcc -o FP_error_given_I -g FP_error_given_I.c -lgsl -lm

FP_error: FP_error.o FP_module.o

FT_newerror: FT_newerror.o FP_module.o

interp_coef: interp_coef.o FP_module.o

interp_omega: interp_omega.o P_module.o

interp_domega: interp_domega.o P_module.o

P: P.o P_module.o 

P_error: P_error.o P_module.o FP_module.o SM_module.o

T_newerror: T_newerror.o P_module.o FP_module.o SM_module.o

SM: SM.o SM_module.o FP_module.o P_module.o

SM_given_I: SM_given_I.o SM_module.o FP_module.o P_module.o

explore: explore.o SM_module.o FP_module.o P_module.o

phase_port_SM: phase_port_SM.o SM_module.o FP_module.o P_module.o

IM: IM.o IM_module.o P_module.o

diffusion: diffusion.o SM_module.o FP_module.o P_module.o IM_module.o

diffusion_greedy: diffusion_greedy.o SM_module.o FP_module.o P_module.o IM_module.o

diffusion_triple_greedy: diffusion_triple_greedy.o SM_module.o FP_module.o P_module.o IM_module.o

dijkstra: dijkstra.o dijkstra_module.o

diffusion_shortest_path: diffusion_shortest_path.o SM_module.o FP_module.o \
	P_module.o IM_module.o dijkstra_module.o

diffusion_shortest_path_TM: diffusion_shortest_path_TM.o TM_module.o \
	SM_module.o FP_module.o P_module.o IM_module.o dijkstra_module.o

diffusion_stoch: diffusion_stoch.o SM_module.o FP_module.o P_module.o IM_module.o
	gcc -o diffusion_stoch -g diffusion_stoch.c SM_module.c FP_module.c \
	P_module.c IM_module.c -lgsl -lm

max_dLtilde_dI: max_dLtilde_dI.o FP_module.o

max_d2Ltilde_dI: max_d2Ltilde_dI.o FP_module.o

twist: twist.o P_module.o FP_module.o

orbit_error: orbit_error.o SM_module.o FP_module.o P_module.o

diffusion_shortest_path_Iini_Ifin: diffusion_shortest_path_Iini_Ifin.o SM_module.o FP_module.o \
	P_module.o IM_module.o dijkstra_module.o

.PHONY : clean
clean:
	-rm $(progs) $(objects)
