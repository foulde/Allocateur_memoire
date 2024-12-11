#include <stdio.h>
#include <assert.h>
#include "../include/mymalloc.h"
void test_mallocvoid(size_t n){
    for (int i = 0 ; i< n ; i++ ){

    void * out = mymalloc(0); 
    assert(out==NULL && "the null pointer was not allocated to null  ");
    myfree(out) ; 
    }
}

void test_malloc_normal(size_t n){
for (int i = 0 ; i< n ; i++ ){

    void * out = mymalloc(4096);
    assert(out!=NULL && "the returned pointer is null");

    myfree(out);
}
    
}


void test_malloc_small_malloc(size_t n){
for (int i = 0 ; i< n ; i++ ){
    void * out = mymalloc(100);
    assert(out!=NULL && "the returned pointer is null");
    myfree(out);

}
}


void test_malloc_big_malloc( size_t n ){


    for (int i = 0 ; i< n ; i++ ){
    void * out = mymalloc(55555555);
    assert(out!=NULL && "the returned pointer is null");
    myfree(out);
    }

}



int main(){

    test_mallocvoid(100); 
    

    return 0; 
}