#define NOT_READY -1
#define FILLED 0 
#define TAKEN 1 
#define GO 2 
#define STOP 3 
/*
header file that outlines layout of memory, defines terms used for its use, and layout of ints to be used by other processes
*/
struct ints {
int i1;
int i2;
};
struct Memory {
int status; 
int gostop; 
struct ints data;
};
