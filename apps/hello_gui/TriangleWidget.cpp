#include "TriangleWidget.h"

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtGui/qopengl.h>
#include <qdebug.h>
#include <qlogging.h>
#include <qtypes.h>

static const char *vertexShaderSource = "shaders/vertex.vert";
static const char *fragmentShaderSource = "shaders/fragment.frag";

TriangleWidget::TriangleWidget(QWidget *parent)
    : QOpenGLWidget(parent), m_time(0), m_timer(this) {

  connect(&m_timer, &QTimer::timeout, this, &TriangleWidget::updateFrame);
  m_elapsedTimer.restart();
  m_targetFrameRate = screen()->refreshRate();
  double period = 1.0 / m_targetFrameRate;
  double period_ms = period * 1000.0;
  m_timer.start(period_ms);
}

void TriangleWidget::initializeGL() {
  bool success;

  success = initializeOpenGLFunctions();
  if (!success)
  {
    qFatal("Could not initialize OpenGL functions");
  }

  glClearColor(8.0f / 79.0f, 8.0f / 79.0f, 8.0f / 79.0f, 1.0f);

  m_program = new QOpenGLShaderProgram(this);
  success = m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderSource);
  if (!success)
  {
    qDebug() << "Failed to compile vertex shader:" << m_program->log();
  }
  success = m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderSource);
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
  matrix.rotate(20.0f * m_time / m_targetFrameRate, 1, 0, 0);
  matrix.rotate(30.0f * m_time / m_targetFrameRate, 0, 0, 1);
  matrix.rotate(50.0f * m_time / m_targetFrameRate, 0, 1, 0);
  m_program->setUniformValue(m_matrixUniform, matrix);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  m_vao.release();
  m_program->release();
}

void TriangleWidget::showEvent(QShowEvent *event) {
  QOpenGLWidget::showEvent(event);
  m_time = 0.0; // Reset animation
  update();
}

void TriangleWidget::updateFrame(void) {
  qint64 elapsedMs = m_elapsedTimer.restart();
  m_time += elapsedMs;
  update();
}
