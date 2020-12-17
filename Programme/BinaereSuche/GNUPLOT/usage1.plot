#set terminal postfile       (These commented lines would be used to )
#set output  "d1_plot.ps"    (generate a postscript file.            )
set title "Energy vs. Time for Sample Data"
set xlabel "Time"
set ylabel "Energy"
plot sin(x) with lines
pause -1 "Hit any key to continue"