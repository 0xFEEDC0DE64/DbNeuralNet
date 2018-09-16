#include "neurallayer.h"

#include "neuralnet.h"
#include "debug.h"
#include "neuron.h"

NeuralLayer::NeuralLayer(NeuralNet *neuralNet) :
    QObject(neuralNet),
    INeuralLayer(),
    m_neuralNet(neuralNet),
    m_neurons()
{
    debug(QString("NeuralLayer::NeuralLayer()"));
}

void NeuralLayer::pulse()
{
    debug(QString("NeuralLayer::pulse()"));

    for(auto neuron : m_neurons)
        neuron->pulse();
}

void NeuralLayer::applyLearning()
{
    debug(QString("NeuralLayer::applyLearning()"));

    qreal learningRate = m_neuralNet->learningRate();

    debug(QString("NeuralLayer::applyLearning() learningRate = %0").arg(learningRate, 0, 'f', 8));

    for(auto neuron : m_neurons)
        neuron->applyLearning(learningRate);
}

void NeuralLayer::initializeLearning()
{
    debug(QString("NeuralLayer::initializeLearning()"));

    for(auto neuron : m_neurons)
        neuron->initializeLearning();
}

INeuron *NeuralLayer::addNeuron(qreal bias)
{
    debug(QString("NeuralLayer::addNeuron() %0").arg(bias, 0, 'f', 8));

    auto neuron = new Neuron(bias, this);
    m_neurons << neuron;
    return neuron;
}

QList<INeuron *> &NeuralLayer::neurons()
{
    return m_neurons;
}

const QList<INeuron *> &NeuralLayer::neurons() const
{
    return m_neurons;
}
