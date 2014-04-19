project(GLShaderDev)

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(Qt4 REQUIRED)
find_package(QScintilla REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(CXX11 REQUIRED)

set(QTPROPERTYBROWSER_INCLUDE_PATH "ext/QtPropertyBrowser/src")

find_library(QTPROPERTYBROWSER_LIBRARY
    NAMES libQtPropertyBrowser QtPropertyBrowser
    PATHS
    ext/QtPropertyBrowser/bin
    DOC "The libQtPropertyBrowser library"
)

set(QT_MIN_VERSION 4.8.0)
set(QT_USE_QTOPENGL true)

include_directories(${QT_INCLUDES} ${GLEW_INCLUDE_PATH} ${QSCINTILLA_INCLUDE_DIR} ${QTPROPERTYBROWSER_INCLUDE_PATH} include src)

add_subdirectory(src)
