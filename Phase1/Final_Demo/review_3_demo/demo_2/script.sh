echo here1
cd ./demo_2
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" match_param_arg_fut_prom.lara -p testfile_demo_2.cpp > test_o_lara.txt
python3 read_lara_o.py
g++ -pthread scheduler.cpp -o demo_2_ex
./demo_2_ex > output.txt