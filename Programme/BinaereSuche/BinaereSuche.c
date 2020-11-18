// Author: FabioPlunser //
// Date: 24.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specifig Git-location: https://github.com/FabioPlunser/FSST_Lezuo/tree/main/Programme/TCP_ECHO_Server //
// Compiled with Cmake, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// TCP-Echo-server //

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include <fcntl.h>

#define BUF_SIZE 100

int copy(int argc, char* source, char*destination)
{
	if(argc != 3){
		printf("Usage: ./nameofprogramm sroucefile destinationfile\n");
		return 1;
	}

	int input_file, output_file, read_length, write_length; 
	void* buffer = malloc(BUF_SIZE); //allocate Buffer

	input_file = open(source, O_RDONLY); //open source file, also if it's binary open it as binary file
	if (input_file == -1){ //check if source file has been opened, if not print error: No such file or directory
		perror("open");
		return 2;
	}	
	
	output_file = open(destination, (O_RDWR && O_TRUNC) | O_CREAT, 0644); 	//open Source file as read/write and trunc to start at the beginning of the file
	if (output_file == -1){																//o_creat => create file if doesn't exist yet | O_BINARY open it as a binary file 																					
		perror("open");																	//0644 only needed for linux, so linux know the permission, 0644 is the normal user permission
		return 3;
	}
	
	while ((read_length = read(input_file, buffer, BUF_SIZE))>0){ 	//read source file and write it in the destination file, with 20Btyes at a time because buffer is only 20Bytes
		write_length = write(output_file, buffer, read_length);		
		if(write_length != read_length){							//if writing doesn't work print error
			perror("write");
			return 4; 
		}
	}
	printf("Read %p and wrote it in %s file\n", buffer, destination);
	
	close(input_file);
	close(output_file);
	free(buffer);  //not really nedded because only 20Bytes big, but if programm runs on SOC you want to save as many memory as needed
}

void* compare(int input)
{
    int input_file, read_length;
    void* buffer = malloc(BUF_SIZE);

    input_file = open("wortbuffer", O_RDONLY);
    if (input_file == -1)
    {
        perror("open");
        return EXIT_FAILURE;
    }

    read_length = read(input_file, buffer, BUF_SIZE);
    if (read_length == -1)
    {
        perror("read");
        return EXIT_FAILURE;
    }
    void* BFbuffer = malloc(read_length);

    read_length = read(input_file, BFbuffer, BUF_SIZE);
    if (read_length == -1)
    {
        perror("read");
        return EXIT_FAILURE;
    }
    
    char* search_inde = malloc(sizeof(input));

    
}

int main()
{
    for(;;)
    {
        char input[100];

        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = 0;

        if(!strlen(input)) break;

        struct timeval tv_begin, tv_end, tv_diff;

        gettimeofday(&tv_begin, NULL);
        void*res = compare(input);//test
        gettimeofday(&tv_begin, NULL);

        timersub(&tv_end, &tv_begin, &tv_diff);

        if(res != NULL)
        {
            printf("found");
        }
        else
        {
            printf("not found");
        }
        printf("in (%id seconds %id microseconds)\n", tv_diff.tv_sec, tv_diff.tv_usec);   
    }
}