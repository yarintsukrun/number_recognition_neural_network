// MlpNetwork.h
#ifndef MLPNETWORK_H
#define MLPNETWORK_H
#define NUM_OF_RULU_LAYERS 4
#define INDEX_OF_SOFT_LAYER 3
#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const mmatrix_dims img_dims = {28, 28};
const mmatrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const mmatrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};



class MlpNetwork {
private:
	Matrix _weights[4];
	Matrix _biases[4];
	Dense* layers[NUM_OF_RULU_LAYERS]{};

public:
	MlpNetwork(const Matrix weights[], const Matrix biases[]) {
		for (int i = 0; i < NUM_OF_RULU_LAYERS; ++i) {
			_weights[i] = weights[i];
			_biases[i] = biases[i];
			if (i == INDEX_OF_SOFT_LAYER) {
				layers[i] = new Dense(_weights[i], _biases[i], activation::softmax);
			} else {
				layers[i] = new Dense(_weights[i], _biases[i], activation::relu);
			}
		}
	}

	~MlpNetwork() {
		for (int i = 0; i < NUM_OF_RULU_LAYERS; ++i) {
			delete layers[i];
		}
	}

	digit operator()(Matrix &m) const;
};

#endif // MLPNETWORK_H
