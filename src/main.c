#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


/*we define a blockheader struct in order to store the size of the allocated block 
usefull for memory de-allocation */
// typedef struct BlockHeader { 
//     size_t size;                 // Size of the allocated block
// } BlockHeader;

typedef struct BlockHeader { 
    size_t size; // Size of the allocated block
    // struct BlockHeader * next ; /*we store the next pointer position in order */                   
} BlockHeader;



#define BLOCKSIZE sizeof(BlockHeader) /*here the size of a size_t*/


void* mymalloc(size_t taille) {
    if (taille == 0) {
        perror("The size must be greater than zero");
        return NULL;  // Return NULL on error
    }

    

    // Use mmap to allocatlse memory
    
    void *ptr = mmap(NULL, taille +BLOCKSIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return NULL;  // Return NULL if mmap fails
    }

    BlockHeader* header = (BlockHeader*)ptr; //we cast the allocated pointer into ou struct of type block header 
    header->size = taille;// we store the size of the allocated space into 
    

    // return ptr;  // Return the allocated pointer
    return (void*)((char*)ptr + BLOCKSIZE); /* we cast ptr onto a char ptr as void ptr do not support pointer 
    arithmetics 
    the rest of the line describe how malloc return the address just after the header 
    this will be usefull later for de-allocation we will subtract the header size to the adress and cast the 
    pointer to a block header to access the size attribute and the size of memory block needed for 
    using munmap*/ 

}


// void* mymalloc2(size_t taille) {

// }





void myfree (void* pointer){

    if (pointer == NULL){
        return; 
    }

    BlockHeader *header = (BlockHeader*) ((char*)pointer - BLOCKSIZE);  /* we substract the BLOCKSIZE to access the 
    size of the allocated memory bloc*/
    // size_t taille = (size_t*) pointer;
     /* we take the size of the mapping using the first entry 
    being the block header */

    size_t taille  = header->size + BLOCKSIZE; /* we add BLOCKSIZE in order to also free the space 
    dedicated to the header*/ 
    // munmap( pointer ,taille ); 
    if (munmap( header ,taille ) != 0 ){
        perror("munmap failed"); 
    }
}



int main() {
    // size_t size = 1024;  // Allocate 1024 bytes
    // size_t size = 1024;  // Allocate 1024 bytes
    // void *memory = mymalloc(size);
    void *memory = mymalloc(100);

    if (memory == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Memory allocated at address: %p\n", memory);


    myfree(memory); 
    // Remember to free the memory
    // munmap(memory, size);




    size_t nb_iteration = 19;
    // size_t taille = 1024*8*8*8*8*8;
    size_t taille = 1024;

    struct timespec start, end;
    double default_malloc_time, custom_malloc_time;

    /*CUSTOM DEFAULT CALCULATION*/
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < nb_iteration; i++) {
        void* ptr = malloc(taille);
        if (ptr == NULL) {
            printf("Default malloc failed\n");
            return 1;
        }
        free(ptr);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    default_malloc_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; 
    /*divide to get in seconds*/



    
    /*CUSTOM MALLOC CALCULATION*/
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < nb_iteration; i++) {
        void* ptr = mymalloc(taille);
        if (ptr == NULL) {
            printf("Custom mymalloc failed\n");
            return 1;
        }
        myfree(ptr);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    custom_malloc_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Default malloc  time: %.6f seconds\n", default_malloc_time);
    printf("Custom mymalloc time: %.6f seconds\n", custom_malloc_time);

    /*we shoudl put all those calcultion into a specific test file where we try for : 
    -small size alloc 
    -large size alloc 
    -low number of iteration
    -large number of iteration

    from what we can observe implementing the most basic function we can observe we 

    */



    return 0;
}





