cd ./model/pre_processor/
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" fill_input_5.lara -p inline_input.c > test_o_lara_5.txt
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" get_function_call.lara -p inline_input.c > inliner_o_lara.txt
python3 read_lara_o_ip5.py
python3 read_inliner_o.py
cd ../
pwd > t2.txt
python3 --version > t3.txt
python3 inline.py
python3 predict_2.py 2> t1.txt
python3 test.py > pgm_comp_output.txt
python3 function_replacer_NN.py