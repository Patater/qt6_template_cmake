#ifndef TRIANGLE_WIDGET
#define TRIANGLE_WIDGET

#include <QElapsedTimer>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QtGui/qopengl.h>

class QWidget;
class QOpenGLShaderProgram;

class TriangleWidget : public QOpenGLWidget,
                       protected QOpenGLFunctions_3_3_Core {
public:
  TriangleWidget(QWidget *parent = nullptr);

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void showEvent(QShowEvent *event) override;

private:
  void updateFrame(void);

  double m_time = 0;
  QOpenGLShaderProgram *m_program = nullptr;
  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;
  QOpenGLBuffer m_cbo;
  GLint m_posAttr = 0;
  GLint m_colAttr = 0;
  GLint m_matrixUniform = 0;

  // Timers for driving animation by time elapsed.
  // - m_timer is for periodically telling Qt we want the surface to be
  // rendered. If we don't do this, no animation happens unless there is
  // another reason to redraw the surface (like resizing the window).
  // - m_elapsedTimer keeps track of how long the animation has been running,
  // so that we know what image to show if we've been asked to generate a new
  // frame, via paintGL().
  // When m_timer expires, we check how much time has elapsed and progress the
  // time by that much and request a render via update().
  // It's okay if the timer is not synchronized with vblank, because the
  // handling of the render request, via update(), is synchronous to vblank
  // (at least when compositing is enabled).
  QWindow *m_window;
  double m_targetFrameRate;
  QTimer m_timer;
  QElapsedTimer m_elapsedTimer;
};

#endif
