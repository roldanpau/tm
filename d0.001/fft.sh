BINDIR=..
PAPERDIR=.
IMGDIR=$PAPERDIR/images
TORMIN=2
TORMAX=8

cd $BINDIR
make spline_interp fft
cd -

# SM1
printf "***** SM1: Interpolating curves and performing DFT *****\n"
for ((k=TORMIN; k <=TORMAX; k++))
do
	# swap columns 1 and 2, and sort curve points according to phi_+
	LC_ALL=C awk -f $BINDIR/swap.awk curve1_${k}_${k}_rng_0.res | LC_ALL=C \
	sort -g -k 1,1 > curve_${k}_SM1

	# to perform DFT, interpolate curve on just 128 points
	$BINDIR/spline_interp curve_${k}_SM1 > curve_${k}_interp_SM1

	# perform DFT
	$BINDIR/fft curve_${k}_interp_SM1 >coeffs_${k}_SM1.res 2> fft_${k}_SM1.res
done

gnuplot curves_SM1.plt
gnuplot decay_An.plt
gnuplot decay_Bn.plt

mv curves_SM1.tex $IMGDIR
#mv curves_SM1.png $IMGDIR
mv decay_An.eps $IMGDIR
mv decay_Bn.eps $IMGDIR

# SM2
printf "\n\n\n"
printf "***** SM2: Interpolating curves and performing DFT *****\n"
for ((k=TORMIN; k <=TORMAX; k++))
do
	# swap columns 1 and 2, and sort curve points according to phi_+
	LC_ALL=C awk -f $BINDIR/swap.awk curve2_${k}_${k}_rng_0.res | LC_ALL=C sort -g -k 1,1 > \
	curve_${k}_SM2

	# to perform DFT, interpolate curve on just 128 points
	$BINDIR/spline_interp curve_${k}_SM2 > curve_${k}_interp_SM2

	# perform DFT
	$BINDIR/fft curve_${k}_interp_SM2 >coeffs_${k}_SM2.res 2> fft_${k}_SM2.res
done

gnuplot curves_SM2.plt

mv curves_SM2.tex $IMGDIR
#mv curves_SM2.png $IMGDIR
