#!/usr/bin/env python
# coding = utf-8

import os
import numpy as np
from sklearn.manifold import TSNE

from ggplot import *
from pandas import DataFrame

X = np.random.rand(1000, 3)
X_embedded = TSNE(n_components=2).fit_transform(X)

print X_embedded.shape

plot_data = []
for i in range(X_embedded.shape[0]):
    plot_data.append({'x':X_embedded[i,0],
                      'y':X_embedded[i,1]})

plot_data = DataFrame(plot_data)

print ggplot(plot_data, aes(x='x', y='y') ) \
            + geom_point(size=75,alpha=0.8) \
        + ggtitle("t-sne-visual")

