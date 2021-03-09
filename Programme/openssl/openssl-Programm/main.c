// Author: FabioPlunser //
// Date: 17.2.2021 - 8.03.2021 //
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
#include <fcntl.h>

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <sys/stat.h> 


#if defined(__linux__)

int input_plaintext_from_file(char *source, unsigned char *key, unsigned char *iv, unsigned char *plaintext, unsigned char *ciphertext);
int input_ciphertext_from_file(char *source, unsigned char *key, unsigned char *iv, unsigned char *plaintext, unsigned char *ciphertext);



int main()
{
    unsigned char *key = malloc(16);
    unsigned char *iv = malloc(16);
    unsigned char ciphertext[128];
    unsigned char plaintext[128];
    unsigned char path_plaintext[1000];
    unsigned char path_ciphertext[1000];
    int choose;
    printf("\033[1m\033[32m");
    printf("\n \e[4mWillkommen zu AES-128, encrypt und decrypt\e\n\n");
    printf("\033[0m");
    printf("1 fuer encrypt\n2 fuer decrypt\n3 Encrypt eines Plaintextes aus einer txt datei\n4 Decrypt eines Cipthertextes aus einer txt Datei\n5 schliessen\n\nEingabe:");
    scanf("%i", &choose);

    if (choose == 1)
    {
        printf("Key: ");
        //scanf("%[^\n]", key);
        scanf("%s", key);
        printf("IV: ");
        scanf("%s", iv);
        printf("Text der zu verschluesseln ist: ");
        scanf(" %[^\n]", plaintext); //%%[^\n]
        printf("\n");
        int plaintext_len = strlen(plaintext);
        int ciphertext_len = diyencryption(key, iv, plaintext, plaintext_len, ciphertext);
        printf("\033[1m\033[32m");
        printf("Verschluesselung: \n");
        printf("\033[0m");
        printf("\033[0;31m");
        for (int i = 0; i < ciphertext_len; i++)
        {
            printf("%02X", ciphertext[i]);
        }
        printf("\033[0m");
        printf("\n");
        main();
    }
    else if (choose == 2)
    {
        printf("Key: ");
        scanf("%s", key);

        printf("IV: ");
        scanf("%s", iv);

        printf("Zu entschluesselnder Text in \033[0;31m HEX \033[0m");
        scanf("%s", ciphertext);

        diydecryption(key, iv, plaintext, ciphertext);

        printf("Entschuesellung: ");
        printf("\033[0;31m");
        printf("%s", plaintext);
        printf("\033[0m");
        printf("\n\n");

        main();
    }
    else if (choose == 3)
    {
        printf("Key: ");
        scanf("%s", key);

        printf("IV: ");
        scanf("%s", iv);

        printf("Path zur \033[0;31m txt \033[0m Datei wo der Plaintext drinnen steht: ");
        scanf("%s", path_plaintext);
        printf("\n\n");

        int ciphertext_len = input_plaintext_from_file(path_plaintext, key, iv, plaintext, ciphertext);
        printf("Verschluesselung: \n");
        printf("\033[0;31m");
        for (int i = 0; i < ciphertext_len; i++)
        {
            printf("%02X", ciphertext[i]);
        }
        printf("\033[0m");
        printf("\n");
        main();
    }
    else if (choose == 4)
    {
        printf("Key: ");
        scanf("%s", key);

        printf("IV: ");
        scanf("%s", iv);

        printf("Path zur \033[0;31m txt \033[0m Datei wo der Ciphertext drinnen steht: ");
        scanf("%s", path_ciphertext);
        printf("\n\n");

        printf("Path Ciphertext: %s\n", path_ciphertext);
       
        input_ciphertext_from_file(path_ciphertext, key, iv, plaintext, ciphertext);
        printf("Entschuesellung: ");
        printf("\033[0;31m");
        printf("%s", plaintext);
        printf("\033[0m");
        printf("\n\n");
        main();
    }
    else if (choose == 5)
    {
        printf("\033[0;31m");
        printf("Wird geschlossen\n\n");
        printf("\033[0m");
        
        main();
    }
    else
    {
        printf("\033[0;31m");
        printf("Es wurde keine moegliche Aktion ausgewaehlt\n\n");
        printf("\033[0m");
        
        main();
    }
}
#endif

#if defined(_WIN64) || defined(_WIN32)

int main()
{
    printf("Only for Linux Use")
}
#endif
