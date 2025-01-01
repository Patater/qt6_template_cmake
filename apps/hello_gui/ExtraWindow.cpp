#include "ExtraWindow.h"
#include "TriangleWidget.h"
#include <qnamespace.h>
#include <QVBoxLayout>

ExtraWindow::ExtraWindow(QWidget *parent) : QWidget(parent, Qt::Window) {
  setWindowTitle("Extra Triangle");
  setMinimumSize(400, 400);

  QVBoxLayout *layout = new QVBoxLayout(this);
  // Remove all margins and spacing
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  TriangleWidget *triangle = new TriangleWidget(this);
  layout->addWidget(triangle);

  // Enable keyboard focus
  setFocusPolicy(Qt::StrongFocus);
}

void ExtraWindow::keyPressEvent(QKeyEvent *event) {
  QWidget::keyPressEvent(event);
}

void ExtraWindow::keyReleaseEvent(QKeyEvent *event) {
  QWidget::keyReleaseEvent(event);
}
