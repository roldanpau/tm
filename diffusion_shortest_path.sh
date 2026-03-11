PAPERDIR=.
IMGDIR=$PAPERDIR/images

make phase_port_SM diffusion_shortest_path

# The initial point (I=1, \phi) and final point (I=7, \phi) below 
# where found using program diffusion_shortest_path_Iini_Ifin
./diffusion_shortest_path 1 4.398230 7 1.884956 > diffusion_shortest_path.res
gnuplot diffusion_shortest_path.plt
mv diffusion_shortest_path.png $IMGDIR
