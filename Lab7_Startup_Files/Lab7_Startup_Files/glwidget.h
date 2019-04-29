#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>
#include <QKeyEvent>
#include <QMainWindow>
#include <QtOpenGL>
#include <cmath>
#include <vector>
using namespace std;
#include "objects.h"

class arcBall;

class GLWidget : public QGLWidget {
  Q_OBJECT

public:
  GLWidget(QWidget *parent = 0);
  Objects *objects;

  void loadTextures();
  void setOrtho();
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  void keyPressEvent(QKeyEvent *event);
  void wheelEvent(QWheelEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void drawAxes();
  void drawGrid(GLfloat *colour, int nGridlines);
  void solidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
  void drawHuman();
  void animate(int time);
  virtual ~GLWidget();
public slots:
  void resetArc();
  void resetPos();
  void resetZoom();

protected:
  arcBall *arc;
  bool resetArcBall;
  bool axes;
  bool grid;
  bool wframe;
  bool animation;

  // Animation parameters
  int time;
  int nframes;

  // model position
  float posn_x, posn_z, bodyTheta;
  float left_arm, right_arm;
  float left_leg, right_leg;

  GLuint textures[4];

  int nGridlines;
public slots:
  void idle();
  void saveImage();
};

#endif /* GLWIDGET_H_ */
