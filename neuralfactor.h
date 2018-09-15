#ifndef NEURALFACTOR_H
#define NEURALFACTOR_H

#include <QObject>
#include <qglobal.h>

class Neuron;

class NeuralFactor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal weight READ weight WRITE setWeight NOTIFY weightChanged)
    Q_PROPERTY(qreal delta READ delta WRITE setDelta NOTIFY deltaChanged)

public:
    explicit NeuralFactor(qreal weight, QObject *parent = Q_NULLPTR);

    void applyWeightChange(qreal learningRate);
    void resetWeightChange();

    qreal weight() const;
    void setWeight(qreal weight);

    qreal delta() const;
    void setDelta(qreal delta);

Q_SIGNALS:
    void weightChanged(qreal weight);
    void deltaChanged(qreal delta);

private:
    qreal m_weight;
    qreal m_delta;
};

#endif // NEURALFACTOR_H
