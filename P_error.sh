# Compute global P error over the global domain I\in[0,7]

PAPERDIR=.
IMGDIR=$PAPERDIR/images

make P_error

# SM1
printf "***** SM1: Computing global P error *****\n"
./P_error 1 7 > P_error.res
#gnuplot P_error.plt
#mv P_error.tex $IMGDIR

# SM2
printf "\n\n\n"
printf "***** SM2: Computing global P error *****\n"
./P_error 2 7 > P_error_SM2.res
#gnuplot P_error_SM2.plt
#mv P_error_SM2.tex $IMGDIR
