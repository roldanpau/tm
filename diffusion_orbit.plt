load "plotdefs.plt"

#set term post eps color
#set out "images/diffusion_orbit_XYZ.eps" 

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

set view 60,185

#$Mydata1 << EOD
#-.9901571858419089 0.002431132106917601 -0.00001787784654263232
#-.9901603705827249 0.002430819433404007 0.0002400164432447684
#EOD

splot [:] [:] [-0.0005:0.0005] \
"pseudo1_1.res" u 1:3:5 w l ls 2 not, \
"pseudo1_2.res" u 1:3:5 w l ls 2 not, \
"pseudo1_3.res" u 1:3:5 w l ls 2 not, \
"pseudo1_4.res" u 1:3:5 w l ls 2 not
#$Mydata1 w p ls SM1 not

pause -1

replot \
"pseudo2.res" u 1:3:5 w l ls 1 not, \
"pseudo3.res" u 1:3:5 w l ls 1 not, \
"pseudo4.res" u 1:3:5 w l ls 1 not, \
"pseudo5.res" u 1:3:5 w l ls 1 not, \
"pseudo6.res" u 1:3:5 w l ls 1 not
#$Mydata2 w p ls IM not

pause -1

replot \
"pseudo7_1.res" u 1:3:5 w l ls 3 not, \
"pseudo7_2.res" u 1:3:5 w l ls 3 not, \
"pseudo7_3.res" u 1:3:5 w l ls 3 not, \
"pseudo7_4.res" u 1:3:5 w l ls 3 not
#$Mydata1 w p ls SM1 not

if(0) { ############ BEGIN COMMENTED OUT BLOCK ##############
pause -1

replot \
"pseudo49_1.res" u 1:3:5 w l ls 3 not, \
"pseudo49_2.res" u 1:3:5 w l ls 3 not, \
"pseudo49_3.res" u 1:3:5 w l ls 3 not, \
"pseudo49_4.res" u 1:3:5 w l ls 3 not
#$Mydata1 w p ls SM1 not
} ################# END COMMENTED OUT BLOCK ##############

unset out
unset term
