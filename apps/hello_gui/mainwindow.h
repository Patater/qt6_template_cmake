#include "ui_mainwindow.h"

#include <QMainWindow>

class MainWindowForm : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindowForm(QMainWindow *parent = nullptr);

private:
  Ui::MainWindow ui;
};
