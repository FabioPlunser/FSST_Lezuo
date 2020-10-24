#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#define BUF_SIZE 20

int main(int argc, char **argv)
{
	int input_file, output_file, read_length, write_length;
	char* buffer = malloc(BUF_SIZE);
	
		
	if(argc != 3){
		printf("Usage: name of exe file1 file2\n");
		return 1;
	}

	input_file = open(argv[1], O_RDONLY); 
	if (input_file == -1){
		perror("open");
		return 2;
	}	
	
	output_file = open(argv[2], (O_RDWR && O_TRUNC) | O_CREAT, 0644);
	if (output_file == -1){
		perror("open");
		return 3;
	}
	
	
	
	while ((read_length = read(input_file, buffer, BUF_SIZE))>0){
		write_length = write(output_file, buffer, read_length);
		if(write_length != read_length){
			perror("write");
			return 4; 
		}
	}
	printf("Read %s and wrote it in %s file\n",buffer, argv[2]);
	close(input_file);
	close(output_file);
}
