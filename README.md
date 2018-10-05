# DbNeuralNet
Small library to define and execute a neural net with back propagation. The example applications tries to learn XOR operations.

# Building from source
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
./bin/databasetree
```
