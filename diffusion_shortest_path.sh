PAPERDIR=.
IMGDIR=$PAPERDIR/images

make phase_port_SM diffusion_shortest_path

# The initial point (I=1, \phi=5.026548) and final point (I=7, \phi=0) below 
# where found using program diffusion_shortest_path_Iini_Ifin
./diffusion_shortest_path 1 5.026548 7 0 > diffusion_shortest_path.res
gnuplot diffusion_shortest_path.plt
mv diffusion_shortest_path.png $IMGDIR
