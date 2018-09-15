#include "neuralfactor.h"

#include "debug.h"

NeuralFactor::NeuralFactor(qreal weight, QObject *parent) :
    QObject(parent),
    m_weight(weight),
    m_delta(0.0)
{
    debug(QString("NeuralFactor::NeuralFactor() %0").arg(weight, 0, 'f', 8));
}

void NeuralFactor::applyWeightChange(qreal learningRate)
{
    debug(QString("NeuralFactor::applyWeightChange() %0").arg(learningRate, 0, 'f', 8));

    m_weight += m_delta * learningRate;
}

void NeuralFactor::resetWeightChange()
{
    debug(QString("NeuralFactor::resetWeightChange()"));

    m_delta = 0.0;
}

qreal NeuralFactor::weight() const
{
    return m_weight;
}

void NeuralFactor::setWeight(qreal weight)
{
    debug(QString("NeuralFactor::setWeight() %0").arg(weight, 0, 'f', 8));

    if(m_weight != weight)
        Q_EMIT weightChanged(m_weight = weight);
}

qreal NeuralFactor::delta() const
{
    return m_delta;
}

void NeuralFactor::setDelta(qreal delta)
{
    debug(QString("NeuralFactor::setDelta() %0").arg(delta, 0, 'f', 8));

    if(m_delta != delta)
        Q_EMIT deltaChanged(m_delta = delta);
}
