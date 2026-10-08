load "plotdefs.plt"

set term png size 800,600
set out "diffusion_shortest_path.png"

set xlabel 'phi'
set ylabel 'I'

#"diffusion_shortest_path.res" u 2:1 w l ls PO not, \

plot [0:2*pi] \
"phase_port_SM.res" u 2:1 ls PPSM1 not, \
"phase_port_SM2.res" u 2:1 ls PPSM2 not, \
"< awk '{if($5 == \"SM1\") print $1,$2,\"\\n\" $3,$4; else print \"\\n\"}' diffusion_shortest_path.res" u 2:1 w lp \
ls SM1 t "TM1 iterate", \
"< awk '{if($5 == \"SM2\") print $1,$2,\"\\n\" $3,$4; else print \"\\n\"}' diffusion_shortest_path.res" u 2:1 w lp \
ls SM2 t "TM2 iterate", \
"< awk '{if($5 == \"IM\") print $1,$2,\"\\n\" $3,$4; else print \"\\n\"}' diffusion_shortest_path.res" u 2:1 w lp \
ls IM t "IM iterate", \
"< awk '{if($5 == \"SM1\") print}' diffusion_shortest_path.res" u 2:1 w p \
ls SM1 not, \
"< awk '{if($5 == \"SM2\") print}' diffusion_shortest_path.res" u 2:1 w p \
ls SM2 not, \
"< awk '{if($5 == \"IM\") print}' diffusion_shortest_path.res" u 2:1 w p \
ls IM not

unset out
unset term
