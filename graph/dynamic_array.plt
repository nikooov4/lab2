set terminal png size 800,600
set output 'graph/dynamic_array.png'
set title 'Performance of DynamicArray with Person'
set xlabel 'Number of Elements'
set ylabel 'Time (ms)'
set xrange [0:*]
set yrange [0:*]
plot 'graph/dynamic_array.dat' using 1:2 with linespoints title 'DynamicArray'
