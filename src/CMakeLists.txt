set(GLShaderDev_SRCS OpenGLWidget.cpp BuildOutput.cpp ShaderLexer.cpp CodeWidget.cpp CodeEditor.cpp GLShaderDev.cpp main.cpp)
set(GLShaderDev_RCCS resources.qrc)

qt4_automoc(${GLShaderDev_SRCS})
qt4_add_resources(GLShaderDev_RCC_SRCS ${GLShaderDev_RCCS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ansi")

add_executable(GLShaderDev ${GLShaderDev_SRCS} ${GLShaderDev_RCC_SRCS})
target_link_libraries(GLShaderDev ${OPENGL_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${QSCINTILLA_LIBRARY})
install(TARGETS GLShaderDev RUNTIME DESTINATION bin)
