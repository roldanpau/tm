set term png size 800,600
set out "resonance23.png"
#set term post eps
#set out "resonance23.eps"

set xlabel '$\phi$'
set ylabel '$I$'

set xrange [0:pi]
set yrange [2:3]

# Resonance 2:3 is located at I=2.452
I=2.452
# Resonance 5:7 is located at I=5.1505
#I=5.1505

set arrow from 0,I to pi,I nohead 
plot "resonance23.res" u 2:1 pt 7 ps 0.01 not

unset out
unset term

