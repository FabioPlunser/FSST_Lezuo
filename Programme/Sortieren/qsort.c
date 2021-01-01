/*
 * Projekt:	Quick Sort Algorithmus
 * Datei:	qsort.c
 * Autor:	Gleinser Andreas
 * Datum:	16.12.2020
 *
 *
 *
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <andgleinser@tsn.at> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 *
 * Gleinser Andreas
 *
 *
 *
 * Beschreibung:
 * Implementieren Sie Quicksort (https://de.wikipedia.org/wiki/Quicksort) für
 * arrays mit integern. Testen und Messen sie die Zeiten mit 10, 100, 1000,
 * 10000, 100000 Elementen.
 *
 * Bonus Aufgabe: Messreihe und Vergleich mit Bubblesort, messen gegen qsort(3)
 * aus der C Bibliothek.
 */

//----- includes ---------------------------------------------------------------
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//----- subroutines ------------------------------------------------------------

/*
 * Funktion: swap
 * --------------
 * Tauscht die Werte zweier Variablen
 *
 * Parameter:
 * a: erste Variable
 * b: zweite Variable
 *
 * Return:
 * nichts
 */
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
 * Funktion: partition
 * -------------------
 * Implementiert die Partition für den Quick Sort Algorithmus
 *
 * Parameter:
 * *a: unsortiertes Array
 * us: untere Schranke (Anfang vom Array)
 * os: obere Schranke (End vom Array)
 *
 * Return:
 * Index i
 */
int partition(int *a, int us, int os)
{
	int i, piv;

	/* set pivot */
	piv = a[os];
	i = us - 1;

	for(int j = us; j < os; j++)
	{
		if(a[j] < piv)
		{
			i++;
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i+1], &a[os]);

	return (i+1);
}

/*
 * Funktion: qs
 * ------------
 * Implementiert Quick Sort
 *
 * Parameter:
 * a: unsortiertes Array
 * us: untere Schranke (Anfang vom Array)
 * os: obere Schranke (End vom Array)
 *
 * Return:
 * nichts
 */
void qs(int *a, int us, int os)
{
	int pi;

	if(us < os)
	{
		pi = partition(a, us, os);

		qs(a, us, pi-1);
		qs(a, pi+1, os);
	}
}

/*
 * Funktion: bsort
 * ---------------
 * Implementiert Bubble Sort
 *
 * Parameter:
 * a: unsortiertes Array
 * n: Grösse des Arrays
 *
 * Return:
 * nichts
 */
void bsort(int *a, int n)
{
	int swapped;

	for(int i = 0; i < n-1; i++)
	{
		swapped = 0;
		for(int j = 0; j < n-i-1; j++)
		{
			if(a[j] > a[j+1])
			{
				swap(&a[j], &a[j+1]);
				swapped = 1;
			}
		}

		if(swapped == 0)
			break;
	}
}

/*
 * Funktion: create_array
 * -----------------------
 * Erstellt ein Array mit (pseudo-)zufälligen Zahlen
 *
 * Parameter:
 * size: 	Größe des Arrays
 * max_int:	Größte Zufallszahlen
 *
 * Return:
 * unsortiertes Array b
 */
int *create_array(int size, int max_int)
{
	int *b = (int*)malloc(size * sizeof(int));

	for(int i = 0; i < size; i++)
		b[i] = rand() % max_int;

	return b;
}

/*
 * Funktion: cmp
 * -------------
 * Vergleichen von 2 Variablen
 *
 * Parameter:
 * a: erste Variable
 * b: zweite Variable
 *
 * Return:
 * Differenz beider Variablen
 */
