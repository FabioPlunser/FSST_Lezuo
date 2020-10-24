#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 20

int writing(char * file_name,char * buffer, int iLength) {

	int iRead = 0;
	size_t  O_TRUNC, O_RDWR;

	int f_handler = open(file_name, O_RDWR && O_TRUNC);

	printf("output-file: %i\n", f_handler);
	iRead = write(f_handler,buffer,iLength);

	close(f_handler);

	return iRead;
}


int copy(char* source, char* destination)
{
	int input_file, output_file, read_length, write_length;
	int O_RDONLY, O_RDWR, O_CREAT, O_WRONLY, O_APPEND;
	size_t  O_TRUNC;
	void* buffer = calloc(BUF_SIZE, sizeof(char));
	
	input_file = open(source, O_RDONLY); 
	// output_file = open(destination, O_RDWR && O_TRUNC);
	
	printf("input-file: %i\n", input_file);
	printf("output-file: %i\n", output_file);
	
	

	while((read_length = read(input_file, buffer, BUF_SIZE)) > 0){
		printf("read: %i\n", read_length);
		write_length = writing(destination, buffer, read_length);
		if(write_length != read_length)
		{
			printf("Error du hure \n");
		}
		printf("write: %i\n", write_length);
	}
	
	
	

	close(input_file);
	close(output_file);	
}

int main(int argc, char **argv)
{

	copy(argv[1], argv[2]);
	
}
