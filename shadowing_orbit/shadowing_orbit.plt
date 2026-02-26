load "plotdefs.plt"

set term post eps color
set out "shadowing_orbit_XYZ.eps" 

set xlabel '$X$'
set ylabel '$Y$'
set zlabel '$Z$'

#
# reset linetypes to base dash patterns
#
set for [i=1:5] linetype i dt i

set style line 1 lt 1 lw 3 linecolor rgb "green"
set style line 2 lt 1 lw 3 linecolor rgb "blue"
set style line 3 lt 1 lw 3 linecolor rgb "red"

set object 1 circle at -1,0 size 0.0001 front fc rgb "blue" fs solid

set view 66,181

#$Mydata1 << EOD
#-.9901571858419089 0.002431132106917601 -0.00001787784654263232
#-.9901603705827249 0.002430819433404007 0.0002400164432447684
#EOD

#splot [:] [:] [-0.0008:0.0008] \

splot \
"shadow_1.res" u 2:4:6 w l ls 2 not, \
"shadow_2.res" u 2:4:6 w l ls 2 not, \
"shadow_3.res" u 2:4:6 w l ls 2 not, \
"shadow_4.res" u 2:4:6 w l ls 2 not

if(0) { ################ BEGIN COMMENT BLOCK ##############
pause -1

splot \
"pseudo_1.res" u 2:4:6 w l ls 3 not, \
"pseudo_2.res" u 2:4:6 w l ls 3 not, \
"pseudo_3.res" u 2:4:6 w l ls 3 not, \
"pseudo_4.res" u 2:4:6 w l ls 3 not
#$Mydata1 w p ls SM1 not

replot for [i=2:6] "pseudo".i.".res" u 2:4:6 w l ls 1 not
#$Mydata2 w p ls IM not

pause -1

replot \
"pseudo7_1.res" u 2:4:6 w l ls 3 not, \
"pseudo7_2.res" u 2:4:6 w l ls 3 not, \
"pseudo7_3.res" u 2:4:6 w l ls 3 not, \
"pseudo7_4.res" u 2:4:6 w l ls 3 not

pause -1

replot \
"pseudo8_1.res" u 2:4:6 w l ls 3 not, \
"pseudo8_2.res" u 2:4:6 w l ls 3 not, \
"pseudo8_3.res" u 2:4:6 w l ls 3 not, \
"pseudo8_4.res" u 2:4:6 w l ls 3 not
#$Mydata1 w p ls SM1 not

pause -1

replot for [i=9:15] "pseudo".i.".res" u 2:4:6 w l ls 1 not
#$Mydata2 w p ls IM not

pause -1

replot \
"pseudo16_1.res" u 2:4:6 w l ls 2 not, \
"pseudo16_2.res" u 2:4:6 w l ls 2 not, \
"pseudo16_3.res" u 2:4:6 w l ls 2 not, \
"pseudo16_4.res" u 2:4:6 w l ls 2 not

pause -1

replot \
"pseudo47_1.res" u 2:4:6 w l ls 3 not, \
"pseudo47_2.res" u 2:4:6 w l ls 3 not, \
"pseudo47_3.res" u 2:4:6 w l ls 3 not, \
"pseudo47_4.res" u 2:4:6 w l ls 3 not
} ################ END COMMENT BLOCK ##############

unset out
unset term
