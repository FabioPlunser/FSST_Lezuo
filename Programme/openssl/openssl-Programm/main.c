// Author: FabioPlunser //
// Date: 17.2.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specific Git-location: https://github.com/FabioPlunser/FSST_Lezuo/tree/main/Programme/openssl/openssl-Programm //
// Compiled with make, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// openssl //

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

//Basierend auf http://www.firmcodes.com/how-do-aes-128-bit-cbc-mode-encryption-c-programming-code-openssl/
//und 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>


int do_decrypt(char *ciphertext, int ciphertext_len, char *key, char *iv, char* plaintext);

int main()
{
    
    unsigned char key[16];
    unsigned char iv[16];

    memset(key, 'B', 16);
    memset(iv, 'B', 16);

    unsigned char ciphertext[128] = {
    0xAA, 0xE3, 0x65, 0x27, 0x2C, 0x81, 0x07, 0x8A, 0xB6, 0x11, 0x6B, 0x36, 0x18, 0x31, 0xD0, 0xF6, 
    0xA5, 0xD3, 0xC8, 0x58, 0x7E, 0x94, 0x6B, 0x53, 0x0B, 0x79, 0x57, 0x54, 0x31, 0x07,0xF1, 0x5E
    };

    unsigned char* plaintext="Schoene Crypto Welt";
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