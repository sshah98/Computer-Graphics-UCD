#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QMainWindow>
#include <QtOpenGL>
#include <vector>

#include "PPMImage.h"
#include "RGBValue.h"

class GLWidget : public QGLWidget {
  Q_OBJECT
public:
  GLWidget(QWidget *parent = 0);

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  // load & save routines
  void loadImage();
  void saveImage();

  // clear routine
  void clearImage();

  // paint in image with brush
  void paintImageAt(int x, int y);

  // utility routine
  void setBrushColour(Byte r, Byte g, Byte b);

  virtual ~GLWidget();

protected:
  void keyPressEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

private:
  QWidget *mainWindow;
  RGBValue brushColour; // current brush colour
  PPMImage image;       // image being drawn
  int brushSize;        // brush size
  int width, height;
};

#endif // GLWIDGET_H
