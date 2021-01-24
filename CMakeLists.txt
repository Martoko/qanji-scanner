cmake_minimum_required(VERSION 3.17)
project(qanji_scanner)

set(CMAKE_CXX_STANDARD 17) # libtorch does not work with c++ > 17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(OpenCV COMPONENTS core imgproc REQUIRED)
find_package(Torch REQUIRED)

set(SOURCES main.cpp scanner.cpp scanner.h model.cpp model.h kanji.h)

if (WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
else ()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE torch opencv_core opencv_imgproc Qt6::Core Qt6::Gui Qt6::Widgets)
