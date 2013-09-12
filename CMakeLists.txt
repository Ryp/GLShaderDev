project(GLShaderDev)

cmake_minimum_required(VERSION 2.8)

list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(Qt4 REQUIRED)
find_package(QScintilla REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${QSCINTILLA_INCLUDE_DIR})

set(GLShaderDev_SRCS BuildOutput.cpp ShaderLexer.cpp CodeWidget.cpp CodeEditor.cpp GLShaderDev.cpp main.cpp)
qt4_automoc(${GLShaderDev_SRCS})
add_executable(GLShaderDev ${GLShaderDev_SRCS})
target_link_libraries(GLShaderDev ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QSCINTILLA_LIBRARY})
install(TARGETS GLShaderDev RUNTIME DESTINATION bin)
