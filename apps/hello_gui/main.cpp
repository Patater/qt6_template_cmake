#include "mainwindow.h"
#include "TriangleWidget.h"

#include <QDebug>
#include <qlogging.h>
#include <QSurfaceFormat>
#include <QApplication>
#include <QOpenGLContext>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setVersion(3, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindowForm form;
  TriangleWidget widget(&form);
  form.setCentralWidget(&widget);
  form.show();

  qDebug() << "OpenGL Version:"
           << QOpenGLContext::currentContext()->format().majorVersion() << "."
           << QOpenGLContext::currentContext()->format().minorVersion();

  return app.exec();
}
