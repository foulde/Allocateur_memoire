#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "../include/mymalloc.h"









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




    size_t nb_iteration = 1000;
    // size_t taille = 1024*8*8*8*8*8;
    // size_t taille = 1024;
    // size_t taille = 1024;

    struct timespec start, end;
    double default_malloc_time, custom_malloc_time;

    /*CUSTOM DEFAULT CALCULATION*/
    // size_t  rangemax =1<<18;  /*2¹⁸*/
    size_t  rangemax =1e9;   /*2¹⁸*/

    FILE *fptr; 

    fptr = fopen("benchmarks.txt" , "w"); 

    for ( int i =1 ; i < rangemax ; i=i+100000){





    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int j = 0; j < nb_iteration; j++) {
        void* ptr = malloc(i);
        if (ptr == NULL) {
            printf("Default malloc failed\n");
            return 1;
        }
        free(ptr);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    default_malloc_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; 
    /*divide to get in seconds*/

    // printf("je suis passé par la "); 


    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int j = 0; j < nb_iteration; j++) {
        void* ptr = mymalloc(i);
        if (ptr == NULL) {
            printf("Custom mymalloc failed\n");
            return 1;
        }
        myfree(ptr);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    custom_malloc_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;






    fprintf(fptr , "%d ", i); 

    fprintf(fptr , "%f ", default_malloc_time); 

    fprintf(fptr , "%f\n", custom_malloc_time); 


    } 



    fclose(fptr); 




    
    // /*CUSTOM MALLOC CALCULATION*/
    // clock_gettime(CLOCK_MONOTONIC, &start);
    // for (int i = 0; i < nb_iteration; i++) {
    //     void* ptr = mymalloc(taille);
    //     if (ptr == NULL) {
    //         printf("Custom mymalloc failed\n");
    //         return 1;
    //     }
    //     myfree(ptr);
    // }
    // clock_gettime(CLOCK_MONOTONIC, &end);
    // custom_malloc_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // printf("Default malloc  time: %.6f seconds\n", default_malloc_time);
    // printf("Custom mymalloc time: %.6f seconds\n", custom_malloc_time);

    // ; 

    // fptr = fopen("custom.txt" , "w"); 
    // fprintf(fptr , "%f\n", custom_malloc_time); 

    // fclose(fptr); 

    /*we shoudl put all those calcultion into a specific test file where we try for : 
    -small size alloc 
    -large size alloc 
    -low number of iteration
    -large number of iteration

    from what we can observe implementing the most basic function we can observe we 

    */



    return 0;
}
