import pandas as pd
import os
from pycparser import c_parser
import numpy as np

root = 'data/'
# ppl = Pipeline('3:1:1', 'data/')
# ppl.run()

from gensim.models.word2vec import Word2Vec


from gensim.models import Word2Vec
  
from nltk.cluster import KMeansClusterer
import nltk
import numpy as np 
  
from sklearn import cluster
from sklearn import metrics

X = []
label_names = []

with open("targets.txt") as f:
    l = f.readlines()[2::]
for i in range(len(l)):
    l[i] = l[i].strip("\n")
    l[i] = l[i].split(" ", maxsplit=1)
    l[i][1] = list(map(float, l[i][1].split()))
    X.append(l[i][1])
    label_names.append(l[i][0])
print(X[0], label_names[0])


NUM_CLUSTERS = 4
from sklearn import cluster
from sklearn import metrics
kmeans = cluster.KMeans(n_clusters=NUM_CLUSTERS)
kmeans.fit(X)
# print(model.vocab, X[:10])

labels = kmeans.labels_
centroids = kmeans.cluster_centers_
 
# print ("Cluster id labels for inputted data")
print (labels)
print (len(labels))
# print ("Centroids data")
# print (centroids)
# print ("Score (Opposite of the value of X on the K-means objective which is Sum of distances of samples to their closest cluster center):")
# print (kmeans.score(X))
 
# silhouette_score = metrics.silhouette_score(X, labels, metric='euclidean')

# print ("Silhouette_score: ")
# print (silhouette_score)

# str_corpus = [''.join(c) for c in corpus]




# s = set()
# d = {}
# for i in range(len(labels)):
#     if labels[i] not in s:
#         s.add(labels[i])
#         print(i)
#         d[labels[i]] = [X_[0][i], X_[1][i]]
        # print(labels[i], X_[i], i, end = "\n\n")
# print(model.vocab)

# words = list(model.vocab)
# for i, word in enumerate(words):  
    # print (word + ":" + str(labels[i]))

# print(labels[0], X_[0])
# print(labels[10], X_[10])
# print(labels[20], X_[20])
# print(labels[30], X_[30])
# print(labels[40], X_[40])
# print(X_[50])
# model2 = Word2Vec(corpus, size=128)
# print(model2[model2.wv.vocab])
# print("INPUT: ", c_code)
# print("\nPrediction Cluster: ", kmeans.predict(model2[model2.wv.vocab])[0], d[kmeans.predict(model2[model2.wv.vocab])[0]][1])
# print("\nThe given program closely matches to:\n", d[kmeans.predict(model2[model2.wv.vocab])[0]][0].strip("\n"))







import numpy as np

from sklearn.datasets import make_blobs
from sklearn.cluster import KMeans

import matplotlib.pyplot as plt
plt.style.use('ggplot')

import seaborn as sns

# Generate some random clusters
# X, y = make_blobs()
# kmeans = KMeans(n_clusters=3).fit(X)

# plot the cluster centers and samples 
# sns.scatterplot(kmeans.cluster_centers_[:,0], kmeans.cluster_centers_[:,1], 
#                 marker='+', 
#                 color='black', 
#                 s=200)

T = []
# label_names_ = []
# for i in range(len(labels)):
    # label_names_.append(label_names)
for i in X:
    T.append(sum(i)/len(i))
# for i in labels:
#     print(i, d[i][1])
# print(len(T), len(labels))
# print(le)
sns.swarmplot(label_names, T)
plt.savefig('kmeans.png')
