project(GLShaderDev)

cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(Qt4 REQUIRED)
find_package(QScintilla REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${QSCINTILLA_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})

set(QT_MIN_VERSION 4.2.0)
set(QT_USE_QTOPENGL true)
set(GLShaderDev_SRCS OpenGLWidget.cpp BuildOutput.cpp ShaderLexer.cpp CodeWidget.cpp CodeEditor.cpp GLShaderDev.cpp main.cpp)

qt4_automoc(${GLShaderDev_SRCS})
add_executable(GLShaderDev ${GLShaderDev_SRCS})
target_link_libraries(GLShaderDev ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${OPENGL_LIBRARIES} ${QSCINTILLA_LIBRARY})
install(TARGETS GLShaderDev RUNTIME DESTINATION bin)
