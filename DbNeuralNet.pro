QT += core
QT -= gui widgets

DBLIBS +=

TARGET = neuralnet

PROJECT_ROOT = ..

SOURCES += main.cpp \
    neuron.cpp \
    neurallayer.cpp \
    neuralnet.cpp \
    neuralfactor.cpp \
    debug.cpp

HEADERS += \
    neuralfactor.h \
    interfaces/ineuronreceptor.h \
    interfaces/ineuronsignal.h \
    interfaces/ineuron.h \
    interfaces/ineurallayer.h \
    interfaces/ineuralnet.h \
    neuron.h \
    neurallayer.h \
    neuralnet.h \
    debug.h

FORMS +=

RESOURCES +=

TRANSLATIONS +=

include($${PROJECT_ROOT}/app.pri)
