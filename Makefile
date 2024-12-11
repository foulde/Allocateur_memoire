

all: test benchmark 

test : 
	gcc  src/test.c src/mymalloc.c -o fin 
	./fin	
	

benchmark : 
	gcc  src/benchmark.c src/mymalloc.c -o benchmark 
	./benchmark
	rm benchmark 
