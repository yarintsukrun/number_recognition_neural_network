#define LEVELS 4
#define LASTLEVEL 3
#include "MlpNetwork.h"
#include "Activation.h"


digit MlpNetwork::operator()( Matrix &m) const {
    Matrix copyofm = m.vectorize();
    for (int level = 0; level < NUM_OF_RULU_LAYERS; ++level) {
        copyofm = layers[level]->operator()(copyofm);
    }
    Matrix lastvec = copyofm;

    digit result;
    result.value = lastvec.argmax();
    result.probability = lastvec(result.value, 0);

    return result;
}
