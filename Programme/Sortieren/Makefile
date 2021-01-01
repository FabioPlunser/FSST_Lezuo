quicksort:
	gcc quicksort.c -o quicksort

benchmark: quicksort.c usage.plot 
	gcc quicksort.c -o quicksort
	./quicksort
	gnuplot usage.plot 

plot: usage.plot usage.csv
	gnuplot usage.plot

clean: 
	rm *.c