load "plotdefs.plt"

#set term post eps color
set term pdf
set out "shadowing_orbit.pdf" 

set xlabel '$X$'
set ylabel '$Y$'
set zlabel '$Z$'

#
# reset linetypes to base dash patterns
#
set for [i=1:5] linetype i dt i

set style line 1 lt 1 lw 1 linecolor rgb "green"
set style line 2 lt 1 lw 1 linecolor rgb "blue"
set style line 3 lt 1 lw 1 linecolor rgb "red"

set object 1 circle at -1,0 size 0.0001 front fc rgb "blue" fs solid

set view 31,173

splot [:] [:] [:] \
"pseudo1_1.res" u 2:4:6 w l ls 3 not, \
"pseudo1_2.res" u 2:4:6 w l ls 3 not, \
"pseudo1_3.res" u 2:4:6 w l ls 3 not, \
"pseudo1_4.res" u 2:4:6 w l ls 3 not
#$Mydata1 w p ls SM1 not

#pause -1

SEGMENTS_SM1="14 11 9 6 4"
replot for [i in SEGMENTS_SM1] \
"pseudo".i."_1.res" u 2:4:6 w l ls 2 not
replot for [i in SEGMENTS_SM1] \
"pseudo".i."_2.res" u 2:4:6 w l ls 2 not
replot for [i in SEGMENTS_SM1] \
"pseudo".i."_3.res" u 2:4:6 w l ls 2 not
replot for [i in SEGMENTS_SM1] \
"pseudo".i."_4.res" u 2:4:6 w l ls 2 not

SEGMENTS_SM2="16 15 13 12 10 8 7 5 3 2"
replot for [i in SEGMENTS_SM2] \
"pseudo".i."_1.res" u 2:4:6 w l ls 3 not
replot for [i in SEGMENTS_SM2] \
"pseudo".i."_2.res" u 2:4:6 w l ls 3 not
replot for [i in SEGMENTS_SM2] \
"pseudo".i."_3.res" u 2:4:6 w l ls 3 not
replot for [i in SEGMENTS_SM2] \
"pseudo".i."_4.res" u 2:4:6 w l ls 3 not

unset out
unset term
