#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 20

int main(int argc, char **argv)
{
	int input_file, output_file, read_length, write_length;
	int O_RDONLY, O_RDWR, O_CREAT, O_WRONLY; 
	size_t O_TRUNC;
	char* buffer = malloc(BUF_SIZE);
	
	printf("%s\n", argv[1]);
	printf("%s\n", argv[2]);

	input_file = open(argv[1], O_RDONLY); 
	output_file = open(argv[2], O_WRONLY && O_TRUNC);
	
	printf("input-file: %i\n", input_file);
	printf("output-file: %i\n", output_file);
	
	
	read_length = read(input_file, buffer, BUF_SIZE); 
	printf("read: %i\n", read_length);
	write_length = write(output_file, buffer, strlen(buffer));
	printf("read: %i\n", write_length);
	
	// if (write_length != read_length){
	// 	printf("There has been an error");
	// }	
	// else{
	// 	close(input_file);
	// 	close(output_file);
	// }
	close(input_file);
	close(output_file);
}