// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
namespace activation {

    typedef Matrix (*SoftmaxFunction)(Matrix);
    typedef Matrix (*ReluFunction)(Matrix);

    Matrix softmax( Matrix m);
    Matrix relu( Matrix m);
}

#endif // ACTIVATION_H