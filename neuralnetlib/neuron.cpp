#include "neuron.h"

#include <qmath.h>

#include "neurallayer.h"
#include "neuralfactor.h"
#include "debug.h"

Neuron::Neuron(qreal bias, NeuralLayer *neuralLayer) :
    QObject(neuralLayer),
    INeuron(),
    m_neuralLayer(neuralLayer),
    m_input(),
    m_error(0.0),
    m_bias(new NeuralFactor(bias, this))
{
    debug(QString("Neuron::Neuron() %0").arg(bias, 0, 'f', 8));
}

QMap<INeuronSignal *, NeuralFactor *> &Neuron::input()
{
    return m_input;
}

const QMap<INeuronSignal *, NeuralFactor *> &Neuron::input() const
{
    return m_input;
}

qreal Neuron::output() const
{
    return m_output;
}

void Neuron::setOutput(qreal output)
{
    debug(QString("Neuron::setOutput() %0").arg(output, 0, 'f', 8));

    if(m_output != output)
        Q_EMIT outputChanged(m_output = output);
}

void Neuron::pulse()
{
    debug(QString("Neuron::pulse()"));

    m_output = 0.0;

    for(auto iter = m_input.constBegin(); iter != m_input.constEnd(); iter++)
        m_output += iter.key()->output() * iter.value()->weight();

    m_output += m_bias->weight();
    m_output = sigmoid(m_output);
}

void Neuron::applyLearning(qreal learningRate)
{
    debug(QString("Neuron::applyLearning() %0").arg(learningRate, 0, 'f', 8));

    for(auto factor : m_input.values())
        factor->applyWeightChange(learningRate);

    m_bias->applyWeightChange(learningRate);
}

void Neuron::initializeLearning()
{
    debug(QString("Neuron::initializeLearning()"));

    for(auto factor : m_input.values())
        factor->resetWeightChange();

    m_bias->resetWeightChange();
}

qreal Neuron::error() const
{
    return m_error;
}

void Neuron::setError(qreal error)
{
    debug(QString("Neuron::setError() %0").arg(error, 0, 'f', 8));

    if(m_error != error)
        Q_EMIT errorChanged(m_error = error);
}

NeuralFactor *Neuron::bias()
{
    return m_bias;
}

const NeuralFactor *Neuron::bias() const
{
    return m_bias;
}

qreal Neuron::sigmoid(qreal value)
{
    auto result = 1.0 / (1.0 + qExp(-value));

    debug(QString("Neuron::sigmoid() %0 %1").arg(value, 0, 'f', 8).arg(result, 0, 'f', 8));

    return result;
}
