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
#include <sys/stat.h>
#include <unistd.h> 
#include <fcntl.h>

#define wordbuffer "wortbuffer"


//lower_limit--------------middle-------------------upper_limit//
//0------------------------upper_limit/2------------upper_limit//
//word for example higher than middle word //
//upper_limit/2---------middle----------upper_limit// 

//recursive V2 with list
char** compare_binary_re(char* input, char** search_index, int lower_limit, int upper_limit, int number_of_words)
{   
    int middle = (lower_limit+((upper_limit-lower_limit)/2)); //get middle the middle of the buffer 
    // printf("Middle: %i, upper_limit: %i, lower_limit: %i\n", middle, upper_limit, lower_limit); //printf for debugging
    int diff = strcmp(input, *(search_index+middle)); //compare Strings

    if((middle==lower_limit) || (middle==upper_limit)) // when middle same as lower limit, search long enough
    {
        if(strcmp(input, *(search_index+middle)) != 0)   //then when strcmp not 0 return NULL because middle and lower limit are same when word is found,
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
        // printf("Word: %s at number: %i \n", *(search_index+middle), middle); //Print found word at place for debugging
        return search_index + middle; //return Word
    }
    return compare_binary_re(input,search_index, lower_limit++,upper_limit, number_of_words);    
}




//linear Search recursive
//problem with Segmentation fault if searching for higher words
//word---------------------------------------end//
//-word--------------------------------------end//
//--word-------------------------------------end//
// void* compare_linear(char* input, char** search_index, int lower_limit, int upper_limit, int number_of_words)
// {   

//     if (lower_limit>=number_of_words)
//     {
//         return NULL;
//     }
    
//     if(strcmp(input, *(search_index+(lower_limit++))) == 0){ //compare string and then go one word to the right
//         return (search_index+(--lower_limit)); //if strcmp zero found word
//     }
//     return compare_linear(input,search_index, lower_limit, upper_limit, number_of_words);
// }

//linear Serach none recursive
void* compare_linear(char* input, char** search_index, int lower_limit, int upper_limit, int number_of_words)
{   
    int i = 0;

    while(i<number_of_words)
    {
        if(strcmp(input, *(search_index+(i++))) == 0 ){
            return (search_index+(--i));
        }
    }
}

//compare function for besarch 
int comparfunction(const void * a, const void * b){
    // printf("Comparefunction: 1:%s, 2:%s\n", (char*)a, *((char**)b));
    return strcmp((char*)a, *((char**)b));  
}

//can be done more efficient i think but, this way was the simplest for me
char** compare_all_functions(char* input, char** search_index, int lower_limit, int upper_limit, int number_of_words)
{
    struct timeval tv_begin, tv_end, tv_diff;

    gettimeofday(&tv_begin, NULL);
    char** found_word = compare_binary_re(input,search_index, lower_limit,upper_limit, number_of_words);
    gettimeofday(&tv_end, NULL);
    timersub(&tv_begin, &tv_end, &tv_diff);
    printf("Recursive binary search found word: %s in (%li seconds %li  microseconds)\n", *found_word, tv_begin.tv_sec, tv_end.tv_usec);   //print time
    

    gettimeofday(&tv_begin, NULL);
    found_word = bsearch(input, search_index, number_of_words, sizeof(search_index), comparfunction);
    
    gettimeofday(&tv_end, NULL);
    timersub(&tv_begin, &tv_end, &tv_diff);
    printf("Bsearch found word: %s in (%li seconds %li  microseconds)\n", *found_word, tv_begin.tv_sec, tv_end.tv_usec);   //print time

    gettimeofday(&tv_begin, NULL);
    found_word = compare_linear(input,search_index, lower_limit,upper_limit, number_of_words);
    
    
    gettimeofday(&tv_end, NULL);
    timersub(&tv_begin, &tv_end, &tv_diff);
    printf("Linear search found word: %s in (%li seconds %li  microseconds)\n", *found_word, tv_begin.tv_sec, tv_end.tv_usec);   //print time

    return found_word;  
}




char** create_search_index(char* input)
{
    //set variables 
    int wortbuffer, read_length, i = 0;

    wortbuffer = open(wordbuffer, O_RDONLY);
    if (wortbuffer == -1)
    {
        perror("open");
    }
    struct stat fileStat;
    printf("File Size: \t\t%ld bytes\n",fileStat.st_size);
    char* BFBuffer = malloc(fileStat.st_size);
    read_length = read(wortbuffer, BFBuffer, fileStat.st_size); //writing buffer with 20 Bytes at a time didn't work at all, because the seperation of the word got erased
    
    close(wortbuffer);

    printf("Make List\n");
    char** search_index = malloc(read_length);
    search_index[i] = BFBuffer;
    
    for(int x=0; x<read_length; x++)
    {
        if (*(BFBuffer+x) == 0)
        {
            search_index[++i] = BFBuffer+(++x);
            //printf("%s, %i\n", (char*)search_index[i], i);
            
        }        
    }
    return compare_all_functions(input, search_index, 0, i, i); //compare diy binary_recursiv, bsearch and linear serach
}
int main()
{
    //needed to change main
    for(;;)
    {
        char input[100];

        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;

        if(!strlen(input)) break;
        void* res = create_search_index(input); //create list and compare 
        if(res != NULL)
        {
            printf("found\n");
        }
        else
        {
            printf("not found\n");
        }
       
    }
}