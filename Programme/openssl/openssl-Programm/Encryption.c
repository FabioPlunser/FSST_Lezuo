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


/*
Code From https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
*/
void Error_handling(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int do_decrypt(char *ciphertext, int ciphertext_len, char *key, char *iv, char *plaintext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    if (!(ctx = EVP_CIPHER_CTX_new()))
        Error_handling();

    EVP_CIPHER_CTX_set_padding(ctx, 0);

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        Error_handling();

    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        Error_handling();
    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        Error_handling();
    plaintext_len += len;

    ERR_print_errors_fp(stderr);
    EVP_CIPHER_CTX_cleanup(ctx);
    return plaintext_len;
}

int do_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;
    if (!(ctx = EVP_CIPHER_CTX_new()))
        Error_handling();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        Error_handling();

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        Error_handling();
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        Error_handling();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

/*
Encryption init
*/
int diyencryption(unsigned char *key, unsigned char *iv, unsigned char *plaintext, int plaintext_len, unsigned char *ciphertext)
{
    int ciphertext_len;
    ciphertext_len = do_encrypt(plaintext, strlen(plaintext), key, iv, ciphertext);
    return ciphertext_len;
}

/*
Dencryption init. Was very hard to figure out!!
*/
int diydecryption(unsigned char *key, unsigned char *iv, unsigned char *plaintext, unsigned char *ciphertext)
{
    char temp[2];                                   //temp char array
    unsigned char *hex = malloc(sizeof(unsigned char) * 128);   //array to write ciphertext to
    int x = 0;
    for (int i = 0; i < strlen(ciphertext); i++)    //go through string ciphertext and alwas set two charakters than EOF
    {
        temp[0] = ciphertext[i];
        temp[1] = ciphertext[++i];
        temp[2] = '\0';
        hex[x] = (unsigned int)strtol(temp, NULL, 16);  //add to array of hex values the hex value of the two values put into temp
        x++;
    }

    int ciphertext_len = strlen(hex);
    int decryptedtext_len;
    decryptedtext_len = do_decrypt(hex, ciphertext_len, key, iv, plaintext);
    plaintext[decryptedtext_len] = '\0';
}