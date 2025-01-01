#ifndef TRIANGLE_WIDGET
#define TRIANGLE_WIDGET

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
  TriangleWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {}

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

private:
  int m_frame = 0;
  QOpenGLShaderProgram *m_program = nullptr;
  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;
  QOpenGLBuffer m_cbo;
  GLint m_posAttr = 0;
  GLint m_colAttr = 0;
  GLint m_matrixUniform = 0;
};

#endif
