#!/bin/bash
cd astminer
./cli.sh configs/c_paths1.yaml
./cli.sh configs/c_paths2.yaml
cp output/train/cpp/data/* ../code2vec/data/cpp/cpp.train.c2s
cp output/val/cpp/data/* ../code2vec/data/cpp/cpp.val.c2s
cd ../code2vec
./preprocess.sh
./train.sh
python3 code2vec.py --load models/cpp/saved_model_iter2 --release
python3 code2vec.py --load models/cpp/saved_model_iter2.release --save_t2v models/cpp/targets.txt
python3 code2vec.py --load models/cpp/saved_model_iter2.release --save_w2v models/cpp/tokens.txt
cp models/cpp/targets.txt ../targets.txt
cd ..
python3 kmeans.py