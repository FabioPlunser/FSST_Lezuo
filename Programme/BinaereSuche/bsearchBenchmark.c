#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEBUG 1

#define NUM_SAMPLES 50

#define START_WORD 0
#define END_WORD 130800
#define STEP_SIZE 100

#define START_FUNCTION 0
#define NUM_FUNCTIONS 6
#define BUFFER_SIZE 4725872
#define NUM_WORDS 356008

int diff, i, index_m, num_words, read_length;

void** create_search_index(void * BFBuffer);
void* create_buffer();
void* compare_linear_rl(char* input, void* BFBuffer,void ** nc1, int nc2);
void* compare_linear_nrl(char* input, void* nc1,void ** search_index, int nc2);
void* compare_binary_r(char* input, void* BFBuffer,void ** nc1, int nc2);
void* compare_binary_rl(char* input, void * nc1, void** search_index, int number_of_words);
void* compare_binary_nr(char* input, void* BFBuffer,void ** nc1, int nc2);
void* compare_binary_nrl(char* input, void* nc1,void ** search_index, int nc2);

double response_times[NUM_FUNCTIONS] = {0,0,0,0,0,0};
char* function_names[NUM_FUNCTIONS] = {"Linaer Not Recursive List","Linear Recursive List","Binary Not Recursive","Binary Not Recursive with List","Binary Recursive","Binary Recursive with List"};
void* (* compare[NUM_FUNCTIONS])(char*,void*,void**,int) = {&compare_linear_rl,&compare_linear_nrl,&compare_binary_nr,&compare_binary_nrl,&compare_binary_r,&compare_binary_rl};

double faktor[NUM_FUNCTIONS]={50,50,1,1,1,1};

void** create_search_index(void * BFBuffer){

    num_words = 0;
    void** search_index = malloc(NUM_WORDS*sizeof(void**));
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

    void* BFBuffer = malloc(BUFFER_SIZE);

    #ifdef linux

        int wortbuffer;

        wortbuffer = open("wortbuffer", O_RDONLY);
        if (wortbuffer == -1)
        {
            perror("open");
        }

        read_length = read(wortbuffer, BFBuffer, BUFFER_SIZE);

    #endif

    #ifdef _WIN32

        FILE * file;

        file = fopen("wortbuffer", "r");

        read_length = fread(BFBuffer, 1, BUFFER_SIZE, file);

    #endif

    #if DEBUG
        printf("Read %i Bytes from Buffer \n", read_length);
    #endif

    return BFBuffer;

}

//linear not revursive
void * compare_linear_nrl(char* input, void* nc1,void ** search_index, int nc2){

    int iLauf = 0;
    int diff;

    while (iLauf < num_words) {
        diff = strcmp(input, (*((char **)search_index + (iLauf++))));
        if (diff == 0){
            return (*((char **)nc1 + iLauf));
        }
    }

    return NULL;
}

