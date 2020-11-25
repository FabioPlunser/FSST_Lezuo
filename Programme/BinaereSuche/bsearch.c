// Author: FabioPlunser //
// Date: 24.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specifig Git-location: https://github.com/FabioPlunser/FSST_Lezuo/blob/main/Programme/BinaereSuche/BinaereSuche.c //
// Compiled with make, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// BinaereSuche //

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h> 
#include <fcntl.h>

#define BFBuffer_Size 5000000

int index_m = 0;
char** create_buffer()
{
    int wortbuffer, read_length, i;
    void* BFBuffer = malloc(BFBuffer_Size); 

    wortbuffer = open("wortbuffer", O_RDONLY);
    if (wortbuffer == -1)
    {
        perror("open");
    }
    
    read_length = read(wortbuffer, BFBuffer, BFBuffer_Size); //writing buffer with 20 Bytes at a time didn't work at all, because the seperation of the word got erased
    
    char** search_index = malloc(read_length);
    search_index[0] = BFBuffer;
    
    for(int x=0; x<read_length; x++)
    {
        if (*((char*)BFBuffer+x) == 0)
        {
            search_index[++i] = BFBuffer+(++x);
            index_m++;
        }
    }
    printf("%i\n", index_m);
    return search_index; 
    
}

int comparfunction(const void * a, const void * b){
    printf("Comparefunction: 1:%s, 2:%s\n", (char*)a, (char*)b);
    return strcmp((char*)a,*((char**)b));
    
}

int main()
{
    char** search_index = create_buffer(); //get wordfile into a very big buffer
    for(;;)
    {
        char input[100];

        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;

        if(!strlen(input)) break;

        struct timeval tv_begin, tv_end, tv_diff;
    
        gettimeofday(&tv_begin, NULL); //get time before finding word
        // void* res = compare(input, BFBuffer);
        void* res = bsearch(input, search_index, index_m*sizeof(char*), sizeof(char*), comparfunction);
        
        gettimeofday(&tv_begin, NULL); //get time after finding word

        timersub(&tv_end, &tv_begin, &tv_diff); //subtract times to get the time how long it took

        if(res != NULL)
        {
            printf("found");
        }
        else
        {
            printf("not found");
        }
        printf(" in (%li seconds %li  microseconds)\n", tv_diff.tv_sec, tv_diff.tv_usec);   //print time
    }
}