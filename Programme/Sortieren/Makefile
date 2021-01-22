quicksort: quicksort.c searches.c
	gcc quicksort.c searches.c -o quicksort
	./quicksort

benchmark: quicksort.c searches.c usage.plot 
	gcc quicksort.c searches.c -o quicksort
	./quicksort
	gnuplot usage.plot 

plot: usage.plot usage.csv
	gnuplot usage.plot

clean: 
	rm *.c