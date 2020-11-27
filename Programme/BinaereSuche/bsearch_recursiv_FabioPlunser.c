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

//lower_limit--------------middle-------------------upper_limit//
//0------------------------upper_limit/2------------upper_limit//
//word for example higher than middle word //
//upper_limit/2---------middle----------upper_limit// 

//recursive V2 with list
char** compare(char* input, char** search_index, int lower_limit, int upper_limit, int number_of_words)
{   
    
    
    int middle = (lower_limit+((upper_limit-lower_limit)/2)); //get middle the middle of the buffer 
    printf("Middle: %i, upper_limit: %i, lower_limit: %i\n", middle, upper_limit, lower_limit); //printf for debugging
    int diff = strcmp(input, *(search_index+middle)); //compare Strings

    if((middle==lower_limit) || (middle==upper_limit)) // wenn middle same as lower limit, search long enough
    {
        if(strcmp(input, *(search_index+middle)))   //then when strcmp not 0 return NULL because middle and lower limit are same when word is found,
        {                                           //so extra step to get correctly return word
            return NULL;
        }
    }

    if(diff<0)
    {
        upper_limit = middle; //if input smaller than buffer word, upper_limit must be smaller
    }
    else if(diff>0)
    {
        lower_limit = middle; //if input bigger than buffer word, need to raise lower_limit  
    }
    else
    {
        printf("Word: %s at number: %i \n", *(search_index+middle), middle); //Print found word at place for debugging
        return search_index + middle; //return Word
    }
    
    

    return compare(input, search_index, lower_limit, upper_limit, number_of_words);    
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
    
    close(wortbuffer);

    printf("Make List\n");
    char** search_index = malloc(read_length);
    search_index[i] = BFBuffer;
    
    for(int x=0; x<read_length; x++)
    {
        if (*((char*)BFBuffer+x) == 0)
        {
            search_index[++i] = BFBuffer+(++x);
            //printf("%s, %i\n", (char*)search_index[i], i);
            
        }        
    }
    return compare(input, search_index, 0, i, i);
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
        
        void* res = create_search_index(input); //create list and compare 
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