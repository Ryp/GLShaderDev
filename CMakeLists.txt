project(GLShaderDev)

cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(Qt4 REQUIRED)
find_package(QScintilla REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${QT_INCLUDES} ${QSCINTILLA_INCLUDE_DIR})

set(QT_MIN_VERSION 4.8.0)
set(QT_USE_QTOPENGL true)

add_subdirectory(src)
