#include "ui_mainwindow.h"

#include <QMainWindow>

class MainWindowForm : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindowForm(QMainWindow *parent = nullptr);

private slots:
  void on_actionNew_triggered();
  void on_actionOpen_triggered();
  void on_actionSave_triggered();
  void on_actionClose_triggered();
  void on_actionQuit_triggered();
  void on_actionUndo_triggered();
  void on_actionRedo_triggered();
  void on_actionCut_triggered();
  void on_actionCopy_triggered();
  void on_actionPaste_triggered();
  void on_actionDelete_triggered();
  void on_actionSelect_All_triggered();
  void on_actionCheckbox_triggered();
  void on_actionAbout_triggered();

private:
  Ui::MainWindow ui;
  void setupStandardFileMenu();
  void setupStandardEditMenu();
  void setupStandardHelpMenu();
};
