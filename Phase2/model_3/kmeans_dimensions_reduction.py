import pandas as pd
import os
from pycparser import c_parser
import numpy as np

import numpy as np
from sklearn.manifold import TSNE
import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
import os

# Importing all necessary libraries.
import numpy as np
from numpy import linalg
from numpy.linalg import norm
from scipy.spatial.distance import squareform, pdist

# We import sklearn and TSNE.
import sklearn
from sklearn.manifold import TSNE
from sklearn.datasets import load_digits
from sklearn.preprocessing import scale

# We'll hack a bit with the t-SNE code in sklearn.
from sklearn.metrics.pairwise import pairwise_distances
from sklearn.manifold._t_sne import (_joint_probabilities,
                                    _kl_divergence)
#from sklearn.utils.extmath import _ravel
# Random state.
RS = 25111993

# We'll use matplotlib for graphics.
import matplotlib.pyplot as plt
import matplotlib.patheffects as PathEffects
import matplotlib
# %matplotlib inline

# We import seaborn to make nice plots.
import seaborn as sns
sns.set_style('darkgrid')
sns.set_palette('muted')
sns.set_context("notebook", font_scale=1.5,
                rc={"lines.linewidth": 2.5})

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


def scatter(x, colors):
    # We choose a color palette with seaborn.
    palette = np.array(sns.color_palette("hls", 18))

    # We create a scatter plot.
    f = plt.figure(figsize=(12, 12))
    ax = plt.subplot(aspect='equal')
    sc = ax.scatter(x[:,0], x[:,1], lw=0, s=100,
                    c=palette[colors.astype(np.int)])
    #plt.xlim(-25, 25)
    #plt.ylim(-25, 25)
    ax.axis('on')
    ax.axis('tight')

    # We add the labels for each digit.
    txts = []
    for i in range(18):
        # Position of each label.
        xtext, ytext = np.median(x[colors == i, :], axis=0)
        txt = ax.text(xtext, ytext, str(i), fontsize=64)
        txt.set_path_effects([
            PathEffects.Stroke(linewidth=5, foreground="w"),
            PathEffects.Normal()])
        txts.append(txt)

    return f, ax, sc, txts

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


NUM_CLUSTERS = 3
from sklearn import cluster
from sklearn import metrics
kmeans = cluster.KMeans(n_clusters=NUM_CLUSTERS)
kmeans.fit(X)
# print(model.vocab, X[:10])

labels = kmeans.labels_
centroids = kmeans.cluster_centers_

digits_proj = TSNE(random_state=RS).fit_transform(X)

sns.palplot(np.array(sns.color_palette("hls", 3)))
scatter(digits_proj, labels)
plt.savefig('new_kmeans.png', dpi=120)
 
# print ("Cluster id labels for inputted data")
# print (labels)
# print (len(labels))
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







# import numpy as np

# from sklearn.datasets import make_blobs
# from sklearn.cluster import KMeans

# import matplotlib.pyplot as plt
# plt.style.use('ggplot')

# import seaborn as sns

# Generate some random clusters
# X, y = make_blobs()
# X = np.array(X)
# t = kmeans.transform(X)
# print(t)
# # kmeans = KMeans(n_clusters=3).fit(X)

# # plot the cluster centers and samples 
# print(kmeans.cluster_centers_[:,0])
# sns.scatterplot(kmeans.cluster_centers_[:,0], kmeans.cluster_centers_[:,1], 
#                 marker='+', 
#                 color='black', 
#                 s=200)

# sns.scatterplot(t[:,0], t[:,1], palette=sns.color_palette("Set1", n_colors=15))

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
