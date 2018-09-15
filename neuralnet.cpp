#include "neuralnet.h"

#include <QQueue>
#include <QList>
#include <QVector>

#include "neurallayer.h"
#include "debug.h"
#include "neuron.h"
#include "neuralfactor.h"

NeuralNet::NeuralNet(int inputNeuronCount, int hiddenNeuronCount, int outputNeuronCount, QQueue<qreal> &random, QObject *parent) :
    QObject(parent),
    INeuralNet(),
    m_learningRate(0.5),
    m_inputLayer(new NeuralLayer(this)),
    m_hiddenLayer(new NeuralLayer(this)),
    m_outputLayer(new NeuralLayer(this))
{
    debug(QString("NeuralNet::NeuralNet() %0 %1 %2").arg(inputNeuronCount).arg(hiddenNeuronCount).arg(outputNeuronCount));

    Q_ASSERT(random.count() == hiddenNeuronCount + outputNeuronCount + (hiddenNeuronCount * inputNeuronCount) + (outputNeuronCount * hiddenNeuronCount));

    for (int i = 0; i < inputNeuronCount; i++)
        m_inputLayer->addNeuron(0);

    for (int i = 0; i < outputNeuronCount; i++)
        m_outputLayer->addNeuron(random.dequeue());

    for (int i = 0; i < hiddenNeuronCount; i++)
        m_hiddenLayer->addNeuron(random.dequeue());

    for(auto hiddenNeuron : m_hiddenLayer->neurons())
        for(auto inputNeuron : m_inputLayer->neurons())
            hiddenNeuron->input().insert(inputNeuron, new NeuralFactor(random.dequeue()));

    for(auto outputNeuron : m_outputLayer->neurons())
        for(auto hiddenNeuron : m_hiddenLayer->neurons())
            outputNeuron->input().insert(hiddenNeuron, new NeuralFactor(random.dequeue()));
}

void NeuralNet::trainBackPropagation(const QList<QVector<qreal> > &inputs, const QList<QVector<qreal> > &expexted, int iterations)
{
    {
        QString line = "NeuralNet::trainBackPropagation()";
        for(auto vector : inputs)
            for(auto val : vector)
                line.append(QString(" %0").arg(val, 0, 'f', 8));
        for(auto vector : expexted)
            for(auto val : vector)
                line.append(QString(" %0").arg(val, 0, 'f', 8));
        line.append(QString(" %0").arg(iterations));
        debug(line);
    }

    for(int i = 0; i < iterations; i++)
    {
        debug(QString("NeuralNet::trainBackPropagation() %0").arg(i));

        // set all weight changes to zero
        initializeLearning();

        for(int j = 0; j < inputs.size(); j++)
        {
            preparePerceptionLayerForPulse(inputs.at(j));
            pulse();
            calculateErrors(expexted.at(j));
            calculateAndAppendTransformation();
        }

        applyLearning();
    }
}

void NeuralNet::preparePerceptionLayerForPulse(const QVector<qreal> &input)
{
    {
        QString line = "NeuralNet::preparePerceptionLayerForPulse()";
        Q_FOREACH(auto val, input)
            line.append(QString(" %0").arg(val, 0, 'f', 8));
        debug(line);
    }

    Q_ASSERT(input.size() == m_inputLayer->neurons().size());

    for(int i = 0; i < input.size(); i++)
    {
        debug(QString("NeuralNet::preparePerceptionLayerForPulse() loop %0").arg(i));
        m_inputLayer->neurons().at(i)->setOutput(input.at(i));
    }
}

void NeuralNet::calculateErrors(const QVector<qreal> &expected)
{
    {
        QString line = "NeuralNet::calculateErrors()";
        Q_FOREACH(auto val, expected)
            line.append(QString(" %0").arg(val, 0, 'f', 8));
        debug(line);
    }

    Q_ASSERT(expected.size() == m_outputLayer->neurons().count());

    // Calcualte output error values
    for(int i = 0; i < expected.size(); i++)
    {
        debug(QString("NeuralNet::calculateErrors() loop %0").arg(i));

        auto outputNode = m_outputLayer->neurons().at(i);
        auto temp = outputNode->output();

        outputNode->setError((expected.at(i) - temp) * sigmoidDerivative(temp));
    }

    // calculate hidden layer error values
    for(auto hiddenNode : m_hiddenLayer->neurons())
    {
        auto temp = hiddenNode->output();

        qreal error = 0.0;
        for(auto outputNode : m_outputLayer->neurons())
            error += (outputNode->error() * outputNode->input().value(hiddenNode)->weight()) * sigmoidDerivative(temp);

        hiddenNode->setError(error);
    }
}

void NeuralNet::calculateAndAppendTransformation()
{
    debug(QString("NeuralNet::calculateAndAppendTransformation()"));

    // adjust output layer weight change
    for(auto outputNode : m_outputLayer->neurons())
    {
        for(auto hiddenNode : m_hiddenLayer->neurons())
        {
            auto factor = outputNode->input().value(hiddenNode);
            factor->setDelta(factor->delta() + (outputNode->error() * hiddenNode->output()));
        }

        outputNode->bias()->setDelta(outputNode->bias()->delta() + (outputNode->error() * outputNode->bias()->weight()));
    }

    for(auto hiddenNode : m_hiddenLayer->neurons())
    {
        for(auto inputNode : m_inputLayer->neurons())
        {
            auto factor = hiddenNode->input().value(inputNode);
            factor->setDelta(factor->delta() + (hiddenNode->error() * inputNode->output()));
        }

        hiddenNode->bias()->setDelta(hiddenNode->bias()->delta() + (hiddenNode->error() * hiddenNode->bias()->weight()));
    }
}

void NeuralNet::pulse()
{
    debug("NeuralNet::pulse()");

    m_hiddenLayer->pulse();
    m_outputLayer->pulse();
}

void NeuralNet::applyLearning()
{
    debug("NeuralNet::applyLearning()");

    m_hiddenLayer->applyLearning();
    m_outputLayer->applyLearning();
}

void NeuralNet::initializeLearning()
{
    debug("NeuralNet::initializeLearning()");

    m_hiddenLayer->initializeLearning();
    m_outputLayer->initializeLearning();
}

qreal NeuralNet::learningRate() const
{
    return m_learningRate;
}

void NeuralNet::setLearningRate(qreal learningRate)
{
    debug(QString("NeuralNet::setLearningRate() %0").arg(learningRate, 0, 'f', 8));

    if(m_learningRate != learningRate)
        Q_EMIT learningRateChanged(m_learningRate = learningRate);
}

const INeuralLayer *NeuralNet::inputLayer() const
{
    return m_inputLayer;
}

const INeuralLayer *NeuralNet::hiddenLayer() const
{
    return m_hiddenLayer;
}

const INeuralLayer *NeuralNet::outputLayer() const
{
    return m_outputLayer;
}

qreal NeuralNet::sigmoidDerivative(qreal value)
{
    auto result = value * (1.0 - value);

    debug(QString("NeuralNet::sigmoidDerivative() %0 %1").arg(value, 0, 'f', 8).arg(result, 0, 'f', 8));

    return result;
}
