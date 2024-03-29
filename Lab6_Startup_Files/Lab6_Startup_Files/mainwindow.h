#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glwidget.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  GLWidget *opengl;
  ~MainWindow();

public slots:
  void resetOpenGLView();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
