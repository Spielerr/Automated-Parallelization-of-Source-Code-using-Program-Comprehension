rm time_code a.out seq m3 o3 m4 o4 

gcc time_code.c -o time_code
g++ input_prog_generator.cpp
./a.out 10000 5 > input_prog_test.cpp
g++ input_prog_test.cpp -o seq


# java -jar "/mnt/d/Spielerr/College/7th_sem/capstone/Capstone_Project/clava/Clava.jar" match_param_args.lara -p input_prog_test.cpp > test_o_lara.txt
# java -jar "/mnt/d/Spielerr/College/7th_sem/capstone/Capstone_Project/clava/Clava.jar" fn_names_line_no.lara -p input_prog_test.cpp > test_o_lara_2.txt
# java -jar "/mnt/d/Spielerr/College/7th_sem/capstone/Capstone_Project/clava/Clava.jar" fill_input_4.lara -p input_prog_test.cpp > test_o_lara_3.txt
# python3 read_lara_o.py
# python3 read_lara_o_ip3.py
# python3 get_main_code.py
# python3 read_lara_o_ip4.py

# java -jar "/mnt/d/Spielerr/College/7th_sem/capstone/Capstone_Project/clava/Clava.jar" FunctionReplacer.lara -p input_prog_test.cpp 2>&1
# mv -f ./woven_code/input_prog_test.cpp ./input_prog_test.cpp

g++ thread_scheduling_generator_kkg.cpp -o m3
./m3 > output3.cpp
g++ -std=c++2a -pthread output3.cpp -o o3


g++ thread_scheduling_generator_4.cpp -o m4
./m4 > output4.cpp
g++ -std=c++2a -pthread output4.cpp -o o4


echo "Sequential time:"
./time_code ./seq
echo "Method 3:"
./time_code ./o3
echo "Method 4:"
./time_code ./o4