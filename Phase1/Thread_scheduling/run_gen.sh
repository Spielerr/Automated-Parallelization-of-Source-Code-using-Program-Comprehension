g++ thread_scheduling_generator.cpp
./a.out > generated_thread.cpp
g++ -pthread -g generated_thread.cpp -o thread
./thread 1000000