int cmp(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

/*
 * Funktion: benchmark
 * -------------------
 * Misst alle Bonusaufgaben und gibt diese Messwerte mit GNUPlot aus
 *
 * Parameter:
 * keine
 *
 * Return:
 * nichts
 */
void benchmark()
{
	int fd, size;
	int max_int = 100;
	int qs_measure[5], qsort_measure[5], bsort_measure[5];
	char dat_col[100];
	struct timeval tv_begin, tv_end, tv_diff;

	if((fd = open("benchmark.dat", O_WRONLY | O_CREAT, 0644)) < 0)
	{
		perror("unable to open or create file!\n");
		return;
	}
	
	// create random ints based in current time
	srand(time(NULL));

	/* QuickSort Benchmarking */
	size = 0;
	printf("benchmarking qs:\n");
	for(int i = 1; size != 100000; i++)
	{
		size = pow(10, i);
		int *a = create_array(size, max_int);
		printf("starting benchmark nr%d...", i);

		gettimeofday(&tv_begin, NULL);
		qs(a, 0, size);
		gettimeofday(&tv_end, NULL);

		timersub(&tv_end, &tv_begin, &tv_diff);

		qs_measure[i-1] = tv_diff.tv_usec;
		printf("done! (%ld microseconds)\n", tv_diff.tv_usec);
	}

	/* qsort Benchmarking */
	size = 0;
	printf("benchmarking qsort:\n");
	for(int i = 1; size != 100000; i++)
	{
		size = pow(10, i);
		int *a = create_array(size, max_int);
		printf("starting benchmark nr%d...", i);

		gettimeofday(&tv_begin, NULL);
		qsort(a, size, sizeof(int), cmp);
		gettimeofday(&tv_end, NULL);

		timersub(&tv_end, &tv_begin, &tv_diff);

		qsort_measure[i-1] = tv_diff.tv_usec;
		printf("done! (%ld microseconds)\n", tv_diff.tv_usec);
	}

	/* BubbleSort Benchmarking */
	size = 0;
	printf("benchmarking bsort:\n");
	for(int i = 1; size != 100000; i++)
	{
		size = pow(10, i);
		int *a = create_array(size, max_int);
		printf("starting benchmark nr%d...", i);

		gettimeofday(&tv_begin, NULL);
		bsort(a, size);
		gettimeofday(&tv_end, NULL);

		timersub(&tv_end, &tv_begin, &tv_diff);

		bsort_measure[i-1] = tv_diff.tv_usec;
		printf("done! (%ld microseconds)\n", tv_diff.tv_usec);
	}

	/* Write to Spreadsheet */
	for(int i = 0; i < 5; i++)
	{
		sprintf(dat_col, "%d %d\n", i, qs_measure[i]);
		write(fd, &dat_col, strlen(dat_col));
	}
	for(int i = 0; i < 5; i++)
	{
		sprintf(dat_col, "%d %d\n", i+5, qsort_measure[i]);
		write(fd, &dat_col, strlen(dat_col));
	}
	for(int i = 0; i < 5; i++)
	{
		sprintf(dat_col, "%d %d\n", i+10, bsort_measure[i]);
		write(fd, &dat_col, strlen(dat_col));
	}
	close(fd);
	system("gnuplot -p bench.gnuplot");
}

/*
 * Funktion: demo_qsort
 * --------------------
 * Zeigt die Funktionalität von Quick Sort
 *
 * Parameter:
 * size: die Grösse des Arrays
 *
 * Return:
 * nichts
 */
void demo_qsort(int size, int max_int)
{
	struct timeval tv_begin, tv_end, tv_diff;

	// create random ints based in current time
	srand(time(NULL));

	int *a = create_array(size, max_int);

	gettimeofday(&tv_begin, NULL);
	qs(a, 0, size);
	gettimeofday(&tv_end, NULL);

	int old = -1;
	for(int i = 0; i < size; i++)
	{
		if(old != -1)
			assert(old <= a[i]);
		printf("%d ", a[i]);
		old = a[i];
	}
	printf("\n");

	timersub(&tv_end, &tv_begin, &tv_diff);
	printf("sorted in: %ld microseconds\n", tv_diff.tv_usec);
}

/*
 * Funktion: print_usage
 * ---------------------
 * Gibt Auskunft, wie das Programm zu verwenden ist
 *
 * Parameter:
 * keine
 *
 * Return:
 * nichts
 */
void print_usage()
{
	char text[6][100] = {
		"Usage: ./output [options] [size] [intMax]",
		"Options:",
		"\t-h, --help\tprints this help info",
		"\t-b, --benchmark\tbenchmarks algorithms and plots them",
		"\t-d, --demo\truns quick demo test",
		"Note: [size] and [intMax] only apply for the -d flag"
	};

	for(int i = 0; i < 6; i++)
		printf("%s\n", text[i]);
}

//----- main -------------------------------------------------------------------
int main(int argc, char **argv)
{
	if(argv[1] != NULL)
	{
		if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
			print_usage();
		else if(strcmp(argv[1], "--demo") == 0 || strcmp(argv[1], "-d") == 0)
		{
			if(argv[2] != NULL && argv[3] != NULL)
			{
				char *ptr;
				int size = strtol(argv[2], &ptr, 10);
				int max_int = strtol(argv[3], &ptr, 10);
				demo_qsort(size, max_int);
			}
			else
				print_usage();
		}
		else if(strcmp(argv[1], "--benchmark") == 0 || strcmp(argv[1], "-b") == 0)
			benchmark();
	}
	else
		print_usage();

	return 0;
}

/* END OF FILE [] */
