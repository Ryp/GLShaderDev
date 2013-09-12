#ifndef BUILDOUTPUT_H
#define BUILDOUTPUT_H

#include <qt4/QtGui/QWidget>

class BuildOutput : public QWidget
{
  Q_OBJECT

public:
  BuildOutput(QWidget* parent = 0);
  ~BuildOutput();

};

#endif // BUILDOUTPUT_H
