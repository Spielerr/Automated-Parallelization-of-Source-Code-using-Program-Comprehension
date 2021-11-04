gcc time_code.c -o time_code
# g++ input_prog_generator.cpp
# ./a.out 5000 1 > input_prog_test.cpp
# g++ input_prog_test.cpp -o seq
g++ testfile_demo_4.cpp -o seq


java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" match_param_args.lara -p testfile_demo_4.cpp > test_o_lara.txt
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" fn_names_line_no.lara -p testfile_demo_4.cpp > test_o_lara_2.txt
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" fill_input_4.lara -p testfile_demo_4.cpp > test_o_lara_3.txt
python3 read_lara_o.py
python3 read_lara_o_ip3.py
python3 get_main_code.py
python3 read_lara_o_ip4.py

java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" FunctionReplacer.lara -p testfile_demo_4.cpp 2>&1
mv -f ./woven_code/testfile_demo_4.cpp ./testfile_demo_4.cpp

g++ thread_scheduling_generator_kkg.cpp -o m3
./m3 > output3.cpp
g++ -std=c++2a -pthread -fopenmp output3.cpp -o o3


g++ thread_scheduling_generator_4.cpp -o m4
./m4 > output4.cpp
g++ -std=c++2a -pthread -fopenmp output4.cpp -o o4


./time_code ./seq
./time_code ./seq
./time_code ./seq
./time_code ./seq
./time_code ./seq
./time_code ./o3
./time_code ./o3
./time_code ./o3
./time_code ./o3
./time_code ./o3
./time_code ./o4
./time_code ./o4
./time_code ./o4
./time_code ./o4
./time_code ./o4

rm time_code seq m3 o3 m4 o4 