#include <QtGui/QHBoxLayout>
#include <QtGui/QTreeWidget>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QHeaderView>

#include "BuildOutput.h"

BuildOutput::BuildOutput(QWidget* parent)
: QWidget(parent)
{
  _layout = new QHBoxLayout(this);
  _layout->setSpacing(0); // FIXME
  _layout->setMargin(0);

  QTreeWidget* list = new QTreeWidget(this);
  list->header()->hide();
  list->setRootIsDecorated(false);
  QFont ft = this->font();
  ft.setFamily("Monospace");
  list->setFont(ft);

  QStringList l;
  l.append("Pute");
  l.append("Negre");
//   QTreeWidgetItem* a = new QTreeWidgetItem(list, l);
//   QTreeWidgetItem* b = new QTreeWidgetItem(list, l);
  _layout->addWidget(list);

  //   connect(list, itemDoubleClicked(QTreeWidgetItem*, int), this, onLineSensitiveItem(int, int));
}

BuildOutput::~BuildOutput() {}

#include "BuildOutput.moc"
