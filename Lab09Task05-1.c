#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<errno.h>
#include "header.h"
/*
Program that creates a shared memory within the current working directory.
*/
int main()
{
int shmid;
key_t key;
struct Memory *shm;
key = ftok(".", 'x'); //key is made with id x
if ((shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666)) <0) //gets IPC shared memory segment with permissions RW-RW-RW-
{
perror("shmget error \n");
exit (1);
}
shm = (struct Memory *) shmat(shmid, NULL, 0); //Attaches shared memory segment with Memory struct (defined in header.h)
if ((long)shm == -1) //error check
{
perror("shmat error \n");
exit (1);
}
//initializes aspects of shm
shm->status = NOT_READY;
shm->gostop = GO;
exit(0);
}

