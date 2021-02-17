// Author: FabioPlunser //
// Date: 17.2.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specific Git-location: https://github.com/FabioPlunser/FSST_Lezuo/blob/main/Programme/BinaereSuche/BinaereSuche.c //
// Compiled with make, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// openssl //

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>





int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char* plaintext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))

    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    plaintext_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plaintext+len, &len))
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}
int main()
{
    unsigned char *key = (unsigned char*)"BBBBBBBBBBBBBBBB" ;
    unsigned char *iv = (unsigned char*)"BBBBBBBBBBBBBBBB";
    unsigned char ciphertext[128] = "AAE365272C81078AB6116B361831D0F6A5D3C8587E946B530B7957543107F15E";
    unsigned char decryptedtext[128];
    int decryptedtext_len, ciphertext_len;

    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);
    decryptedtext[decryptedtext_len] = '\0';

    printf("Decrypted test is: %s", decryptedtext);
}