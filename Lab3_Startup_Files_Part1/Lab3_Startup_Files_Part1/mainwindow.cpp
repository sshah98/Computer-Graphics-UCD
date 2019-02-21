#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  opengl = new GLWidget();
  ui->setupUi(this);
  ui->glScrollArea->setWidgetResizable(true);
  ui->glScrollArea->setWidget(opengl);
  opengl->setFocus();

  Q_INIT_RESOURCE(resources);
  QFile::copy(":/comp30020-Lab3.ppm",
              QDir::homePath() + QString("/Desktop/comp30020-Lab3.ppm"));
}

MainWindow::~MainWindow() {
  delete opengl;
  delete ui;
}
