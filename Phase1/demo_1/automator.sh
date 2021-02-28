gcc -g my_sort.c -o test.o
time ./test.o
gdb --batch --command=test.gdb --args ./test.o 5 > out.txt
python paralleliser.py my_sort.c
g++ -fopenmp -g generated_parallel.cpp 2> error
time ./a.out 