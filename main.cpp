#include <QtGui/QApplication>

#include "GLShaderDev.h"

int main(int argc, char** argv)
{
  QCoreApplication::setApplicationName("GLShaderDev");
  QCoreApplication::setApplicationVersion("1.0.0");
  QCoreApplication::setOrganizationDomain("epitech.eu");
  QCoreApplication::setOrganizationName("Epitech");
  QApplication app(argc, argv);
  GLShaderDev ide;
  ide.show();
  return (app.exec());
}
