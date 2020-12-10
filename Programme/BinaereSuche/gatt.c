/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Author: Gatt David, Klasse: 5bHEL, Aufgabe bearbeitet November 2020, Abgabe: 29.11.2020, Betreuer: Lezuo
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Task: Implementiere rekursive binäre Suche in C, benutze die Funktion strcmp(3)
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Funktionsweise: siehe Kommentare
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

#define Buf_Size 50000000


char** binary_search(char* Wort, char** search_index, int mitte, int diff, int iUg, int iOg)
{
     while(1)
    {
        

        mitte = (iUg+iOg)/2;
        diff=strcmp(Wort, *(search_index+mitte));

        if(iUg == iOg)
        {
            
            return(NULL);  
        }
        if(diff < 0)
        {
            iOg = (iUg+iOg)/2;
            
        }
        else if(diff > 0)
        {
            iUg = (iUg+iOg)/2;
        
        }
        else
        {
            printf("Wort gefunden: %s\n", *(search_index+((iUg+iOg)/2)));
            return(search_index+((iUg+iOg)/2));
        }
    }
}
char** index_bin(char* Wort)
{
    
    char* Buf=malloc(Buf_Size);
    int iOpen, iRead,i = 0;

    iOpen = open("wortbuffer", O_RDONLY);
    iRead = read(iOpen, Buf, Buf_Size);
    
    char** search_index=malloc(iRead);
    search_index[i] = Buf;

    for(int x=0; x<iRead; x++)
    {
        if (*(Buf+x) == 0)
        {
            search_index[++i] = Buf+(++x);
            printf("%s, %i\n", (char*)search_index[i], i);
        }
    }
   return binary_search(Wort, search_index, 0, 0, 0, i);
}






int main(int argc, char** argv)
{

    printf("WARUM\n");
    for (;;) {
                printf("GEHST\n");
                char input[100];
                printf("DU\n");
                fgets(input, sizeof(input), stdin);
                printf("MEINE\n");
                input[strlen(input)-1] = 0;
                printf("VERFIGGTE\n");
                if (!strlen(input)) break;
                printf("GUTE\n");

                struct timeval tv_begin, tv_end, tv_diff;
                printf("Warum hasst mi C so sehr\n");
                gettimeofday(&tv_begin, NULL);
                printf("wIESO GeHT DEs NIt\n");
                void *res = index_bin(input);
                printf("warum gehst du nit\n");
                gettimeofday(&tv_end, NULL);

                timersub(&tv_end, &tv_begin, &tv_diff);

                if (res != NULL) {
                        printf("found\n");
                } else {
                        printf("not found\n");
                }
                printf(" in (%ld seconds %ld microseconds)\n", tv_diff.tv_sec, tv_diff.tv_usec); 
        }


    return 0;
}