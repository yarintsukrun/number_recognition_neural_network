//
// Created by ירין on 20/07/2024.
//

#include "Dense.h"

#include "Matrix.h"

Matrix Dense:: get_weights() const{
    return _weights;
}
 Matrix Dense:: get_bias() const {
    return _bias;
}
Matrix (*Dense::get_activation() const)(Matrix) {
    return ActivationFunction;
}

Matrix& Dense::operator()( Matrix& m){
    m = _weights * m;
    m += _bias;
    m = ActivationFunction(m);
    return m;

}