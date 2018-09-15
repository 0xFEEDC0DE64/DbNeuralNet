#ifndef NEURON_H
#define NEURON_H

#include <QObject>
#include <QMap>
#include <qglobal.h>

#include "interfaces/ineuron.h"

class NeuralLayer;
class INeuronSignal;
class NeuralFactor;

class Neuron : public QObject, public INeuron
{
    Q_OBJECT
    Q_PROPERTY(QMap<INeuronSignal*,NeuralFactor*> input READ input)
    Q_PROPERTY(qreal output READ output WRITE setOutput NOTIFY outputChanged)
    Q_PROPERTY(qreal error READ error WRITE setError NOTIFY errorChanged)
    Q_PROPERTY(NeuralFactor* bias READ bias)

public:
    explicit Neuron(qreal bias, NeuralLayer *neuralLayer);

    // INeuronRepetor interface
    QMap<INeuronSignal *, NeuralFactor *> &input() Q_DECL_OVERRIDE;
    const QMap<INeuronSignal *, NeuralFactor *> &input() const Q_DECL_OVERRIDE;

    // INeuronSignal interface
    qreal output() const Q_DECL_OVERRIDE;
    void setOutput(qreal output) Q_DECL_OVERRIDE;

    // INeuron interface
    void pulse() Q_DECL_OVERRIDE;
    void applyLearning(qreal learningRate) Q_DECL_OVERRIDE;
    void initializeLearning() Q_DECL_OVERRIDE;

    qreal error() const Q_DECL_OVERRIDE;
    void setError(qreal error) Q_DECL_OVERRIDE;

    NeuralFactor *bias() Q_DECL_OVERRIDE;
    const NeuralFactor *bias() const Q_DECL_OVERRIDE;

Q_SIGNALS:
    void outputChanged(qreal output);
    void errorChanged(qreal error);
    void lastErrorChanged(qreal lastError);

private:
    static inline qreal sigmoid(qreal value);

    NeuralLayer *m_neuralLayer;
    QMap<INeuronSignal *, NeuralFactor *> m_input;
    qreal m_output;
    qreal m_error;
    NeuralFactor *m_bias;
};

#endif // NEURON_H
