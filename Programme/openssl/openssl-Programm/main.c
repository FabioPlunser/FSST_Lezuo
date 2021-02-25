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



void Error_handling(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int do_decrypt(char *ciphertext, int ciphertext_len, char *key, char *iv, char* plaintext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;
    
    if(!(ctx = EVP_CIPHER_CTX_new())) Error_handling();
    
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) Error_handling();

    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) Error_handling();
    plaintext_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plaintext+len, &len)) Error_handling();
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
    if(!(ctx = EVP_CIPHER_CTX_new())) Error_handling();

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) Error_handling();

    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) Error_handling();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) Error_handling();
    ciphertext_len += len;
    
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int diyencryption (unsigned char* key, unsigned char* iv, unsigned char* plaintext, int plaintext_len, unsigned char* ciphertext)
{
    int ciphertext_len;
    ciphertext_len = do_encrypt(plaintext, strlen(plaintext), key, iv, ciphertext);
    return ciphertext_len;
}

int diydecryption(unsigned char* key, unsigned char* iv, unsigned char* plaintext, unsigned char *ciphertext)
{
    char temp[2];   
    unsigned char *hex = malloc(sizeof(unsigned char)*128);
    int x = 0;
    for(int i=0; i<strlen(ciphertext); i++)
    {
        temp[0] = ciphertext[i];
        temp[1] = ciphertext[++i];
        temp[2] = '\0';
        hex[x] = (unsigned int)strtol(temp, NULL, 16);
        x++;
    }
   
    int ciphertext_len = strlen(hex);
    int decryptedtext_len;
    decryptedtext_len = do_decrypt(hex, ciphertext_len, key, iv, plaintext);
    plaintext[decryptedtext_len] = '\0'; 

}
int main()
{   
    unsigned char* key = malloc(16); 
    unsigned char* iv = malloc(16);
    unsigned char ciphertext[128];
    unsigned char plaintext[128];
    int choose;
    printf("AES-128, encrypt und decrypt\n\n");
    printf("1 für encrypt\n2 für decrypt\n3 encrypt Text aus Datei\n4 decrypt Hexzahl aus datei\n5 schließen\n\nEingabe:");
    scanf("%i", &choose);
    
    if(choose == 1)
    {
        printf("Key: ");
        scanf("%s", key);

        printf("IV: ");
        scanf("%s", iv);

        printf("Text der zu encrypten ist: ");
        scanf("%s", plaintext);
        printf("\n\n");

        int plaintext_len = strlen(plaintext);
        int ciphertext_len = diyencryption(key, iv, plaintext, plaintext_len, ciphertext);
        printf("Enryption ergebniss: \n");
        printf("\033[0;31m");
        for(int i=0; i<ciphertext_len; i++)
        {
            printf("%02X", ciphertext[i]);
        }
        printf("\033[0m");
        printf("\n");
        main();
    }
    else if(choose == 2)
    {
        printf("Key: ");
        scanf("%s", key);

        printf("IV: ");
        scanf("%s", iv);

        printf("Ciphertext: ");
        scanf("%s", ciphertext);
        
        diydecryption(key, iv, plaintext, ciphertext);
        
        printf("EVP: Decrypted test is: ");
        printf("\033[0;31m");
        printf("%s", plaintext);
        printf("\033[0m");
        printf("\n\n");

        main();
    }
    else if(choose == 5)
    {
        printf("\033[0;31m");
        printf("Wird geschlossen\n\n");
        printf("\033[0m");
        return 0;
    }
    else
    {
        printf("\033[0;31m");
        printf("Es wurde keine mögliche Aktion ausgewählt\n\n");
        printf("\033[0m");
        return 0;
    }
}
    
