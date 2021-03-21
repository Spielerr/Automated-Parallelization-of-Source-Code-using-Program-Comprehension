gcc -g my_sort.c -o test.o
gdb --batch -command=test.gdb --args ./test.o > out.txt

