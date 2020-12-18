
BIN_NAME=bin


all: bsearchFabioPlunser Rieser_compare_all_functions 

bsearch: bsearchBenchmark.c GNUPLOT/usage.plot 
	gcc $* -o $(BIN_NAME) 
	./$(BIN_NAME)
	gnuplot GNUPLOT/usage.plot 

plot: GNUPLOT/usage.plot usage.csv
ifeq ("$(end)","")
	$(eval END_NUM=$(end))
else
	$(eval END_NUM=7)
endif
	gnuplot -e "start=2;end=$(END_NUM)" GNUPLOT/usage.plot

%:%.c
	gcc $* -o $(BIN_NAME)
	./$(BIN_NAME)

clean:
	rm output rieser


