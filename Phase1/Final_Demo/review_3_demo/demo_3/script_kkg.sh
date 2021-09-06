echo start
# cd ./demo_3

echo first
java -jar "/mnt/d/Spielerr/College/7th_sem/capstone/Capstone_Project/clava/Clava.jar" match_param_args.lara -p testfile_demo_3.cpp > test_o_lara.txt
echo second
java -jar "/mnt/d/Spielerr/College/7th_sem/capstone/Capstone_Project/clava/Clava.jar" fn_names_line_no.lara -p testfile_demo_3.cpp > test_o_lara_2.txt
java -jar "/mnt/d/Spielerr/College/7th_sem/capstone/Capstone_Project/clava/Clava.jar" fill_input_4.lara -p testfile_demo_3.cpp > test_o_lara_3.txt
python3 read_lara_o.py
python3 read_lara_o_ip3.py
python3 get_main_code.py
python3 read_lara_o_ip4.py

echo third
java -jar "/mnt/d/Spielerr/College/7th_sem/capstone/Capstone_Project/clava/Clava.jar" FunctionReplacer.lara -p testfile_demo_3.cpp 2>&1
mv -f ./woven_code/testfile_demo_3.cpp ./testfile_demo_3.cpp

g++ -g thread_scheduling_generator.cpp
./a.out > output.cpp
g++ -std=c++2a -fopenmp -pthread output.cpp
./a.out
# ./a.out > output.txt
echo end
