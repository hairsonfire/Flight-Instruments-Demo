cmake_minimum_required(VERSION 3.21)

project(FlightDisplay VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

qt_standard_project_setup()

add_executable(FlightDisplay
    src/main.cpp
    src/app/MainWindow.cpp
    src/app/MainWindow.h
    src/model/FlightModel.cpp
    src/model/FlightModel.h
    src/view/FlightDisplayWidget.cpp src/view/FlightDisplayWidget.h
    src/view/ArtificialHorizonWidget.cpp src/view/ArtificialHorizonWidget.h
    src/flightsimulator/FlightSimulator.cpp src/flightsimulator/FlightSimulator.h
    src/view/AltimeterWidget.h src/view/AltimeterWidget.cpp
    src/flightsimulator/FlightSimulator.h
)

target_link_libraries(FlightDisplay PRIVATE Qt6::Widgets Qt6::OpenGLWidgets)