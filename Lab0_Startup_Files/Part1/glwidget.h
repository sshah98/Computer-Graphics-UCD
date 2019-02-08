#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QtOpenGL>

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class GLWidget : public QGLWidget {
  Q_OBJECT
public:
  GLWidget(QWidget *parent = 0);
  void resetObject();
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  virtual ~GLWidget();

protected:
  void keyPressEvent(QKeyEvent *event);
};

#endif // GLWIDGET_H
