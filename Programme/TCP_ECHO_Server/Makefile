output: TCP_echo_server.o
	gcc TCP_echo_server.o -o output -lpthread

TCP_echo_serber.o: TCP_echo_server.c
	gcc -c TCP_echo_server.c -lpthread

clean:
	rm *.o output
