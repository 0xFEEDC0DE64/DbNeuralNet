#pragma once

#include <qglobal.h>

class INeuronSignal
{
public:
    virtual qreal output() const = 0;
    virtual void setOutput(qreal output) = 0;
};
