import pandas as pd
import random
import torch
import time
import numpy as np
from gensim.models.word2vec import Word2Vec
from torch._C import Value
from model import BatchProgramClassifier
from torch.autograd import Variable
from torch.utils.data import DataLoader
import os
import sys
import dill
import pickle


def get_batch(dataset, idx, bs):
    # print(dataset)
    tmp = dataset.iloc[idx: idx+bs]
    data, name = [], []
    for _, item in tmp.iterrows():
        data.append(item[1])
        name.append(item[2])
        # labels.append(item[2]-1)
    return data, name


if __name__ == '__main__':
    root = 'data/'
    query_data = pd.read_pickle(root+'query/blocks.pkl')

    word2vec = Word2Vec.load(root+"train/embedding/node_w2v_128").wv
    embeddings = np.zeros((word2vec.syn0.shape[0] + 1, word2vec.syn0.shape[1]), dtype="float32")
    embeddings[:word2vec.syn0.shape[0]] = word2vec.syn0

    HIDDEN_DIM = 100
    ENCODE_DIM = 128
    LABELS = 104
    EPOCHS = 15
    BATCH_SIZE = 1
    USE_GPU = False
    MAX_TOKENS = word2vec.syn0.shape[0]
    EMBEDDING_DIM = word2vec.syn0.shape[1]
    FINAL_LABELS = {0:"parallel_sort", 1:"parallel_sort", 2:"parallel_sort", 3:"parallel_sort", 4:"BFS", 5:"Knapsack"}
    NUM_OF_CLASSES = len(FINAL_LABELS)

    model = dill.load(open('finalized_model.sav', 'rb'))
    
    

    parameters = model.parameters()
    optimizer = torch.optim.Adamax(parameters)
    loss_function = torch.nn.CrossEntropyLoss()

    i = 0
    # print(len(query_data))
    while i < len(query_data):
        batch = get_batch(query_data, i, BATCH_SIZE)
        i += BATCH_SIZE
        print(batch)
        query_input, fn_name = batch
        model.batch_size = 1
        model.hidden = model.init_hidden()
        output = model(query_input)
        # print(output, output.data)
        # print(output[0][0].data.item())
        sum_ = 0
        for k in range(NUM_OF_CLASSES):
            sum_ += output[0][k].data.item()
        # print(sum_)
        t = 0
        # print("SUM : ", torch.sum(output))
        # t = 0
        # for i in range(NUM_OF_CLASSES):
        #     t += output[0][i].data.item()/sum_
        #     print(output[0][i].data.item()/sum_)
        # print(t)
        value, predicted = torch.max(output.data, 1)
        print(output, value, value/sum_, predicted)
        # if(value<)
        print(fn_name[0], FINAL_LABELS[predicted[0].item()])

# BS : 6.7870e-01,  
# MS : 3.6428e+00,  
# QS : 6.0808e+00, 
# LL : -3.7365e+00,  
# BFS : 1.0830e-02,
# knapsack : 1.1615e+00,