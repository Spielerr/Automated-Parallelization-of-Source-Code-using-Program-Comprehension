g++ thread_scheduling_generator_D.cpp
./a.out > generated_thread.cpp
g++ -pthread -g generated_thread.cpp -lboost_thread -lboost_system -o thread
./thread 1000000


