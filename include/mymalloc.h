


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct BlockHeader { 
    size_t size; // Size of the allocated block
    struct BlockHeader * next ; /*we store the next pointer position in order */                   
} BlockHeader;



#define BLOCKSIZE sizeof(BlockHeader) /*here the size of a size_t*/



void* mymalloc(size_t taille); 


void myfree(void* pointer); 