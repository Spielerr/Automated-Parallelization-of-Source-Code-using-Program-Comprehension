#!/bin/bash
cd astminer
./cli.sh configs/c_paths1.yaml
./cli.sh configs/c_paths2.yaml
# ./cli.sh configs/c_paths1_ss.yaml
# ./cli.sh configs/c_paths2_ss.yaml
cp output/train/c/data/* ../code2vec/data/c/c.train.c2s
cp output/val/c/data/* ../code2vec/data/c/c.val.c2s
cd ../code2vec
./preprocess.sh
./train.sh
python3 code2vec.py --load models/c/saved_model_iter1 --release
python3 code2vec.py --load models/c/saved_model_iter1.release --save_t2v models/c/targets.txt
cp models/c/targets.txt ../targets.txt
cd ..
python3 kmeans.py