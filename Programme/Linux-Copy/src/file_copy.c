/* #Titel: file-copy mit POSIX
   #Autor: Mitterhuber Lorenz
   #Datum: 22.10.2020
   #Git-Repo: https://github.com/lorenzm24/FSST_Mitterhuber_LZ.git

   #Funktion des Programms:
   Das Programm kopiert den Inhalt einer Datei in eine andere. Der Dateipfad wird der Dateien
   wird in der CMD eingegeben. Die Vorraussetzung ist allerdings, dass die Zeildatei bereits ex-
   istiert.            
*/
//#################################################################################################

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define BUFFER_SIZE 20 //Buffergröße entsprechend der Aufgabenstellung

//------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	int iInHandler, iOutHandler;
    int iRead, iWrite, iClose;
    int O_RDONLY, O_RDWR, O_CREAT;
    size_t O_TRUNC;
    char *buffer = malloc(BUFFER_SIZE);
    

    if(argc != 3){
        printf ("Usage: cp file1 file2");
        return 1;
    }

    iInHandler = open(argv[1], O_RDONLY);
    if (iInHandler == -1) {
            perror ("open");
            return 2;
    }
   
    iRead = read(iInHandler, buffer, BUFFER_SIZE);

    iOutHandler = open(argv[2], O_RDWR && O_TRUNC);
    if (iOutHandler == -1) {
            perror ("open");
            return 2;
    }

    iWrite = write(iOutHandler, buffer, strlen(buffer));
    
    
    iClose = close(iInHandler);
    iClose = close(iOutHandler);
    printf("Copy successful - Files closed\n");
    printf("%i\n", iRead);
    printf("%s\n", buffer);
    printf("%i\n", iWrite);

}