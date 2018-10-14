set(HEADERS
    debug.h
    neuralfactor.h
    neurallayer.h
    neuralnet.h
    neuron.h
    interfaces/ineurallayer.h
    interfaces/ineuralnet.h
    interfaces/ineuron.h
    interfaces/ineuronreceptor.h
    interfaces/ineuronsignal.h
)

set(SOURCES
    debug.cpp
    neuralfactor.cpp
    neurallayer.cpp
    neuralnet.cpp
    neuron.cpp
)

add_library(neuralnetlib SHARED ${HEADERS} ${SOURCES})

target_compile_definitions(neuralnetlib PRIVATE NEURALNETLIB_LIBRARY)

target_link_libraries(neuralnetlib Qt5::Core)

target_include_directories(neuralnetlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(neuralnet neuralnetlib)
