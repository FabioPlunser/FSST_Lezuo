all: bsearchFabioPlunser Rieser_compare_all_functions 


bsearchFabioPlunser: bsearchFabioPlunser.c
	gcc bsearchFabioPlunser.c -o output
Rieser_compare_all_functions: Rieser_compare_all_functions.c
	gcc Rieser_compare_all_functions.c -o rieser

bsearch: bsearchBenchmark.c GNUPLOT/usage.plot 
	gcc bsearchBenchmark.c -o bin 
	./bin
	gnuplot GNUPLOT/usage.plot 

clean:
	rm output rieser


