#!/bin/bash
cd ./model_3/pre_processor/
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" fill_input_5.lara -p inline_input.c > test_o_lara_5.txt
java -jar "/mnt/c/Users/mayur/Desktop/PES/PES - 6/Capstone Project/CLAVA/Clava.jar" get_function_call.lara -p inline_input.c > inliner_o_lara.txt
python3 read_lara_o_ip5.py
python3 read_inliner_o.py
cd ../
python3 inline.py
cp *.c astminer/data_predict
cd astminer
./cli.sh configs/c_paths3.yaml
cp output/predict/c/data/* ../code2vec/data/c/c.train.c2s
cd ../code2vec
./preprocess.sh

python3 code2vec.py --load models/c/saved_model_iter1.release --predict --export_code_vectors
cp p_targets.txt ../p_targets.txt
cd ..
python3 kmeans_predict.py > pgm_comp_output.txt
python3 function_replacer_NN.py
rm *.c
rm *.txt
rm astminer/data_predict/*
rm pre_processor/*.txt
rm pre_processor/*.c