gcc -g my_sort1.c -o test.o
./test.o
gdb --batch --command=test.gdb --args ./test.o 5 > out.txt
python3 paralleliser.py my_sort1.c
g++ -fopenmp -g generated_parallel.cpp 2> error
./a.out 