//linear revursive
void* compare_linear_rl(char* input, void* BFBuffer,void ** nc1, int nc2){

    int diff = strcmp(input, (*((char **)nc1 + (index_m++))));

    if ((diff != 0) & (index_m<num_words)){
        return compare_linear_rl(input, BFBuffer, nc1, nc2);
    }else if (diff == 0) {
        return (*((char **)nc1 + index_m));
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

    int word_correction = 0;
    if (diff > 0)   //if input bigger than BFBuffer go right to a bigger word in Buffer
    {
        index_m+=(read_length/i);
    }
    else
    {
        index_m-=(read_length/i);    //all the same as the top but go to left if input is smaller than actual word in Buffer
    }

    while(*((char*)BFBuffer+index_m-1) != 0){
        index_m--;
        word_correction++;
        if (index_m < 0){
            index_m = 0;
            if (strcmp(input,(char *)BFBuffer) == 0){
                return BFBuffer;
            }
        }
    }

    diff = strcmp(input, (char*)BFBuffer+index_m);
    index_m += word_correction;
    
    i = i*2;

    if(diff == 0) //if input word and Buffer word are the same reset variables and return word from buffer
    {
        return BFBuffer+index_m;
    }
    if((index_m>read_length) | (i > read_length)) return NULL; //catch overflow if word is not in Buffer

    return compare_binary_r(input, BFBuffer, nc1, nc2);    //recursive loop
}


// recursive V2 with list
void* compare_binary_rl(char* input, void * nc1, void** search_index, int number_of_words){


    int middle = (index_m+((number_of_words-index_m)/2)); //get middle the middle of the buffer 
    // printf("Middle: %i, upper_limit: %i, lower_limit: %i\n", middle, upper_limit, lower_limit); //printf for debugging
    int diff = strcmp(input, *(search_index+middle)); //compare Strings

    if((middle==index_m) || (middle==number_of_words)) // when middle same as lower limit, search long enough
    {
        if(strcmp(input, *(search_index+middle)) != 0)   //then when strcmp not 0 return NULL because middle and lower limit are same when word is found,
        {                                           //so extra step to get correctly return word
            return NULL;
        }
    }

    if(diff<0)
    {
        number_of_words = middle; //if input smaller than buffer word, upper_limit must be smaller
    }
    else if(diff>0)
    {
        index_m = middle; //if input bigger than buffer word, need to raise lower_limit  
    }
    else
    {
        // printf("Word: %s at number: %i \n", *(search_index+middle), middle); //Print found word at place for debugging
        return search_index + middle; //return Word
    }

    return compare_binary_rl(input, nc1, search_index, number_of_words);
}

// bsearch
int comparfunction(const void * a, const void * b){

    return strcmp((char*)a, *((char**)b)); 

    // int idx = 0;
    // char * str1 = (char *) a;
    // char * str2 = (char *) b;

    // while ((*(str1+idx) != 0) & (*(str2+idx) != 0)) {
    //     if (((*(str1+idx)) - (*(str2+idx))) != 0) {
    //         return ((*  (str1+idx)) - (*(str2+idx)));
    //     }
    //     idx ++;
    // }
    // return ((*(str1+idx)) - (*(str2+idx)));
}

void* compare_binary_nrl(char* input, void* nc1,void ** search_index, int nc2){

    void* found = bsearch(input,  search_index, num_words, sizeof(search_index), comparfunction);
    return found;
}

int write_int(int file_handle,int number) {

    char * temp = malloc(20);

    sprintf(temp,"%i",number);

    return write(file_handle,temp,strlen(temp));

}

int write_double(int file_handle,double number) {

    char * temp = malloc(20);

    sprintf(temp,",%-4.0f",number);

    return write(file_handle,temp,strlen(temp));

}

#define HEADER "Time"

int main(){

    int iLauf;
    int function_pointer = START_FUNCTION;
    int search_index_pointer = START_WORD;
    double temp_time;

    void* res;
    void* BFBuffer = create_buffer();
    void* search_index = create_search_index(BFBuffer);

    int csv = open("usage.csv", (O_RDWR | O_TRUNC) | O_CREAT, 0644);
    if (csv == -1){perror("open");}
    write(csv,HEADER,strlen(HEADER));
    for (iLauf = 0;(iLauf+function_pointer) < NUM_FUNCTIONS;iLauf++){
        write(csv,",",1);
        write(csv,function_names[function_pointer+iLauf],strlen(function_names[function_pointer+iLauf]));
    }
    write(csv,"\r\n",2);
    write_int(csv,search_index_pointer);

    struct timeval tv_begin, tv_end, tv_diff;

    while(1){

        if(search_index_pointer>END_WORD)
        {
            break;
        }
        // Get multiple Samples for each Word per Function
        for (iLauf = 0;iLauf < NUM_SAMPLES;iLauf ++){
            if(search_index_pointer>END_WORD)
            {
                break;
            }
            // Reset Globals
            diff = 1;
            i = 2;
            index_m = 0;

            gettimeofday(&tv_begin, NULL);

            res = (*compare[function_pointer])((*((char **)search_index + search_index_pointer)), BFBuffer, search_index,num_words);

            gettimeofday(&tv_end, NULL);

            timersub(&tv_end, &tv_begin, &tv_diff);
            temp_time += tv_diff.tv_usec;

        }

        temp_time = (temp_time * 1000) / ( faktor[function_pointer] * NUM_SAMPLES);

        write_double(csv,temp_time);

        printf("\t%s (%s) : %s in %f  microseconds\n",
                function_names[function_pointer],
                (*((char **)search_index + search_index_pointer)),
                ((res != NULL) ? "Found ": "Not found "),
                temp_time
        );

        response_times[function_pointer] += temp_time;

        temp_time = 0.0;
        

        if (++function_pointer >= NUM_FUNCTIONS){
            search_index_pointer += STEP_SIZE;
            if ((search_index_pointer < END_WORD)){
                function_pointer = START_FUNCTION;
                write(csv,"\r\n",2);
                write_int(csv,search_index_pointer);
                printf("New Word : %s\n", (*((char **)search_index + search_index_pointer)));
            }else{
                return 0;
            }
        }

    }

    printf("\n\n");

    for (function_pointer = START_FUNCTION; function_pointer < NUM_FUNCTIONS;function_pointer++) {
        printf("Average Response Time of %s : %f\n",
                function_names[function_pointer],
                response_times[function_pointer]/((END_WORD-START_WORD)/STEP_SIZE)
        );
    }

    close(csv);

}
