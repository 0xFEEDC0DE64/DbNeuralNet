#ifndef INEURON_H
#define INEURON_H

#include "ineuronsignal.h"
#include "ineuronreceptor.h"

class INeuralLayer;
class NeuralFactor;

class INeuron : public INeuronSignal, public INeuronRepetor
{
public:
    virtual void pulse() = 0;
    virtual void applyLearning(qreal learningRate) = 0;
    virtual void initializeLearning() = 0;

    virtual qreal error() const = 0;
    virtual void setError(qreal error) = 0;

    virtual NeuralFactor *bias() = 0;
    virtual const NeuralFactor *bias() const = 0;
};

#endif // INEURON_H
