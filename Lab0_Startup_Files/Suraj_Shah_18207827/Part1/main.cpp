#include "mainwindow.h"
#include <QApplication>
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  glutInit(&argc, argv);
  MainWindow w;
  w.setWindowTitle("COMP30020-Lab0-Part1");
  w.show();

  return app.exec();
}
