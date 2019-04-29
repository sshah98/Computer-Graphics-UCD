#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QtOpenGL>
#include <vector>

#include "arcball.h"
#include "point.h"
#include "vector.h"

class GLWidget : public QGLWidget {
  Q_OBJECT
public:
  GLWidget(QWidget *parent = 0);

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  virtual ~GLWidget();

public slots:
  void resetArcballAndZoom();

protected:
  // select model to be displayed
  void keyPressEvent(QKeyEvent *event);
  // zoom
  void wheelEvent(QWheelEvent *event);
  // rotation
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

private:
  void setProjection();

  int width = 800, height = 800;
  // quaternion rotation
  ArcBall *arcBall;
  bool isDragging = false;
  // zoom
  float zoom = 1.0;
  // default is Octahedron
  int modelIndex = 2;
};

#endif // GLWIDGET_H
