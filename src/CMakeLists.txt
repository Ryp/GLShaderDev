set(MOC_HEADERS BuildOutput.h CodeWidget.h GLShaderDev.h OpenGLWidget.h CodeEditor.h QsciLexerGLSL.h)
set(GLShaderDev_SRCS OpenGLWidget.cpp BuildOutput.cpp QsciLexerGLSL.cpp CodeWidget.cpp CodeEditor.cpp GLShaderDev.cpp main.cpp)
set(GLShaderDev_SRCS ${GLShaderDev_SRCS} Shader/ShaderObject.cpp Shader/ShaderProgram.cpp Shader/ShaderManager.cpp)
set(GLShaderDev_RCCS resources.qrc)

qt4_automoc(MOC_SOURCES ${MOC_HEADERS})
qt4_add_resources(GLShaderDev_RCC_SRCS ${GLShaderDev_RCCS})
qt4_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ansi")

add_executable(GLShaderDev ${GLShaderDev_SRCS} ${GLShaderDev_RCC_SRCS} ${MOC_SOURCES})
target_link_libraries(GLShaderDev ${OPENGL_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${GLEW_LIBRARY} ${QSCINTILLA_LIBRARY})
install(TARGETS GLShaderDev RUNTIME DESTINATION bin)
