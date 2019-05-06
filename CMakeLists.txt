cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fdiagnostics-color")

project(pwcalculator LANGUAGES CXX)

find_package(Qt5 COMPONENTS QuickControls2 REQUIRED)
qt5_add_resources(RESOURCES resources/qml.qrc)

file(GLOB SRC src/*.cpp)
add_executable(pwcalculator ${SRC} ${RESOURCES})

target_link_libraries(pwcalculator PRIVATE Qt5::QuickControls2)
