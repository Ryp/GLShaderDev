set(MOC_HEADERS BuildOutput.h ShaderVisualizationOptions.h ShaderStagesView.h CodeWidget.h GLShaderDev.h OpenGLWidget.h CodeEditor.h QsciLexerGLSL.h Dialog/NewFileDialog.h)
set(GLShaderDev_SRCS ShaderVisualizationOptions.cpp ShaderStagesView.cpp OpenGLWidget.cpp BuildOutput.cpp QsciLexerGLSL.cpp CodeWidget.cpp CodeEditor.cpp GLShaderDev.cpp main.cpp)
set(GLShaderDev_SRCS ${GLShaderDev_SRCS} Shader/ShaderObject.cpp Shader/ShaderProgram.cpp Shader/ShaderManager.cpp)
set(GLShaderDev_SRCS ${GLShaderDev_SRCS} Dialog/NewFileDialog.cpp)
set(GLShaderDev_RCCS resources.qrc)

qt4_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})
qt4_automoc(MOC_SOURCES ${MOC_HEADERS})
qt4_add_resources(GLShaderDev_RCC_SRCS ${GLShaderDev_RCCS})

set("${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -ansi -O" CMAKE_CXX_FLAGS) #FIXME dirty fix

add_executable(GLShaderDev ${GLShaderDev_SRCS} ${GLShaderDev_RCC_SRCS} ${MOC_SOURCES})
target_link_libraries(GLShaderDev ${OPENGL_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${GLEW_LIBRARY} ${QSCINTILLA_LIBRARY})
install(TARGETS GLShaderDev RUNTIME DESTINATION bin)
