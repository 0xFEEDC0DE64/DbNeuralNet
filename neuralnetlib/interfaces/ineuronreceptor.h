#pragma once

template <class Key, class T> class QMap;

class INeuronSignal;
class NeuralFactor;

class INeuronRepetor
{
public:
    virtual QMap<INeuronSignal *, NeuralFactor *> &input() = 0;
    virtual const QMap<INeuronSignal *, NeuralFactor *> &input() const = 0;
};
