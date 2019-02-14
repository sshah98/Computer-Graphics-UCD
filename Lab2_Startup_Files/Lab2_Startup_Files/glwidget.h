#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QtOpenGL>

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
  void screenShot(std::string path);
};

#endif // GLWIDGET_H
