#include <stdio .h>
#include <string .h>
#include <stdlib .h>
#include <unistd .h>
#include <sys/types .h>

#include <openssl/aes .h>
#include <openssl/evp .h>
#include <openssl/err .h>


void Error_handling (void)
{
    ERR_print_errors_fp (stderr);
    abort ();
}

int do_decrypt (char* ciphertext, int ciphertext_len, char* key, char* iv, char* plaintext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    if (!(ctx = EVP_CIPHER_CTX_new ())) Error_handling ();

    EVP_CIPHER_CTX_set_padding(ctx, 0);

    if (1 != EVP_DecryptInit_ex (ctx, EVP_aes_128_cbc() , NULL , key , iv) )
    Error_handling();

    if (1 != EVP_DecryptUpdate (ctx, plaintext, &len, ciphertext,
    ciphertext_len )) Error_handling();
    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx , plaintext +len , &len)) Error_handling ();
    plaintext_len += len;

    ERR_print_errors_fp (stderr);
    EVP_CIPHER_CTX_cleanup(ctx);
    return plaintext_len;
}