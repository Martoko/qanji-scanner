cmake_minimum_required(VERSION 3.17)
project(qanji_scanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCES main.cpp scanner.cpp scanner.h)

if (WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
else ()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} ${OpenCV_LIBS})
