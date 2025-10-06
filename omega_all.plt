set term tikz
set out "omega_all.tex"

set xlabel '$I$'
set ylabel '$\omega(I)$'

plot "omega_all.res" w lp not

unset out

set out "omega_all_SM2.tex"

set xlabel '$I$'
set ylabel '$\omega(I)$'

plot "omega_all_SM2.res" w lp not

unset out
unset term
