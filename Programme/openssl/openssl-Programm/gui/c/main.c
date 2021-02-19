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

int hardgecoded()
{
    unsigned char key[16];
    unsigned char iv[16];

    memset(key, 'B', 16);
    memset(iv, 'B', 16);
    unsigned char decryptedtext[128];
    unsigned char decryptedtext2[128];
                                    
    unsigned char ciphertext2[128] = {0xAA, 0xE3, 0x65, 0x27, 0x2C, 0x81, 0x07, 0x8A, 0xB6, 0x11, 0x6B, 0x36, 0x18, 0x31, 0xD0, 0xF6, 
    0xA5, 0xD3, 0xC8, 0x58, 0x7E, 0x94, 0x6B, 0x53, 0x0B, 0x79, 0x57, 0x54, 0x31, 0x07,0xF1, 0x5E};

    unsigned char decryptedtext[128];
    int decryptedtext_len, ciphertext_len;
    decryptedtext_len = do_decrypt(ciphertext, sizeof(ciphertext)/4, key, iv, decryptedtext);
    decryptedtext[decryptedtext_len] = '\0';
    printf("EVP:\nDecrypted test is: %s\n", decryptedtext);
    
    AES_KEY dec_key;
    AES_set_decrypt_key(key, sizeof(key)*8, &dec_key);
    AES_cbc_encrypt(ciphertext, decryptedtext, sizeof(ciphertext)/4, &dec_key, iv, AES_DECRYPT);
    printf("\nAES_KEY:\nDecrypted test is: %s\n", decryptedtext);
}

int decryption_setup(char* key, char* IV, char* Ciphertext)
{
    printf("Key length: %li\n", strlen(key));
    printf("IV length: %li\n", strlen(IV));

    if((strlen(key)!=16)){
        printf("Key besitzt nicht richtige laenge\n");
        printf("Neuer Key: ");
        scanf("%s", key);
    }              
    if((strlen(IV)!=16))
    {
        printf("IV besitzt nicht richtige laenge\n");
        printf("Neuer IV: ");
        scanf("%s", IV);
    }

    int decryptedtext_len, ciphertext_len;

    if(strlen(Ciphertext)>=128)
    {
        printf("Ciphertext is zu lang");
        return 1;
    }
    else
    {
        unsigned char decryptedtext[128];
        decryptedtext_len = do_decrypt(Ciphertext, sizeof(Ciphertext)/4, key, IV, decryptedtext);
        decryptedtext[decryptedtext_len] = '\0';
        printf("EVP:\nDecrypted test is: %s\n", decryptedtext);
        
        AES_KEY dec_key;
        AES_set_decrypt_key(key, sizeof(key)*8, &dec_key);
        AES_cbc_encrypt(Ciphertext, decryptedtext, sizeof(Ciphertext)/4, &dec_key, IV, AES_DECRYPT);
        printf("\nAES_KEY:\nDecrypted test is: %s\n", decryptedtext);
    }
}

int encryption_setup(char* key, char* IV, char* Plaintext)
{
    printf("Key length: %li\n", strlen(key));
    printf("IV length: %li\n", strlen(IV));
    if((strlen(key)!=16)){
        printf("Key besitzt nicht richtige laenge\n");
        printf("Neuer Key: ");
        scanf("%s", key);
    }              
    if((strlen(IV)!=16))
    {
        printf("IV besitzt nicht richtige laenge\n");
        printf("Neuer IV: ");
        scanf("%s", IV);
    }
    
    printf("Key: %s\n", key);
    printf("IV: %s\n", IV);
    char* ciphertext;
    int ciphertext_len;
    ciphertext_len = do_encrypt(Plaintext, strlen((char*)Plaintext), key, IV, ciphertext);
    printf("Ciphertext ist: \n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);
    printf("Ciphertext: %s\n", ciphertext);
    return 1;
}


int main(int argc, char **argv)
{   
    char* key = malloc(16); 
    char* IV = malloc(16);
    char* Plaintext = malloc(128);
    char* Ciphertext = malloc(128);

    int choose;
    printf("AES-128, encrypt und decrypt\n\n");
    printf("1 für encrypt\n2 für decrypt\n");
    scanf("%i", &choose);

    if(choose == 1)
    {
        printf("Key: ");
        scanf("%s", key);

        printf("IV: ");
        scanf("%s", IV);

        printf("Text der zu encrypten ist: ");
        scanf("%s", Plaintext);
        printf("\n\n");
        encryption_setup(key, IV, Plaintext);
    }
    if(choose == 2)
    {
        printf("Key: ");
        scanf("%s", key);

        printf("IV: ");
        scanf("%s", IV);

        printf("Ciphertext: ");
        scanf("%s", Ciphertext);
        decryption_setup(key, IV, Ciphertext);
    }
    printf("Nichts ausgewählt\n");
}
