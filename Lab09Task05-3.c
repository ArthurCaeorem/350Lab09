#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<errno.h>
#include "header.h"
/*
Program that infinitely takes 2 ints as input from stdin and puts it into shared memory to be used by the recieving process.
*/
int main()
{
int shmid;
//2 ints ahead for checker so loop knows 100% when ctrl+D is used.
int l = 1;
int p = 1;
key_t key;
struct Memory *shm;
int i1,i2;
//key is made
key = ftok(".", 'x');
//id is recieved from key
shmid = shmget(key, sizeof(struct Memory), 0);
//shm struct is connected to shared memory
shm = (struct Memory *) shmat(shmid, NULL, 0);
shm->gostop = GO;
shm->status = NOT_READY;
//loop that goes infinitely until CTRL+D is used
while(l != -1 && p != -1)
{
printf("First int: ");
l = scanf("%d", &i1);
shm->data.i1 = i1;
//breaking condition #1
if(l == -1){
    printf("\n");
break;
}
printf("Second int: ");
p = scanf("%d", &i2);
shm->data.i2 = i2;
shm->status = FILLED;
//stopping condition for whole loop (probably isnt necessary but it had it in just to be 100% sure it stopped when I wanted it to.)
if(p == -1){
    printf("\n");
break;
}
    //waiting zone for process while it waits for other process to finish with its data
while(shm->status != TAKEN){
}
printf("Data has been processed by reciever\n");
}
shm->gostop = STOP; //flag to other process that everything has finished here.
shmdt((void *) shm); //disconnects shm from shared memory
exit(0);
}

