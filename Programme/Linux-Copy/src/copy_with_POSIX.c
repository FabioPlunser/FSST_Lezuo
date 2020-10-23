#include <unistd.h> define BUF_SIUE 8192
int main(int argc, char** argv){
	
	char buffer[BUF_SIZE];
	
	input_file = open(argv[1], O_RDONLY); output_file = open(argv[2], O_WRONLY | O_CREAT, 0664); 
	read(input_file, &buffer, BUF_SIZE) write(output_file, &buffer, ())
}
