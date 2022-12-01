#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
Variation of pipe4.c or Task2-2 which is formatted to read input from one pipe and 
write output to another pipe with both being string inputs recieved either from command
line input or from another program calling the exec() system call.
*/
int main(int argc, char *argv[])
{
int data_processed, data_processed2;
char buffer[BUFSIZ + 1];
int file_descriptor, fil2;
memset(buffer, '\0', sizeof(buffer));
//record the two file descriptors.
sscanf(argv[1], "%d", &file_descriptor);
sscanf(argv[2], "%d", &fil2);
//read from first file descriptor
data_processed = read(file_descriptor, buffer, BUFSIZ);
printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
char str[] = "Hi, Mom";
//write str to second file descriptor
data_processed2 = write(fil2, str, strlen(str));
printf("%d - wrote %d bytes\n", getpid(), data_processed2);
exit(EXIT_SUCCESS);
}
