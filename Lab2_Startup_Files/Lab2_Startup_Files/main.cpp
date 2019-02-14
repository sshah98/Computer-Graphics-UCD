#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow w;
  w.setWindowTitle("COMP30020-Lab2");
  w.show();

  return app.exec();
}
