#include<stdio.h>
#include<sys/shm.h>
#include<errno.h>
#include<stdlib.h>
#include "header.h"
/*
This program erases shared memory of key x inside current working directory.
*/
int main() {
key_t key;
int shmid;
struct Memory shm;
//gets key
key = ftok(".", 'x');
//accesses shared memory from key
if ((shmid = shmget(key, sizeof(struct Memory), 0)) <0)
{
perror("shmget error \n");
exit (1);
}
//removes the shared memory
shmctl(shmid, IPC_RMID, NULL);
exit(0);
}
