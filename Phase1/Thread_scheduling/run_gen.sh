g++ thread_scheduling_generator.cpp
./a.out > generated_thread.cpp
g++ -pthread generated_thread.cpp -o thread
./thread

