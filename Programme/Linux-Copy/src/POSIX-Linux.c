// Author: FabioPlunser //
// Date: 24.10.2020 //
// GIT-Repo: https://github.com/FabioPlunser/FSST_Lezuo
// Specifig Git-location: https://github.com/FabioPlunser/FSST_Lezuo/blob/main/Programme/Linux-Copy/src/POSIX-Linux.c //
// Compiled with Cmake, in WSL using Ubuntu 20.0.4, as you can see in my Repo //

// File Copy with POSIX //

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> //needed for the correct addresses of the open, read, write commands

#define BUF_SIZE 20 //open a file and read 20Bytes write 20Bytes repeat till complete source has been copied

#if defined(__linux__) 			//needed beceause linux doesn't need O_BINARY, windows does some wodo magic at the beginning of binary files
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
#endif


#if defined(_WIN64) || defined(_WIN32)		//nedded because windows needs O_BINARY in open
int copy(int argc, char* source, char*destination)
{
	int input_file, output_file, read_length, write_length; 
	void* buffer = malloc(BUF_SIZE); //allocate Buffer

	if(argc != 3){
		printf("Usage: exe sroucefile destinationfile\n");
		return 1;
	}

	input_file = open(source, O_RDONLY | O_BINARY); //open source file, also if it's binary open it as binary file
	if (input_file == -1){ //check if source file has been opened, if not print error: No such file or directory
		perror("open");
		return 2;
	}	
	
	output_file = open(destination, (O_RDWR && O_TRUNC) | O_CREAT | O_BINARY); 	//open Source file as read/write and trunc to start at the beginning of the file
	if (output_file == -1){														//o_creat => create file if doesn't exist yet | O_BINARY open it as a binary file 																					
		perror("open");																	
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
#endif

int main(int argc, char **argv)
{
	copy(argc, argv[1], argv[2]);
}
