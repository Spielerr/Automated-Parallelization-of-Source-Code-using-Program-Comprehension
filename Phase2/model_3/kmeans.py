import pandas as pd
import os
from pycparser import c_parser
import numpy as np
from sklearn.metrics.pairwise import distance_metrics

root = 'data/'

from gensim.models.word2vec import Word2Vec


from gensim.models import Word2Vec
  
from nltk.cluster import KMeansClusterer
import nltk
import numpy as np 
  
from sklearn import cluster
from sklearn import metrics

X = []
label_names = []

with open("targets.txt", "r") as f:
    l = f.readlines()[2::]
# l = sorted(l)
for i in range(len(l)):
    l[i] = l[i].strip("\n")
    l[i] = l[i].split(" ", maxsplit=1)
    l[i][1] = list(map(float, l[i][1].split()))
    X.append(l[i][1])
    label_names.append(l[i][0])
# print(X[0], label_names[0])


NUM_CLUSTERS = 1
from sklearn import cluster
from sklearn import metrics
kmeans = cluster.KMeans(n_clusters=NUM_CLUSTERS)
kmeans.fit(X)

import pickle
with open("kmeans.mdl", "wb") as f:
    pickle.dump(kmeans, f)

labels = kmeans.labels_
centroids = kmeans.cluster_centers_
 
# print ("Cluster id labels for inputted data")
# print (labels)
# print (len(labels))





import numpy as np

from sklearn.datasets import make_blobs
from sklearn.cluster import KMeans

import matplotlib.pyplot as plt
plt.style.use('ggplot')

import seaborn as sns

# Generate some random clusters
# X, y = make_blobs()
X = np.array(X)
t = kmeans.transform(X)
# print(t)
distance_clusters = list(t)
for i in range(len(distance_clusters)):
    distance_clusters[i] = list(distance_clusters[i])
#     for j in range(len(distance_clusters[i])):
#         distance_clusters[i][j] = (distance_clusters[i][j], j)
#     # distance_clusters[i] = sorted(distance_clusters[i])
# assigned_cluster = labels

print("Distance from Centers : ", distance_clusters)

sum_distances = [0] * len(distance_clusters[0])
for i in range(len(distance_clusters)):
    for j in range(len(distance_clusters[i])):
        sum_distances[j] += distance_clusters[i][j]


threshold = [0] * len(distance_clusters[0])
for i in range(len(distance_clusters)):
    for j in range(len(distance_clusters[i])):
        threshold[j] += distance_clusters[i][j] * (1 - 2.5 * distance_clusters[i][j] / sum_distances[j])



for i in range(len(threshold)):
    threshold[i] = threshold[i]/len(distance_clusters)
print("Threshold for each center : ", threshold)
with open("threshold", "wb") as f:
    pickle.dump(threshold, f)
# TODO
cluster_mapping = {-1: "other", 0 : "parallel_sort"}
with open("cluster_mapping", "wb") as f:
    pickle.dump(cluster_mapping, f)



# threshold = [1]*len(distance_clusters[0])
# for i in range(len(distance_clusters)):
#     for j in distance_clusters[i]:
#         if(j[0] < threshold[j[1]]):
#             assigned_cluster[i] = j[1]
#             break

# print(assigned_cluster)


# for i in range(len(label_names)):
#     print(label_names[i], labels[i])
# # kmeans = KMeans(n_clusters=3).fit(X)

# # plot the cluster centers and samples 
# print(kmeans.cluster_centers_[:,0])
# # sns.scatterplot(kmeans.cluster_centers_[:,0], kmeans.cluster_centers_[:,1], 
# #                 marker='+', 
# #                 color='black', 
# #                 s=200)

# sns.scatterplot(t[:,0], 1)

# T = []
# # label_names_ = []
# # for i in range(len(labels)):
#     # label_names_.append(label_names)
# for i in X:
#     T.append(sum(i)/len(i))
# # for i in labels:
# #     print(i, d[i][1])
# # print(len(T), len(labels))
# # print(le)
# # sns.swarmplot(label_names, T)
# plt.savefig('kmeans.png')
