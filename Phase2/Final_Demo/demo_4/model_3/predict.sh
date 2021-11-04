#!/bin/bash
cd astminer
./cli.sh configs/c_paths3.yaml
# ./cli.sh configs/c_paths1_ss.yaml
# ./cli.sh configs/c_paths2_ss.yaml
# cp output/train/c/data/* ../code2vec/data/c/c.train.c2s
cp output/predict/c/data/* ../code2vec/data/c/c.train.c2s
# cp output/predict/c/data/* ../code2vec/data/c/c.val.c2s
# cp output/val/c/data/* ../code2vec/data/c/c.val.c2s
cd ../code2vec
./preprocess.sh
# ./train.sh

python3 code2vec.py --load models/c/saved_model_iter1.release --predict --export_code_vectors
# python3 -u code2vec.py --data data/c/c --load models/c/saved_model_iter1 --save models_pred/c/saved_model
# python3 code2vec.py --load models_pred/c/saved_model_iter1 --release
# python3 code2vec.py --load models_pred/c/saved_model_iter1.release --save_t2v models_pred/c/p_targets.txt
# cp models_pred/c/p_targets.txt ../p_targets.txt
cp p_targets.txt ../p_targets.txt
cd ..
python3 kmeans_predict.py