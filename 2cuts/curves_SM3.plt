#set term tikz
#set out "curves_SM3.tex"
set term png
set out "curves_SM3.png"

TORMIN=2
TORMAX=14
set xlabel '$\phi$'
set ylabel '$I$'
plot [0:2*pi] [:]\
for [i=TORMIN:TORMAX] (i-1) w l lc (i-TORMIN+1) not, \
for [i=TORMIN:TORMAX] sprintf('curve_%i_interp_SM3',i) w lp lc (i-TORMIN+1) not

unset out 
unset term
