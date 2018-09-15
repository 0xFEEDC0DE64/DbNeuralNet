#ifndef NEURALNET_H
#define NEURALNET_H

#include <QObject>

#include "interfaces/ineuralnet.h"

template <class T> class QQueue;

class INeuralLayer;

class NeuralNet : public QObject, public INeuralNet
{
    Q_OBJECT
    Q_PROPERTY(qreal learningRate READ learningRate WRITE setLearningRate NOTIFY learningRateChanged)
    Q_PROPERTY(INeuralLayer inputLayer READ inputLayer)
    Q_PROPERTY(INeuralLayer hiddenLayer READ hiddenLayer)
    Q_PROPERTY(INeuralLayer outputLayer READ outputLayer)

public:
    explicit NeuralNet(int inputNeuronCount, int hiddenNeuronCount, int outputNeuronCount, QQueue<qreal> &random, QObject *parent = Q_NULLPTR);

    void trainBackPropagation(const QList<QVector<qreal> > &inputs, const QList<QVector<qreal> > &expexted, int iterations);
    void preparePerceptionLayerForPulse(const QVector<qreal> &input);
    void calculateErrors(const QVector<qreal> &expected);
    void calculateAndAppendTransformation();

    // INeuralNet interface
    void pulse() Q_DECL_OVERRIDE;
    void applyLearning() Q_DECL_OVERRIDE;
    void initializeLearning() Q_DECL_OVERRIDE;

    qreal learningRate() const Q_DECL_OVERRIDE;
    void setLearningRate(qreal learningRate) Q_DECL_OVERRIDE;

    const INeuralLayer *inputLayer() const Q_DECL_OVERRIDE;
    const INeuralLayer *hiddenLayer() const Q_DECL_OVERRIDE;
    const INeuralLayer *outputLayer() const Q_DECL_OVERRIDE;

Q_SIGNALS:
    void learningRateChanged(qreal learningRate);

private:
    static qreal sigmoidDerivative(qreal value);

    qreal m_learningRate;
    INeuralLayer *m_inputLayer;
    INeuralLayer *m_hiddenLayer;
    INeuralLayer *m_outputLayer;
};

#endif // NEURALNET_H
