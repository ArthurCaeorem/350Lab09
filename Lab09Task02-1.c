#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
Program that takes pipe3.c from the book and modifies it so the appropriate pipes are closed with the parent and child and the child 
waits for the parent to finish. 
*/
int main()
{
int data_processed;
int stat = 0;
int file_pipes[2];
const char some_data[] = "123";
char buffer[BUFSIZ + 1];
pid_t fork_result;
memset(buffer, '\0', sizeof(buffer));
//check to see pipe creation was successful.
if (pipe(file_pipes) == 0) {
    //create fork
fork_result = fork();
//error condition
if (fork_result == (pid_t)-1) {
fprintf(stderr, "Fork failure");
exit(EXIT_FAILURE);
}
if (fork_result == 0) { //child
//close write end
    close(file_pipes[1]);
    //set buffer to file descriptor of read end of pipe
sprintf(buffer,"%d", file_pipes[0]);
//send child to Lab9Task2-2 with the file descriptor for the read end of the pipe.
(void)execl("./Lab9Task2-2", "Lab9Task2-2", buffer, (char *)0);
exit(EXIT_FAILURE);
}
else { //parent
//read end is closed
    close(file_pipes[0]);
    //write to pipe
data_processed = write(file_pipes[1], some_data, strlen(some_data));
//wait for child
wait(&stat);
printf("%d - wrote %d bytes\n", getpid(), data_processed);
}
}
exit(EXIT_SUCCESS);
}
