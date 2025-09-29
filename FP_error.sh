# Compute global FP error over the global domain I\in[0,7]

PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make FP_error

# SM1
./FP_error 1 7 > FP_error.res
#gnuplot FP_error.plt
#mv FP_error.tex $IMGDIR

# SM2
./FP_error 2 7 > FP_error_SM2.res
#gnuplot FP_error_SM2.plt
#mv FP_error_SM2.tex $IMGDIR
