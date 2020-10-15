#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RLEN 10


char* encode(char* str)
{
    int count = 0;
    char* output;

    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == str[i+1])
        {
            ++count;
        }
        sprintf(output, "%s%i", str, count);
        return output;        
    } 
}

int main(int argc, char **argv)
{
    
    char str[MAX_RLEN]; 
    
    do {
        if (fgets(str, MAX_RLEN, stdin) == NULL) break;

        str[MAX_RLEN] = 0;  // --> '\0'
        str[strlen(str)-1] = 0;

        char* res = encode(str);

        printf(">:%s\n", res);
        free(res);
    }
    while (strlen(str) > 1);
}