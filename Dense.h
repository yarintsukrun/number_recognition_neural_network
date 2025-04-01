// Dense.h

#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"


class Dense {
private:
    Matrix _weights; Matrix _bias;
    Matrix (*ActivationFunction)(Matrix m);

public:
    Dense(const Matrix& weights, const Matrix& bias,
        Matrix (*ActivationFunction)(Matrix m)):
    _weights(weights), _bias(bias), ActivationFunction(ActivationFunction)
        {}
    Matrix get_weights() const;
    Matrix get_bias() const;
    Matrix (*get_activation() const)(Matrix);
    Matrix& operator()( Matrix& m);
};



#endif //DENSE_H