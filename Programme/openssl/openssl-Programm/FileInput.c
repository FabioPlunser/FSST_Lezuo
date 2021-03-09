#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <sys/stat.h> 

void Error_handling(void);
int do_decrypt(char *ciphertext, int ciphertext_len, char *key, char *iv, char *plaintext);
int do_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);
int diyencryption(unsigned char *key, unsigned char *iv, unsigned char *plaintext, int plaintext_len, unsigned char *ciphertext);
int diydecryption(unsigned char *key, unsigned char *iv, unsigned char *plaintext, unsigned char *ciphertext);
int main();


/*
Import plaintext from file and encrypt it.
*/
int input_plaintext_from_file(char *source, unsigned char *key, unsigned char *iv, unsigned char *plaintext, unsigned char *ciphertext)
{
    int size, file, file2, read_length, write_length, plaintext_len;
    struct stat st;

    int istxt = strcmp(source + strlen(source) - 4, ".txt");
    if (istxt == 0)
    {
        printf("Angebene Datei valide\n");
    }
    else
    {
        printf("Angegebne Datei ist keine .txt Datei\n Sie kann nicht verwendet werden\n");
        main();
    }

    stat(source, &st);   
    size = st.st_size;  //check File size for correct buffer allocation
    
    char *charBuffer = malloc(size);
    file = open(source, O_RDONLY);  //open File
    read_length = read(file, charBuffer, size); //read File
    printf("Eingelesene Datei: %s\n", charBuffer);  //show Contents of file

    plaintext_len = strlen(charBuffer); //get length of content
    int ciphertext_len = diyencryption(key, iv, charBuffer, plaintext_len, ciphertext); //encrypt content
    close(file);
    free(charBuffer);
    printf("Home directory: %s\n", getenv("HOME"));
    return ciphertext_len;
}

/*
Import ciphertext from file and decrypt it.
*/
int input_ciphertext_from_file(char *source, unsigned char *key, unsigned char *iv, unsigned char *plaintext, unsigned char *ciphertext)
{
    int size, file, file2, read_length, write_length, plaintext_length;
    struct stat st;

    int istxt = strcmp(source + strlen(source)-4, ".txt");
    if (istxt == 0)
    {
        printf("\033[0;31m");
        printf("Angebene Datei valide\n");
        printf("\033[0m");
    }
    else
    {
        printf("\033[0;31m");
        printf("Angegebne Datei ist keine .txt Datei\n Sie kann nicht verwendet werden\n");
        printf("\033[0m");
        main();
    }
    stat(source, &st);
    size = st.st_size;
   
    char *charBuffer = malloc(size);
    file = open(source, O_RDONLY);
    read_length = read(file, charBuffer, size);
    printf("Eingelesene Datei: %s\n", charBuffer);
    plaintext_length = diydecryption(key, iv, plaintext, charBuffer);
    close(file);
    free(charBuffer);
}
