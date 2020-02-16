#include "txtgen/convolution2d.h"

CvltSepKernelT KBlur3 = {
  3, 9, {1, 1, 1}, {1, 1, 1}
};

CvltSepKernelT KGaussianBlur3 = {
  3, 16, {1, 2, 1}, {1, 2, 1}
};

CvltSepKernelT KGaussianBlur5 = {
  5, 256, {1, 4, 6, 4, 1}, {1, 4, 6, 4, 1}
};

CvltSepKernelT KEdgeV3 = {
  3, 1, {1, 2, 1}, {-1, 0, 1}
};

CvltSepKernelT KEdgeH3 = {
  3, 1, {-1, 0, 1}, {1, 2, 1}
};

CvltKernelT KLaplace3 = {
  3, 1, {-1, -1, -1, -1, 8, -1, -1, -1, -1}
};
