#include "mainwindow.h"
#include "ExtraWindow.h"
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QtCore/qobjectdefs.h>
#include <QOpenGLWidget>
#include <qaction.h>
#include <qobject.h>
#include <qstatusbar.h>
#include <QString>
#include <qtypes.h>

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
    : QMainWindow(parent), m_ExtraWindow(nullptr), fpsTimer(this) {
  ui.setupUi(this);
}

void MainWindowForm::setupFPSCounter()
{
  // Track FPS with a periodic timer
  connect(&fpsTimer, &QTimer::timeout, this, &MainWindowForm::updateFPS);
  fpsTimer.start(1000);
  frameCount.storeRelaxed(0);
  fpsElapsedTimer.restart();

  QOpenGLWidget *widget = qobject_cast<QOpenGLWidget *>(centralWidget());
  if (widget)
  {
    connect(widget, &QOpenGLWidget::frameSwapped, this,
            &MainWindowForm::onFrameSwapped);
  }
}

void MainWindowForm::teardownFPSCounter()
{
  QOpenGLWidget *widget = qobject_cast<QOpenGLWidget *>(centralWidget());
  if (widget)
  {
    disconnect(widget, &QOpenGLWidget::frameSwapped, this,
               &MainWindowForm::onFrameSwapped);
  }

  disconnect(&fpsTimer, &QTimer::timeout, this, &MainWindowForm::updateFPS);
  fpsTimer.stop();
}

void MainWindowForm::onFrameSwapped()
{
  frameCount.fetchAndAddRelaxed(1);
}

void MainWindowForm::updateFPS()
{
  qint64 elapsedMs = fpsElapsedTimer.restart();
  int frames = frameCount.fetchAndStoreRelaxed(0);

  qreal fps = frames * 1000.0 / elapsedMs;
  statusBar()->showMessage(QString("FPS: %1").arg(fps, 0, 'f', 1));

  // Reset timer and count
  fpsElapsedTimer.restart();
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

void MainWindowForm::on_actionCheckbox_triggered() {
    if (ui.actionCheckbox->isChecked())
    {
        setupFPSCounter();
    }
    else
    {
        teardownFPSCounter();
    }
}

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
