#include "mainwindow.h"

#include <QDebug>
#include <qlogging.h>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QSurfaceFormat>
#include <qtypes.h>
#include <QApplication>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QtGui/qopengl.h>
#include <QScreen>

class QWidget;

static const char *vertexShaderSource =
    "#version 330 core\n"
    "in vec3 posAttr;\n"
    "in vec3 colAttr;\n"
    "out vec3 col;\n"
    "uniform mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * vec4(posAttr, 1.0f);\n"
    "}\n";

static const char *fragmentShaderSource = "#version 330 core\n"
                                          "in vec3 col;\n"
                                          "out vec4 fragColor;\n"
                                          "void main() {\n"
                                          "   fragColor = vec4(col, 1.0f);\n"
                                          "}\n";

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

void TriangleWidget::initializeGL() {
  bool success;

  success = initializeOpenGLFunctions();
  if (!success)
  {
    qFatal("Could not initialize OpenGL functions");
  }

  glClearColor(8.0f / 79.0f, 8.0f / 79.0f, 8.0f / 79.0f, 1.0f);

  m_program = new QOpenGLShaderProgram(this);
  success = m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  if (!success)
  {
    qDebug() << "Failed to compile vertex shader:" << m_program->log();
  }
  success = m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                     fragmentShaderSource);
  if (!success)
  {
    qDebug() << "Failed to compile fragment shader:" << m_program->log();
  }
  success = m_program->link();
  if (!success)
  {
    qDebug() << "Failed to link shader program:" << m_program->log();;
  }

  m_vao.create();
  m_vao.bind();

  static const GLfloat vertices[] = {
      0.0f, 0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f
  };
  m_vbo.create();
  m_vbo.bind();
  m_vbo.allocate(vertices, sizeof(vertices));

  static const GLfloat colors[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                   0.0f, 0.0f, 0.0f, 1.0f};
  m_cbo.create();
  m_cbo.bind();
  m_cbo.allocate(colors, sizeof(colors));

  m_program->bind();

  m_posAttr = m_program->attributeLocation("posAttr");
  m_colAttr = m_program->attributeLocation("colAttr");
  m_matrixUniform = m_program->uniformLocation("matrix");

  m_vbo.bind();
  m_program->enableAttributeArray(m_posAttr);
  m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);

  m_cbo.bind();
  m_program->enableAttributeArray(m_colAttr);
  m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, 0, 3);

  m_vao.release();
  m_program->release();

  qDebug() << "Attribute locations: posAttr =" << m_posAttr
           << ", colAttr =" << m_colAttr;
  qDebug() << "Uniform location: matrix =" << m_matrixUniform;
}

void TriangleWidget::resizeGL(int w, int h) {
  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);
}

void TriangleWidget::paintGL() {
  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  m_program->bind();
  m_vao.bind();

  QMatrix4x4 matrix;
  float aspect = float(width()) / float(height());
  matrix.perspective(60.0f, aspect, 0.1f, 100.0f);
  matrix.translate(0, 0, -2.0);
  matrix.rotate(20.0f * m_frame / screen()->refreshRate(), 1, 0, 0);
  matrix.rotate(30.0f * m_frame / screen()->refreshRate(), 0, 0, 1);
  matrix.rotate(50.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
  m_program->setUniformValue(m_matrixUniform, matrix);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  m_vao.release();
  m_program->release();

  ++m_frame;

  update();
}

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
