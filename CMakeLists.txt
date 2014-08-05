cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(GLShaderDev C CXX)

# Avoid source tree pollution
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(WARNING "In-source builds are not encouraged. Make a separate folder for building:\nmkdir build; cd build; cmake ..;cd ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(Qt4 REQUIRED)

add_subdirectory(ext)
set(QTPROPERTYBROWSER_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/ext/QtPropertyBrowser)
set(QTPROPERTYBROWSER_LIBRARY QtPropertyBrowser)

find_package(QScintilla REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(CXX11 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS}")

set(QT_MIN_VERSION 4.8.2)
set(QT_USE_QTOPENGL true)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GLShaderDev_BINARY_DIR})

add_subdirectory(src)
