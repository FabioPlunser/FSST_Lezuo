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

int read_length;
int i=0;
void* create_buffer()
{
    int wortbuffer;
    void* BFBuffer = malloc(BFBuffer_Size); 

    wortbuffer = open("wortbuffer", O_RDONLY);
    if (wortbuffer == -1)
    {
        perror("open");
    }
    
    read_length = read(wortbuffer, BFBuffer, BFBuffer_Size); //writing buffer with 20 Bytes at a time didn't work at all, because the seperation of the word got erased
    
    return BFBuffer;
}

int comparfunction(const void * a, const void * b){
    
    char* hallo = *((char**)b);
    printf("Comparefunction: 1:%s, 2:%s\n", (char*)a, hallo);
    return strcmp((char*)a, hallo);
    
}

void** makelist(void* BFBuffer)
{
    void** test = malloc(BFBuffer_Size);
    test[0] = BFBuffer;
    
    for(int x=0; x<BFBuffer_Size; x++)
    {
        if (*((char*)BFBuffer+x) == 0)
        {
            test[++i] = BFBuffer+(++x);
        }
    }
    return test; 
}



void* bsearch_meins (const void *__key, const void *__base, size_t __nmemb, size_t __size, __compar_fn_t __compar)
{
  size_t __l, __u, __idx;
  const void *__p;
  int __comparison;

  __l = 0;
  __u = __nmemb;
  while (__l < __u)
    {
      __idx = (__l + __u) / 2;
      // __p = (void *) (((const char *) __base) + (__idx * __size)); geht nicht
      __p = (void *) (((const char **) __base) + (__idx * __size));
      __comparison = (*__compar) (__key, __p);
      if (__comparison < 0)
	__u = __idx;
      else if (__comparison > 0)
	__l = __idx + 1;
      else
	return (void *) __p;
    }

  return NULL;
}



void* compare(char* input, void* BFBuffer)
{
    void** test = makelist(BFBuffer);
    printf("%i\n", i);
    
    void* found = bsearch_meins(input,  test, i, 1, comparfunction);
   
    return found;   
}



int main()
{
    for(;;)
    {
        char input[100];

        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;

        if(!strlen(input)) break;

        void* BFBuffer = create_buffer(); //get wordfile into a very big buffer
        struct timeval tv_begin, tv_end, tv_diff;
    
        gettimeofday(&tv_begin, NULL); //get time before finding word
        
        void* res = compare(input, BFBuffer);
        

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