QT += core
QT -= gui widgets

DBLIBS +=

PROJECT_ROOT = ../..

SOURCES += \
    neuron.cpp \
    neurallayer.cpp \
    neuralnet.cpp \
    neuralfactor.cpp \
    debug.cpp

HEADERS += \
    neuralfactor.h \
    neuron.h \
    neurallayer.h \
    neuralnet.h \
    debug.h \
    interfaces/ineuronreceptor.h \
    interfaces/ineuronsignal.h \
    interfaces/ineuron.h \
    interfaces/ineurallayer.h \
    interfaces/ineuralnet.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/lib.pri)
