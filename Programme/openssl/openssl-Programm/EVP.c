#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>


// #include <C:/OpenSSL-Win64/nclude/openssl/aes.h>
// #include <C:/OpenSSL-Win64/include/openssl/evp.h>
// #include <C:/OpenSSL-Win64/include/openssl/err.h>

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

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new())) Error_handling();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) Error_handling();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) Error_handling();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) Error_handling();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}