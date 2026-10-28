set term tikz
set out "curves_SM1.tex"

TORMIN=2
TORMAX=8
set xlabel '$\phi$'
set ylabel '$I$'
plot [0:2*pi] [0:8.5]\
for [i=TORMIN:TORMAX] (i-1) w l lc (i-TORMIN+1) not, \
for [i=TORMIN:TORMAX] sprintf('curve_%i_interp_SM1',i) w lp lc (i-TORMIN+1) not

unset out 
unset term
