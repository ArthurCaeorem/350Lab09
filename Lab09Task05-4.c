#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<errno.h>
#include "header.h"
/*
Program that operates on a second screen that reads input into shared memory as it is sent and outputs a result.
Terminates when EOF is reached. (since this uses stdin, that would be ctrl+D)
*/
int main()
{
int shmid, n, int1, int2;
key_t key;
struct Memory *shm;
//make key
key = ftok(".", 'x');
//recieve shmid from key
if ((shmid = shmget(key, sizeof(struct Memory), 0)) <0)
{
perror("shmget error \n");
exit (1);
}
//connect shm struct to ID
shm = (struct Memory *) shmat(shmid, NULL, 0); 
if ((long)shm == -1)
{
perror("shmat error \n");
exit (1);
}
//terminates when gostop becomes something other than GO
while (shm->gostop == GO)
{
    //waiting zone while input is sent from other process
while (shm->status != FILLED)
{
    //breaking condition for waiting zone. for when sender reaches EOF
if (shm->gostop == STOP)
break;
;
}
//break condition for whole loop when stdin reaches EOF
if(feof(stdin)){
    break;
    }
//prints output from shm
printf("The sum is %d\n",shm->data.i1 + shm->data.i2);
//signals to other process that input is taken.
shm->status = TAKEN;
}
shmdt((void *) shm); //detach shm from shared memory.
exit(0);
}

