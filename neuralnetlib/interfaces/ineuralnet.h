#pragma once

#include <qglobal.h>

class INeuralLayer;

class INeuralNet
{
public:
    virtual void pulse() = 0;
    virtual void applyLearning() = 0;
    virtual void initializeLearning() = 0;

    virtual qreal learningRate() const = 0;
    virtual void setLearningRate(qreal learningRate) = 0;

    virtual const INeuralLayer *inputLayer() const = 0;
    virtual const INeuralLayer *hiddenLayer() const = 0;
    virtual const INeuralLayer *outputLayer() const = 0;
};
