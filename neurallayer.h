#ifndef NEURALLAYER_H
#define NEURALLAYER_H

#include <QObject>
#include <QList>

#include "interfaces/ineurallayer.h"

class NeuralNet;
class INeuron;

class NeuralLayer : public QObject, public INeuralLayer
{
    Q_OBJECT

public:
    explicit NeuralLayer(NeuralNet *neuralNet);

    // INeuralLayer interface
    void pulse() Q_DECL_OVERRIDE;
    void applyLearning() Q_DECL_OVERRIDE;
    void initializeLearning() Q_DECL_OVERRIDE;

    INeuron *addNeuron(qreal bias);
    QList<INeuron *> &neurons() Q_DECL_OVERRIDE;
    const QList<INeuron *> &neurons() const Q_DECL_OVERRIDE;

private:
    NeuralNet *m_neuralNet;
    QList<INeuron *> m_neurons;
};

#endif // NEURALLAYER_H
