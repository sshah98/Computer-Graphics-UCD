#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  Q_INIT_RESOURCE(resources);
  QFile::copy(":/earth.ppm", QDir::homePath() + QString("/Desktop/earth.ppm"));
  QFile::copy(":/moon.ppm", QDir::homePath() + QString("/Desktop/moon.ppm"));
  QFile::copy(":/comp30020-Lab5.ppm",
              QDir::homePath() + QString("/Desktop/comp30020-Lab5.ppm"));

  opengl = new GLWidget();
  ui->setupUi(this);
  ui->glScrollArea->setWidgetResizable(true);
  ui->glScrollArea->setWidget(opengl);
  opengl->setFocus();
}

MainWindow::~MainWindow() {
  delete opengl;
  delete ui;
}
