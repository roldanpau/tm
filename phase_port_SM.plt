load "plotdefs.plt"

set term png size 800,600
set out "phase_port_SM_smalldelta.png"
#set term cairolatex png size 4.8,3.6
#set out "phase_port_SM.tex"

#set xlabel '$\phi$'
#set ylabel '$I$'
set xlabel "phi"
set ylabel "J"

set xrange [0:2*pi]
set yrange [0:7]

plot "phase_port_SM.res" u 2:1 ls PPSM1ST not

unset out
unset term

