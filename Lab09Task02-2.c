#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
Program which takes a file descriptor as a string parameter and reads from it along with recording the number of bytes it is.
*/
int main(int argc, char *argv[])
{
int data_processed;
char buffer[BUFSIZ + 1];
int file_descriptor;
memset(buffer, '\0', sizeof(buffer));
//scan argv[1] and record as an integer to file_descriptor
sscanf(argv[1], "%d", &file_descriptor);
//reads from file
data_processed = read(file_descriptor, buffer, BUFSIZ);
printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
exit(EXIT_SUCCESS);
}
