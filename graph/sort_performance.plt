set terminal png size 800,600
set output 'graph/sort_performance.png'
set title 'Performance of Sorting Algorithms'
set xlabel 'Number of Elements'
set ylabel 'Time (ms)'
set xrange [0:*]
set yrange [0:*]
plot 'graph/sort_performance.dat' using 1:2 with linespoints title 'MergeSort', \
     '' using 1:3 with linespoints title 'QuickSort', \
     '' using 1:4 with linespoints title 'HeapSort'
