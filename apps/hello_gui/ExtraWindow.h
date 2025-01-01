#ifndef EXTRAWINDOW_H
#define EXTRAWINDOW_H

#include <qtmetamacros.h>
#include <QWidget>

class ExtraWindow : public QWidget {
  Q_OBJECT

public:
  explicit ExtraWindow(QWidget *parent = nullptr);
};

#endif
