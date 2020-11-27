// Author: FabioPlunser //
// Date: 24.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specific Git-location: https://github.com/FabioPlunser/FSST_Lezuo/blob/main/Programme/BinaereSuche/BinaereSuche.c //
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

//recursive V2 with list
char** compare(char* input, char** search_index, int number_of_words, int index_m, int diff)
{   
    int jump_distance = number_of_words/2;

	int temp_diff = diff;
	diff = strcmp(input, *(search_index + index_m));
    printf("Index: %i, Diff: %i, String: %s\n", index_m, diff, *(search_index + index_m));
	

    if(diff<0)
    {
        index_m -= number_of_words;
        if( temp_diff < 0)
        {
            index_m --;
        }
    }
    else if(diff>0)
    {
        index_m += number_of_words;
        if (temp_diff > 0)
        {
           index_m ++; 
        }
    }

	if (index_m < 0){
		index_m = 0;
	}else if (index_m > number_of_words){
		index_m = number_of_words;
	}

	if (diff == 0){
        diff = 1;
        index_m = 0;
		return search_index + index_m;	
	}else if (number_of_words == 0){
		return NULL;
	}

    return  compare(input, search_index, number_of_words, index_m, diff);
}


char** create_search_index(char* input)
{
    int wortbuffer, read_length, i = 0;
    void* BFBuffer = malloc(BFBuffer_Size); 

    wortbuffer = open("wortbuffer", O_RDONLY);
    if (wortbuffer == -1)
    {
        perror("open");
    }
    
    read_length = read(wortbuffer, BFBuffer, BFBuffer_Size); //writing buffer with 20 Bytes at a time didn't work at all, because the seperation of the word got erased
    
    printf("Make List\n");
    char** search_index = malloc(read_length);
    search_index[i] = BFBuffer;
    
    for(int x=0; x<read_length; x++)
    {
        if (*((char*)BFBuffer+x) == 0)
        {
            search_index[++i] = BFBuffer+(++x);
            // printf("%s, %i\n", (char*)search_index[i], i)
            
        }        
    }
    return  compare(input, search_index, i,  0, 1);
}


int main()
{
    for(;;)
    {
        char input[100];

        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;

        if(!strlen(input)) break;

        struct timeval tv_begin, tv_end, tv_diff;
    
        gettimeofday(&tv_begin, NULL); //get time before finding word
        
        void* res =  create_search_index(input);
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