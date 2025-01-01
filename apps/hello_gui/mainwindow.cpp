#include "mainwindow.h"
#include "ExtraWindow.h"
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QtCore/qobjectdefs.h>

void MainWindowForm::showAboutDialog() {
  QMessageBox::about(
      this, tr("About Hello GUI"),
      tr("<h2>Hello GUI 0.1</h2>"
         "<p>Copyright &copy; 2024 Jaeden Amero</p>"
         "<p>Hello GUI is a sample program to demonstrate "
         "Qt features.</p>"
         "<p>For more information, visit "
         "<a href='http://www.patater.com'>www.patater.com</a></p>"));
}

MainWindowForm::MainWindowForm(QMainWindow *parent)
    : QMainWindow(parent), m_ExtraWindow(nullptr) {
  ui.setupUi(this);
}

void MainWindowForm::on_actionNew_triggered() {}

void MainWindowForm::on_actionOpen_triggered() {}

void MainWindowForm::on_actionSave_triggered() {}

void MainWindowForm::on_actionClose_triggered() {}

void MainWindowForm::on_actionQuit_triggered() { QApplication::quit(); }

void MainWindowForm::on_actionUndo_triggered() {}

void MainWindowForm::on_actionRedo_triggered() {}

void MainWindowForm::on_actionCut_triggered() {
  if (QWidget *w = QApplication::focusWidget()) {
    QMetaObject::invokeMethod(w, "cut");
  }
}

void MainWindowForm::on_actionCopy_triggered() {
  if (QWidget *w = QApplication::focusWidget()) {
    QMetaObject::invokeMethod(w, "copy");
  }
}

void MainWindowForm::on_actionPaste_triggered() {
  if (QWidget *w = QApplication::focusWidget()) {
    QMetaObject::invokeMethod(w, "paste");
  }
}

void MainWindowForm::on_actionDelete_triggered() {
  if (QWidget *w = QApplication::focusWidget()) {
    QMetaObject::invokeMethod(w, "delete");
  }
}

void MainWindowForm::on_actionSelect_All_triggered() {
  if (QWidget *w = QApplication::focusWidget()) {
    QMetaObject::invokeMethod(w, "selectAll");
  }
}

void MainWindowForm::on_actionCheckbox_triggered() {}

void MainWindowForm::on_actionToolsShow_triggered() {
  if (!m_ExtraWindow) {
    m_ExtraWindow = new ExtraWindow(this);

    // Connect window's destroyed signal to null our pointer
    connect(m_ExtraWindow, &QWidget::destroyed,
            [this]() { m_ExtraWindow = nullptr; });
  }

  m_ExtraWindow->show();
  m_ExtraWindow->activateWindow();
}

void MainWindowForm::on_actionAbout_triggered() { showAboutDialog(); }
