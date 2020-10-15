#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RLEN 100


char* encode(char* str)
{
    char* string = str;
    char* output = malloc(MAX_RLEN);
    char* output_value = malloc(MAX_RLEN);

    int j, i;

    for (i = 0; *string != '\0'; i++)
    {
        *(output+i) = *string;
        for(j = i; j<=strlen(string)-1; j++) 
        {
            if(*string == *(output+i))
            {
                string++;
            } 
        }    
        printf("%c %i", string[i], j);
    }
    
    return output;
    
}

int main(int argc, char **argv)
{
    
    char str[MAX_RLEN]; 
    
    do {
        if (fgets(str, MAX_RLEN, stdin) == NULL)
        {
            printf("Empty String");
            break;
        } 

        str[MAX_RLEN] = 0;  // --> '\0'
        str[strlen(str)-1] = 0;

        char* res = encode(str);

        printf(">: %s\n", res);
        free(res);
    }
    while (strlen(str) > 1);
}