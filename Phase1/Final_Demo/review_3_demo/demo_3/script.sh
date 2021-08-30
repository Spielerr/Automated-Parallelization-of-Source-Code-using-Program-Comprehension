echo here1
cd ./demo_3

java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" match_param_args.lara -p testfile_demo_3.cpp > test_o_lara.txt
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" fn_names_line_no.lara -p testfile_demo_3.cpp > test_o_lara_2.txt
python3 read_lara_o.py
python3 read_lara_o_ip3.py
python3 get_main_code.py

java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" FunctionReplacer.lara -p testfile_demo_3.cpp 2>&1
mv -f ./woven_code/testfile_demo_3.cpp ./testfile_demo_3.cpp

g++ thread_scheduling_generator.cpp
./a.out > output.txt
echo here2
