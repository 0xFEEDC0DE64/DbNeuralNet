TEMPLATE = subdirs

SUBDIRS += neuralnetdemo \
           neuralnetlib

neuralnetdemo.depends += neuralnetlib
