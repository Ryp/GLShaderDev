#include <QtGui/QApplication>
#include <QtCore/QResource>

#include "GLShaderDev.h"

int main(int argc, char** argv)
{
  QCoreApplication::setApplicationName("GLShaderDev");
  QCoreApplication::setApplicationVersion("0.0.1");
  QCoreApplication::setOrganizationName("Epitech");
  QResource::registerResource("icons.qrc");
  QApplication app(argc, argv);
  GLShaderDev ide;
  ide.show();
  return (app.exec());
}
