#ifndef BUILDOUTPUT_H
#define BUILDOUTPUT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
QT_END_NAMESPACE

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
