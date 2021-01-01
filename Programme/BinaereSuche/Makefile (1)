all: bsearchFabioPlunser Rieser_compare_all_functions 

bsearch: bsearchBenchmark.c GNUPLOT/usage.plot 
	gcc bsearchBenchmark.c -o bin
	./bin
	gnuplot GNUPLOT/usage.plot 

plot: GNUPLOT/usage.plot usage.csv
	gnuplot GNUPLOT/usage.plot

clean:
	rm output rieser


