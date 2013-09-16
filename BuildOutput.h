#ifndef BUILDOUTPUT_H
#define BUILDOUTPUT_H

#include <qt4/QtGui/QWidget>

class QHBoxLayout;

class BuildOutput : public QWidget
{
  Q_OBJECT

public:
  BuildOutput(QWidget* parent = 0);
  ~BuildOutput();

signals:
  void	onLineSensitiveItem(int line, int type);

private:
  QHBoxLayout*	_layout;
};

#endif // BUILDOUTPUT_H
