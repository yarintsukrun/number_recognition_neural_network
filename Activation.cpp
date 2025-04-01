#include "Matrix.h"
#include <cmath>

namespace activation {
    Matrix relu(Matrix m) {
        Matrix newvec(m.get_rows(), m.get_cols());
        for (int i = 0; i < m.get_rows(); i++) {
            for (int j = 0; j < m.get_cols(); j++) {
                if(m(i,j) > 0) {
                    newvec(i,j) = m(i,j);
                }
            }
        }
        return newvec;
    }

    Matrix softmax(Matrix m) {
        Matrix result(m);
        float mehane = 0;
        for (int i = 0; i < m.get_rows(); i++) {
            for (int j = 0; j < m.get_cols(); j++) {
                result(i,j) = exp(result(i,j));
                mehane += result(i,j);

            }
        }
        if (mehane == 0) {
            throw std::runtime_error("Division by zero");
        }
        Matrix final = (1/mehane) * result;
        return  final;

    }
}
