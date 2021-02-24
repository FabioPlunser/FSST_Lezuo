// Author: FabioPlunser //
// Date: 17.2.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specific Git-location: https://github.com/FabioPlunser/FSST_Lezuo/tree/main/Programme/openssl/openssl-Programm //
// Compiled with make, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// openssl //

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

//Basierend auf http://www.firmcodes.com/how-do-aes-128-bit-cbc-mode-encryption-c-programming-code-openssl/
//und https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>

int do_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char* plaintext);
int do_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);




unsigned char* diyencryption (unsigned char* key, unsigned char* iv, unsigned char* plaintext, unsigned char ciphertext[128])
{
    int ciphertext_len;
    ciphertext_len = do_encrypt(plaintext, strlen(plaintext), key, iv, ciphertext);
    BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);

    // unsigned char* returnvalue;
    // for(int i=0; i<ciphertext_len; i++)
    // {
    //     returnvalue[i] = ciphertext[i];
    // }
    // returnvalue[ciphertext_len] = '\0';
    // return returnvalue;    
}

unsigned char* diydecryption(unsigned char* key, unsigned char* iv, unsigned char plaintext[128], unsigned char ciphertext[128])
{

    unsigned char hex[128]={0};
    char temp[2];
    int x = 0;
    for(int i; i<strlen(ciphertext); i++)
    {
        temp[0] = ciphertext[i];
        temp[1] = ciphertext[++i];
        temp[2] = '\0';
        hex[x] = (unsigned int)strtol(temp, NULL, 16);
        x++;
        printf("Hex: %X", hex[x]);
    }

    // int decryptedtext_len;
    // decryptedtext_len = do_decrypt(hex, sizeof(hex)/4, key, iv, plaintext);
    // plaintext[decryptedtext_len] = '\0';
    // printf("EVP: Decrypted test is: %s \n", plaintext);
    
    // AES_KEY dec_key;
    // AES_set_decrypt_key(key, sizeof(key)*8, &dec_key);
    // AES_cbc_encrypt(hex, plaintext, sizeof(hex)/4, &dec_key, iv, AES_DECRYPT);
    // printf("AES_KEY: Decrypted test is: %s\n", plaintext);
}
int main()

{   
    char* sciphertext= "AAE365272C81078AB6116B361831D0F6A5D3C8587E946B530B7957543107F15E";
    
    unsigned char cipertext={0xAA, 0x34, }
    unsigned char key[16];
    unsigned char iv[16];

    for(int i = 0; i<16; i++)
    {
        key[i] = 'B';
        iv[i] = 'B';
    }

    unsigned char* Plaintext = "Schoene Crypto Welt";    
    unsigned char ciphertext[128];
    unsigned char plaintextout[128];
    diyencryption(key, iv, Plaintext, ciphertext);
    printf("enryption ergebniss: ");
    for(int i=0; i<strlen((char*)ciphertext)-4; i++)
    {
        printf("%X", ciphertext[i]);
    }
    printf("\n");
    
    // printf("Ciphertext TEST: %s", ciphertext);
    // printf("\n\n");
    // BIO_dump_fp (stdout, (const char *)ciphertext, strlen(ciphertext));

    diydecryption(key, iv, plaintextout, ciphertext);
    // printf("Decrypted text is: %s\n", plaintextout);
    
}
    
