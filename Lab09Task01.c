#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int Read_End = 0;
int Write_End = 1;
/*
Program that takes the pipe1.c program from the book and slightly modifies it so the buffer is of 
the exact size of the string rather than being of a arbitraily large size.
When you reverse the write and read ends, an error is given since you are trying to provide input and get output from the wrong 
sides of the pipe.
*/
int main()
{
int data_processed;
int file_pipes[2];
const char some_data[] = "123";
char *buffer;
//set size of buffer to size of some_data
buffer = malloc(strlen(some_data)*sizeof(char));
//buffer becomes copy of some_data
for(int i = 0; i < strlen(some_data);i++){
    buffer[i] = some_data[i];
}
memset(buffer, '\0', sizeof(buffer));
//pipe is checked to see if it executed correctly
if (pipe(file_pipes) == 0) {
    //write text to pipe
data_processed = write(file_pipes[Write_End], some_data, strlen(some_data));
printf("Wrote %d bytes\n", data_processed);
    //read text from pipe
data_processed = read(file_pipes[Read_End], buffer, sizeof(buffer));
printf("Read %d bytes: %s\n", data_processed, buffer);
exit(EXIT_SUCCESS);
}
exit(EXIT_FAILURE);
}
