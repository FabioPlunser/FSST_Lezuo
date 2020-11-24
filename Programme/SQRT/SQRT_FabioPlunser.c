#include <stdio.h>

int iInput;
int result = 0;

int square(int isqrt){      //squaring by double adding as long as isqrt's smaller then the input
    int i = 0;              //what the idea is, is that from 0 the programm is squaring as long as the output 
    i++;                    //is smaller than the input number
    int result = 0;         // so 0*0 = 0 | 1*1=1 | 2*2=4 and so on

    for(; i<=isqrt; i++){
        int j = 0;
        j++;        

        for (; j<=isqrt; j++){
            result++;
        }
    }
    return result;
}
int my_qrt(int iInput){

    int Endresult = -1; //-1 because the suqring starts at 0
    int isqrt = 0;
    
    while (square(isqrt) <= iInput)
    {   
        isqrt++;
        Endresult++;
    }
    printf("sqrt(%i) = %i", iInput, Endresult);

}

int main(){
    printf("Number for square root: ");
    scanf("%i", &iInput);
    my_qrt(iInput);

}




