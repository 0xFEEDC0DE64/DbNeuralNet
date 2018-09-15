#ifndef INEURONSIGNAL_H
#define INEURONSIGNAL_H

#include <qglobal.h>

class INeuronSignal
{
public:
    virtual qreal output() const = 0;
    virtual void setOutput(qreal output) = 0;
};

#endif // INEURONSIGNAL_H
