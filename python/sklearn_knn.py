#!/usr/bin/env python
import sklearn
import numpy as np
from sklearn.neighbors import KNeighborsClassifier

neigh = KNeighborsClassifier(n_neighbors=5)

train_features = np.random.rand(50000, 1280)
labels = np.array(np.random.rand(50000) > 0.5, np.uint8)


neigh.fit(train_features, labels)

test_feature = np.random.rand(10000, 1280)
predict = neigh.predict(test_feature)

print(predict.shape)
