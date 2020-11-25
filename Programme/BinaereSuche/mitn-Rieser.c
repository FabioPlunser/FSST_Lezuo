// Author: FabioPlunser //
// Date: 24.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specifig Git-location: https://github.com/FabioPlunser/FSST_Lezuo/blob/main/Programme/BinaereSuche/BinaereSuche.c //
// Compiled with make, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// BinaereSuche //

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#define DEBUG 1

#define NUM_FUNCTIONS 6
#define BFBuffer_Size 5000

int diff, i, index_m, num_words, read_length;

void** create_search_index(void * BFBuffer);
void* create_buffer();
void* compare_linear_rl(char* input, void* BFBuffer,void ** nc1, int nc2);
void* compare_linear_nrl(char* input, void* nc1,void ** search_index, int nc2);
void* compare_binary_r(char* input, void* BFBuffer,void ** nc1, int nc2);
void* compare_binary_rl(char* input, void * nc1, void** search_index, int number_of_words);
void* compare_binary_nr(char* input, void* BFBuffer,void ** nc1, int nc2);
void* compare_binary_nrl(char* input, void* BFBuffer,void ** nc1, int nc2);

double response_times[NUM_FUNCTIONS] = {0,0,0,0,0,0};
char* function_names[NUM_FUNCTIONS] = {"Linaer Not Recursive List","Linear Recursive List","Binary Not Recursive","Binary Not Recursive List","Binary Recursive","Binary Recursive with List"};
void* (* compare[NUM_FUNCTIONS])(char*,void*,void**,int) = {&compare_linear_rl,&compare_linear_nrl,&compare_binary_r,&compare_binary_rl,&compare_binary_nr,&compare_binary_nrl};

#ifdef _WIN32

    #include <windows.h>

    void textcolor (int color){

        static int __BACKGROUND;

        HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

        GetConsoleScreenBufferInfo(h, &csbiInfo);

        SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),color + (__BACKGROUND << 4));
    }

#endif

void** create_search_index(void * BFBuffer){

    num_words = 0;
    void** search_index = malloc(read_length);
    search_index[num_words] = BFBuffer;

    for(int x=0; x<read_length; x++)
    {
        if (*((char*)BFBuffer+x) == 0)
        {
            search_index[++num_words] = BFBuffer+(++x);
        }

    }

    #if DEBUG
        printf("Created Search-Array of %i Words\n", num_words);
    #endif

    return search_index;
}

void * create_buffer(){

    void* BFBuffer = malloc(BFBuffer_Size);

    #ifdef linux

        int wortbuffer;

        wortbuffer = open("wortbuffer", O_RDONLY);
        if (wortbuffer == -1)
        {
            perror("open");
        }

        read_length = read(wortbuffer, BFBuffer, BFBuffer_Size);

    #endif

    #ifdef _WIN32

        FILE * file;

        file = fopen("wortbuffer", "r");

        read_length = fread(BFBuffer, 1, BFBuffer_Size, file);

    #endif

    #if DEBUG
        printf("Read %i Bytes from Buffer \n", read_length);
    #endif

    return BFBuffer;

}

//linear not revursive
void * compare_linear_nrl(char* input, void* nc1,void ** search_index, int nc2){

    int iLauf = 0;

    while (iLauf < num_words) {
        if (strcmp(input, (*((char **)search_index + (iLauf++)))) == 0){
            return (*((char **)nc1 + iLauf));
        }
    }

    return NULL;
}

//linear revursive
void* compare_linear_rl(char* input, void* BFBuffer,void ** nc1, int nc2){

    if (strcmp(input, (*((char **)nc1 + (index_m++)))) == 0){
        return (*((char **)nc1 + index_m));
    }else if (index_m < num_words) {
        return compare_linear_rl(input, BFBuffer, nc1, nc2);
    }else{
        return NULL;
    }
}

// binary not recursive
void* compare_binary_nr(char* input, void* BFBuffer,void ** nc1, int nc2){

    int word_correction = 0;

    while(diff !=0)
    {
        if (diff > 0)
        {
            index_m += (read_length/i);
        }
        else
        {
            index_m -= (read_length/i);
        }
        while((*((char*)BFBuffer+index_m-1)) != 0){
            index_m++;
            word_correction++;
        }
        diff = strcmp(input, (char*)BFBuffer+index_m);
        index_m -= word_correction;
        word_correction = 0;
        i *= 2;
        if(i>read_length) return NULL;
    }
    return BFBuffer;
}

