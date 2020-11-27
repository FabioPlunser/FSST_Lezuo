/* #Titel: Binäre Suche
   #Autor: Mitterhuber Lorenz
   #Datum: 24.11.2020
   #Git-Repo: https://github.com/lorenzm24/FSST_Mitterhuber_LZ.git

   #Funktion des Programms:
   

   #Anmerkungen
   

   #Testen des Programms unter linux:
   
*/
//#################################################################################################

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>


#define BUFFER_SIZE 5e06
#define FILE "wortbuffer"

/*void **createSearcharray(void *buffer, int iRead)
{
    void **search_index = malloc(iRead);
    int j=0;
    search_index[j]=buffer;
    for (int i=0; i<iRead; i++)
    {
        //printf("hure2\n");
        if ((*((char*)buffer+i)) == 0)
        {
            //printf("%s\n", (char*)search_index[j]);
            search_index[++j] = buffer+(++i); //Beginn nächstes Wort daher +(++i)
        }
    }
    printf("words: %i\n", j);
    return search_index;
}*/

/*void* compareBuffer(char* input, char **search_index, int index_m, int prev_diff)
{
    //printf("found %i words\n", iAnzahl);
    //printf("input: %s\n", input);
    //printf("%s\n", search_index[100000]);
    /*
    printf("mittleres word: %s\n", search_index[iAnzahl/i]);
    int comparedString = strcmp(input, search_index[iAnzahl/i]);
    if (comparedString==0){
        printf("gleich\n");
        return *search_index;
    }
    else if (comparedString>0){
        printf("obere Hälfte\n");
        i=i*2;
        search_index[iAnzahl/2]+=*search_index[iAnzahl/i];
        printf("%s", search_index[iAnzahl/2]);
        //while(((char)search_index-1) != 0){
          //  search_index++;
        //}
    } else{
        printf("untere Hälfte\n");
        search_index[iAnzahl/2]+=*search_index[(iAnzahl/2)/2]; 
        while(((char)search_index-1) != 0){
            search_index++;
        }
    }*/
    /*int comparedString = strcmp(input, *search_index);
    printf("%s\n", *search_index);
    //printf("%i\n", comparedString);
    if (comparedString==0){
        printf("gleich\n");
        return *search_index;
    }
    else if (comparedString>0){
        printf("obere Hälfte\n");
        
        search_index+=iAnzahl/i;
        
        //printf("%s", search_index[iAnzahl/2]);
        //while(((char)search_index-1) != 0){
          //  search_index++;
        //}
    }
    else {
        printf("untere Hälfte\n");
        
        search_index-=iAnzahl/i;
        
    }
    if (i>iAnzahl)
    {
        return NULL; //not in Buffer
    }
    
    int iAnzahl/2 = number_of_words/2;

    int diff = strcmp(input, *((char **)search_index + index_m));

    if (diff == 0){
        return *((char **)search_index + index_m);
    }else if (number_of_words == 0){
        // Check one more List-Entry just to be sure
        if (strcmp(input, *((char **)search_index + index_m + (diff < 0 ? -1 : 1))) == 0) {
            return *((char **)search_index + index_m);
        }
        return NULL;
    }

    if(diff<0)
    {
        index_m -= iAnzahl/2;
        if(prev_diff < 0) index_m --;
    }
    else if(diff>0)
    {
        index_m += iAnzahl/2;
        if (prev_diff > 0) index_m ++;
    }

    if (index_m < 0){
        index_m = 0;
    }

    return compareBuffer(input, search_index, iAnzahl/2,index_m, diff);
}*/

void* compareBuffer(char* input, char** search_index, int iAnzahl){


    int comparedString = strcmp(input, *search_index);
    if (comparedString == 0){
        return *search_index;
    }else if (iAnzahl == 0){
        /*int iZwischen;
        // Check one more List-Entry just to be sure
        if (comparedString<0){
            iZwischen = -1;
        }else{
            iZwischen = 1;
        }
        if (strcmp(input, *(search_index + iZwischen)) == 0) {
            return *search_index;
        }*/
        return NULL;
    }

    if(comparedString<0)
    {
        search_index -= iAnzahl/2+1;
        //if(diff_prev < 0) search_index --; //Um Rundungsfehler zu verbessern, wenn zweimalmin selbe richtung
    }
    else if(comparedString>0)
    {
        search_index += iAnzahl/2+1;
        //if (diff_prev > 0) search_index ++;
    }
    return compareBuffer(input, search_index, iAnzahl/2);
}

void *readBuffer(char *input)
{
    int iOpen, iRead;
    void *buffer = malloc(BUFFER_SIZE); 
    
    //Oeffnen des zu lesenden Files; bei Rückgabe von -1 --> abbrechen, da ewas schief gegangen ist
    //O_RDONLY sorgt dafür, dass das File nur gelesen wird!
    iOpen = open(FILE, O_RDONLY);
    if (iOpen == -1) {
        perror ("open");
        //return EXIT_FAILURE;
    }

    //Es wird solange ausgelesen, bis die gelesenen Bytes Null sind (read() gibt Anzahl der
    //gelsenen Bytes zurück; write() gibt Anzahl der geschriebenen Bytes zurück)
    //Wenn die Anzahl der geschriiebenen Bytes ungleich der gelesenen ist --> Abbruch
    iRead = read(iOpen, buffer, BUFFER_SIZE);
    if(iRead==-1){
        perror("read");
        //return EXIT_FAILURE;
    }
    
    //Nach Kopiervorgang --> File schließen!
    close(iOpen);
    printf("read file successfully\n");
    printf("bytes read: %i\n", iRead);

    //****************************************************************************************
    
    char **search_index = malloc(iRead);
    int iAnzahl=0;
    search_index[iAnzahl]=buffer;
    for (int i=0; i<iRead; i++)
    {
        //printf("hure2\n");
        if ((*((char*)buffer+i)) == 0)
        {
            //printf("%s\n", (char*)search_index[j]);
            search_index[++iAnzahl] = buffer+(++i); //Beginn nächstes Wort daher +(++i)
        }
    }
    //printf("words: %i\n", iAnzahl);
    int i=0;
    
    return compareBuffer(input, search_index, iAnzahl);
}

//------------------------------------------------------------------------------------------------------
int main(void)
{   
    for(;;)
    {
    char input[100];

    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1] = 0;

    if (!strlen(input)) break;

    struct timeval tv_begin, tv_end, tv_diff;

    gettimeofday(&tv_begin, NULL);
    void *res = readBuffer(input);// wie auch immer
    gettimeofday(&tv_end, NULL);

    timersub(&tv_end, &tv_begin, &tv_diff);

    if (res != NULL) {
            printf("found");
    } else {
            printf("not found");
    }
    printf(" in (%ld seconds %ld microseconds)\n", tv_diff.tv_sec, tv_diff.tv_usec);
    
     
    }

    //void **lele = readBuffer();
    //int iAnzahl = readBuffer();
    //printf("%i", (int*)iAnzahl);
    //printf("%s\n", (char*)lele[100000]);


}