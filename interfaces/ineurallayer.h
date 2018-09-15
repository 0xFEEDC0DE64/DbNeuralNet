#ifndef INEURALLAYER_H
#define INEURALLAYER_H

#include <QList>

class INeuron;
class INeuralNet;

class INeuralLayer
{
public:
    virtual void pulse() = 0;
    virtual void applyLearning() = 0;
    virtual void initializeLearning() = 0;

    virtual INeuron *addNeuron(qreal bias) = 0;
    virtual QList<INeuron *> &neurons() = 0;
    virtual const QList<INeuron *> &neurons() const = 0;
};

#endif // INEURALLAYER_H
