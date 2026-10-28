TORMIN=2
TORMAX=14

set out "decay_An.eps"
set term post eps color

set title "Decay of Fourier coeffs A_n (log-log plot)"
set xlabel "n"
set ylabel "|A_n|"

set logscale xy

plot [1:40] \
for [i=TORMIN:TORMAX] sprintf('fft_%i_SM1.res', i) u 1:2 w lp not
set term pop
set out 
