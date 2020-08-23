import numpy as np
import scipy.stats as st

def gkern(kernlen=5, nsig=3):
    """Returns a 2D Gaussian kernel.
    borrowed from https://stackoverflow.com/questions/29731726/how-to-calculate-a-gaussian-kernel-matrix-efficiently-in-numpy
    """

    x = np.linspace(-nsig, nsig, kernlen+1)  # [-3.  -1.8 -0.6  0.6  1.8  3. ]
    x = st.norm.cdf(x)  # [0.0013499  0.03593032 0.27425312 0.72574688 0.96406968 0.9986501 ]
    kern1d = np.diff(x)  # [0.03458042 0.2383228  0.45149376 0.2383228  0.03458042]
    kern2d = np.outer(kern1d, kern1d)
    return kern2d/kern2d.sum()

kernel = gkern()
print(kernel)
