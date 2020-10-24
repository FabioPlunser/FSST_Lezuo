#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 20

int writing(char * file_name,char * buffer,int iLength) {

	int iRead = 0;
	size_t  O_TRUNC, O_RDWR;

	int f_handler = open(file_name, O_RDWR && O_TRUNC);

	iRead = write(f_handler,buffer,iLength);

	close(f_handler);

	return iRead;
}

int copy(char* source, char* destination)
{
	int input_file, output_file, read_length, write_length;
	size_t  O_TRUNC, O_RDWR;
	char* buffer = malloc(BUF_SIZE);

	input_file = open(source, O_RDWR || O_TRUNC);
	output_file = open(destination, O_RDWR || O_TRUNC);

	printf("input-file: %i\n", input_file);
	printf("output-file: %i\n", output_file);

	while((read_length = read(input_file, buffer, BUF_SIZE)) > 0){
		printf("read: %i\n", read_length);
		write_length = writing(destination,buffer,read_length);
		if(write_length != read_length)
		{
			printf("Error du hure \n");
		}
		printf("write: %i\n", write_length);
	}

	printf("read: %i\n", read_length);

	close(input_file);
	close(output_file);

	return 0;
}

int main(int argc, char **argv)
{

	copy(argv[1], argv[2]);

}
