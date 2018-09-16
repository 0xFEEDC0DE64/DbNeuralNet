#include <QCoreApplication>
#include <QQueue>
#include <QList>
#include <QVector>
#include <QDebug>

#include "debug.h"
#include "neuralnet.h"
#include "interfaces/ineurallayer.h"
#include "interfaces/ineuron.h"

const qreal low = .01;
const qreal mid = .5;
const qreal high = .99;
const int iterations = 5;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(!initDebug())
        return -1;

    QQueue<qreal> random;
    random.enqueue(0.248668584157093);
    random.enqueue(0.110743977181029);
    random.enqueue(0.467010679872246);
    random.enqueue(0.771604122021982);
    random.enqueue(0.657518893786482);
    random.enqueue(0.432782601300991);
    random.enqueue(0.354083763600366);
    random.enqueue(0.943862276125635);
    random.enqueue(0.101266453555444);

    NeuralNet net(2, 2, 1, random);

    QList<QVector<qreal> > input {
        QVector<qreal> { high, high },
        QVector<qreal> { low, high },
        QVector<qreal> { high, low },
        QVector<qreal> { low, low }
    };

    QList<QVector<qreal> > output {
        QVector<qreal> { low },
        QVector<qreal> { high },
        QVector<qreal> { high },
        QVector<qreal> { low }
    };

    int count = 0;
    qreal hh, lh, hl, ll;
    do
    {
        net.setLearningRate(3);
        net.trainBackPropagation(input, output, iterations);

        net.inputLayer()->neurons().at(0)->setOutput(high);
        net.inputLayer()->neurons().at(1)->setOutput(high);
        net.pulse();
        hh = net.outputLayer()->neurons().at(0)->output();

        net.inputLayer()->neurons().at(0)->setOutput(low);
        net.inputLayer()->neurons().at(1)->setOutput(high);
        net.pulse();
        lh = net.outputLayer()->neurons().at(0)->output();

        net.inputLayer()->neurons().at(0)->setOutput(high);
        net.inputLayer()->neurons().at(1)->setOutput(low);
        net.pulse();
        hl = net.outputLayer()->neurons().at(0)->output();

        net.inputLayer()->neurons().at(0)->setOutput(low);
        net.inputLayer()->neurons().at(1)->setOutput(low);
        net.pulse();
        ll = net.outputLayer()->neurons().at(0)->output();

        debug(QString("round %0: hh=%1 lh=%2 hl=%3 ll=%4").arg(count++).arg(hh, 0, 'f', 8).arg(lh, 0, 'f', 8).arg(hl, 0, 'f', 8).arg(ll, 0, 'f', 8));
    }
    while(hh > (mid + low) / 2.0 ||
          lh < (mid + high) / 2.0 ||
          hl < (mid + low) / 2.0 ||
          ll > (mid + high) / 2);

    qDebug() << count * iterations << "iterations";
    qDebug() << "hh" << hh;
    qDebug() << "lh" << lh;
    qDebug() << "hl" << hl;
    qDebug() << "ll" << ll;

    return 0;
}
