echo here1
cd ./demo_4

java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" match_param_args.lara -p testfile_demo_4.cpp > test_o_lara.txt
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" fn_names_line_no.lara -p testfile_demo_4.cpp > test_o_lara_2.txt
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" fill_input_4.lara -p testfile_demo_4.cpp > test_o_lara_3.txt
python3 read_lara_o.py
python3 read_lara_o_ip3.py
python3 get_main_code.py
python3 read_lara_o_ip4.py

java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" FunctionReplacer.lara -p testfile_demo_4.cpp 2>&1
mv -f ./woven_code/testfile_demo_4.cpp ./testfile_demo_4.cpp

g++ thread_scheduling_generator_4.cpp
./a.out > output.cpp
rm *.txt
echo here2
