#!/usr/bin/env python
import sklearn
import numpy as np
import os
from sklearn.neighbors import KNeighborsClassifier


def get_feature(split='train'):
    feature_dir = os.path.join('tmp/triplet_feature/', split)

    feature_files = os.listdir(feature_dir)

    names = [file_name[:6] for file_name in feature_files if 'feature' in file_name]

    features = np.zeros((40000, 1280))
    labels = np.zeros((40000))

    idx = 0
    for name in names:
        feature = np.load('{}/{}_feature.npy'.format(feature_dir, name))
        label = np.load('{}/{}_label.npy'.format(feature_dir, name))
        n_feature = feature.shape[0]

        features[idx:idx+n_feature] = feature
        labels[idx:idx+n_feature] = label

        idx += n_feature

    return features[:idx], labels[:idx]



'''
train_feature, train_label = get_feature('train')
test_feature, test_label = get_feature('test')

np.save('tmp/train_feature.npy', train_feature)
np.save('tmp/train_label.npy', train_label)
np.save('tmp/test_feature.npy', test_feature)
np.save('tmp/test_label.npy', test_label)
'''


train_feature = np.load('tmp/train_feature.npy')
train_label = np.array(np.load('tmp/train_label.npy'), np.uint8)
test_feature = np.load('tmp/test_feature.npy')
test_label = np.array(np.load('tmp/test_label.npy'), np.uint8)

'''
# KNN predict
neigh = KNeighborsClassifier(n_neighbors=10)

print 'start fitting train data'
neigh.fit(train_feature, train_label)

print 'start predicting'
predict_label = neigh.predict(test_feature)

np.save('tmp/test_predict_label.npy', predict_label)
'''

test_predict_label = np.array(np.load('tmp/test_predict_label.npy'), np.uint8)

from sklearn.manifold import TSNE
import matplotlib.pyplot as plt
import matplotlib.cm as cm



embedding = TSNE(n_components=2).fit_transform(train_feature[:10000])

x = embedding[:,0]
y = embedding[:,1]
classes = train_label[:10000]

unique = list(set(classes))
colors = [cm.jet(float(i)/max(unique)) for i in unique]


for i, u in enumerate(unique):
    xi = [x[j] for j  in range(len(x)) if classes[j] == u]
    yi = [y[j] for j  in range(len(x)) if classes[j] == u]
    plt.scatter(xi, yi, c=colors[i], label=str(u), s=5)

plt.legend()
plt.title("Triplet feature of train set.")
plt.show()

