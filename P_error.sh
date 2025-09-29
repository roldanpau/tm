# Compute global P error over the global domain I\in[0,7]

PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make P_error

# SM1
./P_error 1 7 > P_error.res
#gnuplot P_error.plt
#mv P_error.tex $IMGDIR

# SM1
./P_error 2 7 > P_error_SM2.res
#gnuplot P_error_SM2.plt
#mv P_error_SM2.tex $IMGDIR
