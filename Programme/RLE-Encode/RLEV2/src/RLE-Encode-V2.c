// Author: FabioPlunser //
// Date: 21.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// RLE-Encode//

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RLEN 100

char* encode(char* str){
    
    char* string = str;
    int istrlen = strlen(string);
    char* output = malloc(MAX_RLEN);
    char* count = malloc(MAX_RLEN);

    int j, i, x = 0;

    for(i=0; *string != '\0'; i++){    
        
        *(output+i) = *string;
        for(j=0; *string == *(output+i); j++){
            string++;
        }
        sprintf(count, "%i", j);
        //*(output+(++i)) = *count;

        for (x =0; x<strlen(count); x++){
            *(output+(++i)) = *(count+x);
        }
    }
    free(count);
    *(output+(++i)) == '\0';
    
    return output;
}

int main(int argc, char **argv){
    
    char str[MAX_RLEN];

    do {
        if (fgets(str, MAX_RLEN, stdin) == NULL){
            break;
        }
        
        str[MAX_RLEN] = 0; 
        str[strlen(str)-1] = 0;

        char* res= encode(str);

        printf("Output>: %s\n", res);
        free(res);
    }
    while (strlen(str)>1);
    
}
