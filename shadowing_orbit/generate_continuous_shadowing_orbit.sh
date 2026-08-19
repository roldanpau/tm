gawk 'BEGIN {time = 0} {print time+$1,$2,$3,$4,$5,$6,$7} ENDFILE {time = time + $1}' pseudo[1-9]_*.res pseudo1[0-6]_*.res
#gawk 'BEGIN {time = 0} {} ENDFILE {time = time + $1; print FILENAME; print time}' 
