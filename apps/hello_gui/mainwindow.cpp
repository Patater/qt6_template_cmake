#include "mainwindow.h"
#include <QAction>
#include <QApplication>
#include <QIcon>
#include <QKeySequence>
#include <QMetaObject>
#include <QWidget>
#include <QMessageBox>

void MainWindowForm::setupStandardFileMenu() {
  QAction *action;

  action = ui.actionNew;
  if (action) {
    action->setText(tr("&New"));
    action->setIcon(QIcon::fromTheme("document-new"));
    action->setShortcuts(QKeySequence::New);
    action->setStatusTip(tr("Create a new file"));
  }

  action = ui.actionOpen;
  if (action) {
    action->setText(tr("&Open..."));
    action->setIcon(QIcon::fromTheme("document-open"));
    action->setShortcuts(QKeySequence::Open);
    action->setStatusTip(tr("Open an existing file"));
  }

  action = ui.actionSave;
  if (action) {
    action->setText(tr("&Save"));
    action->setIcon(QIcon::fromTheme("document-save"));
    action->setShortcuts(QKeySequence::Save);
    action->setStatusTip(tr("Save the document to disk"));
  }

  action = ui.actionClose;
  if (action) {
    action->setText(tr("&Close"));
    action->setIcon(QIcon::fromTheme("document-close"));
    action->setShortcuts(QKeySequence::Close);
    action->setStatusTip(tr("Close the current document"));
  }

  action = ui.actionQuit;
  if (action) {
    action->setText(tr("&Quit"));
    action->setIcon(QIcon::fromTheme("application-exit"));
    action->setShortcuts(QKeySequence::Quit);
    action->setStatusTip(tr("Exit the application"));
  }
}

void MainWindowForm::setupStandardEditMenu() {
  QAction *action;

  action = ui.actionUndo;
  if (action) {
    action->setText(tr("&Undo"));
    action->setIcon(QIcon::fromTheme("edit-undo"));
    action->setShortcuts(QKeySequence::Undo);
    action->setStatusTip(tr("Undo the last operation"));
  }

  action = ui.actionRedo;
  if (action) {
    action->setText(tr("&Redo"));
    action->setIcon(QIcon::fromTheme("edit-redo"));
    action->setShortcuts(QKeySequence::Redo);
    action->setStatusTip(tr("Redo the last operation"));
  }

  action = ui.actionCut;
  if (action) {
    action->setText(tr("Cu&t"));
    action->setIcon(QIcon::fromTheme("edit-cut"));
    action->setShortcuts(QKeySequence::Cut);
    action->setStatusTip(
        tr("Cut the current selection's contents to the clipboard"));
  }

  action = ui.actionCopy;
  if (action) {
    action->setText(tr("&Copy"));
    action->setIcon(QIcon::fromTheme("edit-copy"));
    action->setShortcuts(QKeySequence::Copy);
    action->setStatusTip(
        tr("Copy the current selection's contents to the clipboard"));
  }

  action = ui.actionPaste;
  if (action) {
    action->setText(tr("&Paste"));
    action->setIcon(QIcon::fromTheme("edit-paste"));
    action->setShortcuts(QKeySequence::Paste);
    action->setStatusTip(
        tr("Paste the clipboard's contents into the current selection"));
  }

  action = ui.actionDelete;
  if (action) {
    action->setText(tr("&Delete"));
    action->setIcon(QIcon::fromTheme("edit-delete"));
    action->setShortcuts(QKeySequence::Delete);
    action->setStatusTip(tr("Delete the current selection"));
  }

  action = ui.actionSelect_All;
  if (action) {
    action->setText(tr("Select &All"));
    action->setIcon(QIcon::fromTheme("edit-select-all"));
    action->setShortcuts(QKeySequence::SelectAll);
    action->setStatusTip(tr("Select all items"));
  }
}

void MainWindowForm::setupStandardHelpMenu() {
  QAction *action;
  action = ui.actionAbout;
  if (action) {
    action->setText(tr("&About"));
    action->setIcon(QIcon::fromTheme("help-about"));
    action->setStatusTip(tr("Show the application's About box"));
  }
}

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

MainWindowForm::MainWindowForm(QMainWindow *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  // Connect some standard menu actions.
  setupStandardFileMenu();
  setupStandardEditMenu();
  setupStandardHelpMenu();
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

void MainWindowForm::on_actionAbout_triggered() { showAboutDialog(); }
