find_package(Qt5Core CONFIG REQUIRED)

set(HEADERS
)

set(SOURCES
    main.cpp
)

add_executable(neuralnetdemo ${HEADERS} ${SOURCES})

target_link_libraries(neuralnetdemo Qt5::Core neuralnetlib)

add_dependencies(neuralnet neuralnetdemo)
