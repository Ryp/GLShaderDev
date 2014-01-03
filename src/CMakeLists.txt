set(GLShaderDev_SRCS
  main.cpp
  GLShaderDev.cpp
  OpenGLWidget.cpp
  ShaderStagesView.cpp
  ShaderVisualizationOptions.cpp
  Build/BuildOutput.cpp
  Build/OutputParser.cpp
  Dialog/GLInfoDialog.cpp
  Dialog/NewFileDialog.cpp
  Editor/CodeEditor.cpp
  Editor/CodeWidget.cpp
  Editor/QsciLexerGLSL.cpp
  Model/Model.cpp
  Model/ModelLoader.cpp
  Shader/ShaderManager.cpp
  Shader/ShaderObject.cpp
  Shader/ShaderProgram.cpp
)

set(MOC_HEADERS
  ShaderVisualizationOptions.h
  ShaderStagesView.h
  GLShaderDev.h
  OpenGLWidget.h
  Editor/CodeEditor.h
  Editor/CodeWidget.h
  Editor/QsciLexerGLSL.h
  Build/BuildOutput.h
  Dialog/NewFileDialog.h
  Dialog/GLInfoDialog.h
)

set(GLShaderDev_RCCS
  resources.qrc
)

qt4_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})
qt4_automoc(MOC_SOURCES ${MOC_HEADERS})
qt4_add_resources(GLShaderDev_RCC_SRCS ${GLShaderDev_RCCS})

set(CMAKE_CXX_FLAGS "-Wall -Wextra -ansi -O ${CXX11_FLAGS} ${CMAKE_CXX_FLAGS}")

add_executable(GLShaderDev ${GLShaderDev_SRCS} ${GLShaderDev_RCC_SRCS} ${MOC_SOURCES})
target_link_libraries(GLShaderDev ${OPENGL_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${GLEW_LIBRARY} ${QSCINTILLA_LIBRARY})
install(TARGETS GLShaderDev RUNTIME DESTINATION bin)