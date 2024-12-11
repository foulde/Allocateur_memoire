#include "../include/mymalloc.h"

/*we define a blockheader struct in order to store the size of the allocated block 
usefull for memory de-allocation */
// typedef struct BlockHeader { 
//     size_t size;                 // Size of the allocated block
// } BlockHeader;


void* mymalloc(size_t taille) {
    if (taille == 0) {
        // perror("The size must be greater than zero");
        return NULL;  // Return NULL on error
    }

    

    // Use mmap to allocatlse memory
    size_t nb_page = (taille+BLOCKSIZE)/4096 +1 ; 




    void *ptr = mmap(NULL, nb_page *4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return NULL;  // Return NULL if mmap fails
    }

    BlockHeader* header = (BlockHeader*)ptr; //we cast the allocated pointer into ou struct of type block header 
    header->size = ((taille+BLOCKSIZE)/4096 +1)*4096 -BLOCKSIZE;// we store the size of the allocated space into 
    

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



