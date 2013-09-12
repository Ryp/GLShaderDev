#include <QtGui/QApplication>
#include "GLShaderDev.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  GLShaderDev ide;
  ide.show();
  return (app.exec());
}
