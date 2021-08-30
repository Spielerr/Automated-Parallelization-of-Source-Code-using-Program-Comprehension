echo "Running script"
# ./a.out
gcc temp.c -o test_script
./test_script
g++ -pthread testfile.cpp -o thread2 -lboost_thread -lboost_system
./thread2 1000000
echo "Ending script"
