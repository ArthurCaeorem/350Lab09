#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
/*
This program is a variation of Task 1 but instead of using pipes it utilizes a fifo made using the shell command mkfifo task4_fifo
to share data. another way to create a fifo would be using mkfifo within a c program instead of using the command prompt.
*/
int main()
{
int data_processed;
//open fifo
int fd = open("task4_fifo",O_RDWR);
const char some_data[] = "123";
char *buffer;
buffer = malloc(strlen(some_data)*sizeof(char));
for(int i = 0; i < strlen(some_data);i++){
    buffer[i] = some_data[i];
}
memset(buffer, '\0', sizeof(buffer));
//write to fifo
data_processed = write(fd, some_data, strlen(some_data));
printf("Wrote %d bytes\n", data_processed);
//read from fifo
data_processed = read(fd, buffer, sizeof(buffer));
printf("Read %d bytes: %s\n", data_processed, buffer);
exit(EXIT_SUCCESS);
}
