#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
Variation of pipe3.c from task 2 which is formatted to send messages back and forth using 2 pipes

*/
int main()
{
int data_processed, data_processed2;
//pipe 1
int file_pipes[2];
//pipe 2
int pip2[2];
const char some_data[] = "Hello Kiddo!";
char buffer[BUFSIZ + 1];
char buffer2[BUFSIZ + 1];
pid_t fork_result;
memset(buffer, '\0', sizeof(buffer));
//error check for pipe 1
if (pipe(file_pipes) == 0) {
    //error check for pipe 2
if(pipe(pip2) != 0){
    printf("Pipe 2 creation failed.\n");
    exit(EXIT_FAILURE);
}
//fork is created
fork_result = fork();
if (fork_result == (pid_t)-1) {
fprintf(stderr, "Fork failure");
exit(EXIT_FAILURE);
}
if (fork_result == 0) {
    //inappropriate file descriptors are closed from both pipes
    close(pip2[0]);
    close(file_pipes[1]);
    //read end of first pipe and write end of second pipe are turned to strings
sprintf(buffer, "%d", file_pipes[0]);
sprintf(buffer2, "%d", pip2[1]);
//file descriptor strings are send to Lab9Task3-2
(void)execl("./Lab9Task3-2", "Lab9Task3-2", buffer, buffer2, (char *)0);
exit(EXIT_FAILURE);
}
else {
    //inappropriate file descriptors are closed
    close(pip2[1]);
    close(file_pipes[0]);
    //write data to first pipe
data_processed = write(file_pipes[1], some_data, strlen(some_data));
printf("%d - wrote %d bytes\n", getpid(), data_processed);
//buffer for reading from second pipe
char buf[BUFSIZ + 1];
//wait for child to finish its operations
wait();
//read data from second pipe
data_processed2 = read(pip2[0], buf, BUFSIZ);
printf("%d - read %d bytes: %s\n", getpid(), data_processed2, buf);
}
}
exit(EXIT_SUCCESS);
}
