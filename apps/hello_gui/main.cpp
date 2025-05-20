#include "mainwindow.h"
#include "TriangleWidget.h"
#include "VSyncDriver.h"

#include <QDebug>
#include <qlogging.h>
#include <QSurfaceFormat>
#include <QApplication>
#include <QOpenGLContext>

int main(int argc, char **argv) {
  // We need to set the surface format before creating the application.
  // Otherwise, the application may get created with a format that we didn't
  // request and, due to OpenGL context sharing, are unable to change.
  QSurfaceFormat defaultFormat = QSurfaceFormat::defaultFormat();
  defaultFormat.setVersion(3, 3);
  defaultFormat.setProfile(QSurfaceFormat::CoreProfile);
  defaultFormat.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  defaultFormat.setSwapInterval(0);
  QSurfaceFormat::setDefaultFormat(defaultFormat);

  // Ensure all windows share a single OpenGL context. This also needs to be
  // called before creating the application.
  QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

  QApplication app(argc, argv);

  // Create the main window.
  MainWindowForm form;
  TriangleWidget widget(&form);
  form.setCentralWidget(&widget);
  form.show();

  qDebug() << "OpenGL Version:"
           << QOpenGLContext::currentContext()->format().majorVersion() << "."
           << QOpenGLContext::currentContext()->format().minorVersion();

  return app.exec();
}
