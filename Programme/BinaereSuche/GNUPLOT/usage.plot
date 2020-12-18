# Output W3C Scalable Vector Graphics
set terminal x11
# Read comma-delimited data from file
set datafile separator comma

# Set graph title
set title 'BigFuckingBuffer Bsearch Lezuo'

# Set label of x-axis
set xlabel 'index'

# Set label of y-axis
set ylabel 'time[us]'

# Use a line graph
set style data line

# Plot data from a file, with extra notes below:
#
# for [i=2:5]         Loop for values of i between 2 and 5 (inclusive)
# using i:xtic(1)     Plot column i using tick labels from column 1
# title columnheader  Use the column headers (first row) as titles
# linewidth 4         Use a wider line width
#
plot for [i=start:end] 'usage.csv' using i:xtic(1) title columnheader linewidth 4
pause -1 "Hit any key to continue\n"