//binary recursive
void* compare_binary_r(char* input, void* BFBuffer,void ** nc1, int nc2){

    if (diff > 0)   //if input bigger than BFBuffer go right to a bigger word in Buffer
    {
        index_m+=(read_length/i); //go to the half of the half of the half of the half of the half and eventually found word
        while(*((char*)BFBuffer+index_m-1) != 0){
            index_m++; //"go" right
        }

        diff = strcmp(input, (char*)BFBuffer+index_m); //compare new word with input word
        i = i*2; //set new half of halt
    }
    else
    {
        index_m-=(read_length/i);    //all the same as the top but go to left if input is smaller than actual word in Buffer
        while(*((char*)BFBuffer+index_m-1) != 0){
            index_m--;
        }

        diff = strcmp(input, (char*)BFBuffer+index_m);
        i = i*2;
    }

    if(diff == 0) //if input word and Buffer word are the same reset variables and return word from buffer
    {
        return BFBuffer+index_m;
    }
    if(i>read_length) return NULL; //catch overflow if word is not in Buffer

    return compare_binary_r(input, BFBuffer, nc1, nc2);    //recursive loop
}


// recursive V2 with list
void* compare_binary_rl(char* input, void * nc1, void** search_index, int number_of_words){

    int jump_distance = number_of_words/2;

	int moin = diff;
	diff = strcmp(input, *((char **)search_index + index_m));
    // printf("Index: %i, Diff: %i, String: %s\n", number_of_words, diff, *((char **)search_index + index_m));

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
        index_m -= jump_distance;
        if(moin < 0) index_m --;
    }
    else if(diff>0)
    {
        index_m += jump_distance;
        if (moin > 0) index_m ++;
    }

	if (index_m < 0){
		index_m = 0;
	}else if (index_m > num_words){
		index_m = num_words;
	}

    return compare_binary_rl(input, nc1, search_index, jump_distance);
}

// bsearch
int comparfunction(const void * a, const void * b){

    int idx = 0;
    char * str1 = (char *) a;
    char * str2 = (char *) b;

    while ((*(str1+idx) != 0) & (*(str2+idx) != 0)) {
        if (((*(str1+idx)) - (*(str2+idx))) != 0) {
            return ((*(str1+idx)) - (*(str2+idx)));
        }
        idx ++;
    }
    return ((*(str1+idx)) - (*(str2+idx)));
}

void* bsearch_meins(const void *__key, const char ** __base, size_t __nmemb, size_t __size, int (__compar)(const void *,const void *)){

    size_t __l, __u, __idx;
    const void * __p;
    int __comparison;

    __l = 0;
    __u = __nmemb;
    while (__l < __u){
        __idx = (__l + __u) / 2;
        // __p = (void *) (((const char *) __base) + (__idx * __size)); geht nicht
        __p = (void *) (((const char **) __base) + (__idx * __size));
        __comparison = (*__compar) (__key, __p);
        if (__comparison < 0)
            __u = __idx;
        else if (__comparison > 0)
            __l = __idx + 1;
        else
            return (void *) *(__base + (__size * __idx));
    }

    return NULL;
}

void* compare_binary_nrl(char* input, void* BFBuffer,void ** nc1, int nc2){

    void * found = BFBuffer;

    // void* found = bsearch_meins(input,  BFBuffer, num_words, 1, comparfunction);

    return found;
}

int main(){

    int function_pointer = 0;
    int search_index_pointer = 0;
    void* BFBuffer = create_buffer();
    void* search_index = create_search_index(BFBuffer);

    #ifdef linux
        struct timeval tv_begin, tv_end, tv_diff;
    #endif

    while(search_index_pointer < num_words){
        // Reset Globals
        diff = 1;
        i = 2;
        index_m = 0;

        #ifdef linux
            gettimeofday(&tv_begin, NULL); //get time before finding word
        #endif

        void* res = (*compare[function_pointer])((*((char **)search_index + search_index_pointer)), BFBuffer, search_index,num_words);

        #ifdef linux
            gettimeofday(&tv_begin, NULL); //get time after finding word
            timersub(&tv_end, &tv_begin, &tv_diff); //subtract times to get the time how long it took
            response_times[function_pointer] += tv_diff.tv_usec;
        #endif

        #ifdef _WIN32
            if (res != NULL) {
                textcolor(2);
            }else{
                textcolor(4);
            }
            printf("\t%s (%s) : %s\n",
                    function_names[function_pointer],
                    (*((char **)search_index + search_index_pointer)),
                    ((res != NULL) ? "Found ": "Not found ")
            );
            textcolor(15);
        #endif
        #ifdef linux
            printf("\t%s (%s) : %s in (%li seconds %li  microseconds)\n",
                    function_names[function_pointer],
                    (*((char **)search_index + search_index_pointer)),
                    ((res != NULL) ? "Found ": "Not found "),
                    tv_diff.tv_sec,
                    tv_diff.tv_usec
            );
        #endif

        if ((++function_pointer) >= NUM_FUNCTIONS){
            search_index_pointer++;
            function_pointer = 0;
            printf("New Word : %s\n", (*((char **)search_index + search_index_pointer)));
        }
    }

    for (function_pointer = 0; function_pointer < NUM_FUNCTIONS;function_pointer++) {
        printf("Average Response Time of %s : %f\n",
                function_names[function_pointer],
                response_times[function_pointer]/search_index_pointer
        );
    }

}
