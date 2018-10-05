# DbNeuralNet
Small library to define and execute a neural net with back propagation. The example applications tries to learn XOR operations.

[![Build Status](https://travis-ci.org/0xFEEDC0DE64/DbNeuralNet.svg?branch=master)](https://travis-ci.org/0xFEEDC0DE64/DbNeuralNet) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/b3a543e59b1a46cfb24697fdddc2b7ac)](https://www.codacy.com/app/0xFEEDC0DE64/DbNeuralNet?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=0xFEEDC0DE64/DbNeuralNet&amp;utm_campaign=Badge_Grade)

## Building from source
This project can only be built as part of the project structure [DbSoftware](https://github.com/0xFEEDC0DE64/DbSoftware)

```Shell
git clone https://github.com/0xFEEDC0DE64/DbSoftware.git
cd DbSoftware
git submodule update --init --recursive DbNeuralNet
cd ..
mkdir build_DbSoftware
cd build_DbSoftware
qmake CONFIG+=ccache ../DbSoftware
make -j$(nproc) sub-DbNeuralNet
make sub-DbNeuralNet-install_subtargets
./bin/neuralnetdemo
```
