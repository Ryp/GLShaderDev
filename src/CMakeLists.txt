set(GLShaderDev_SRCS
  main.cpp
  GLShaderDev.cpp
  Build/BuildOutput.cpp
  Build/OutputDelegate.cpp
  Build/OutputItem.cpp
  Build/OutputModel.cpp
  Build/OutputParser.cpp
  Dialog/GLInfoDialog.cpp
  Dialog/NewFileDialog.cpp
  Editor/CodeEditor.cpp
  Editor/CodeWidget.cpp
  Editor/QsciLexerGLSL.cpp
  GL/GLInfo.cpp
  GL/GLPreviewWidget.cpp
  GL/OpenGLWidget.cpp
  GL/ShaderUtils.cpp
  GL/Shader/ShaderManager.cpp
  GL/Shader/ShaderObject.cpp
  GL/Shader/ShaderProgram.cpp
  Model/Model.cpp
  Model/ModelLoader.cpp
  Preferences/PreferencesWidget.cpp
  Preferences/PreferenceListItemDelegate.cpp
  Preferences/SettingsList.cpp
  Preferences/Panels/APreferencePanel.cpp
  Preferences/Panels/GeneralPanel.cpp
  Preferences/Panels/ShaderExtensionsPanel.cpp
  Preferences/Panels/ExtensionValidator.cpp
  Project/ProjectManager.cpp
  Project/ShaderProject.cpp
  ShaderInputView/ShaderInputView.cpp
  ShaderStagesView/StagesModel.cpp
  ShaderStagesView/ShaderStagesView.cpp
)

set(MOC_HEADERS
  GLShaderDev.h
  Build/BuildOutput.h
  Build/OutputDelegate.h
  Build/OutputModel.h
  Dialog/NewFileDialog.h
  Dialog/GLInfoDialog.h
  Editor/CodeEditor.h
  Editor/CodeWidget.h
  Editor/QsciLexerGLSL.h
  GL/GLPreviewWidget.h
  GL/OpenGLWidget.h
  Preferences/PreferencesWidget.h
  Preferences/PreferenceListItemDelegate.h
  Preferences/Panels/APreferencePanel.h
  Preferences/Panels/GeneralPanel.h
  Preferences/Panels/ShaderExtensionsPanel.h
  Preferences/Panels/ExtensionValidator.h
  ShaderInputView/ShaderInputView.h
  ShaderStagesView/StagesModel.h
  ShaderStagesView/ShaderStagesView.h
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