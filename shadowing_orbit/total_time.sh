gawk 'BEGIN {time = 0; print time} {} ENDFILE {time = time + $1; print time}' pseudo*.res
