#include "glwidget.h"
#include <QDebug>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {

    setFocusPolicy(Qt::StrongFocus);
    mainWindow = NULL;
    brushSize = 3;
    this->setBrushColour(0, 0, 0);
}

void GLWidget::setBrushColour(Byte r, Byte g, Byte b) {
    /*
   * TO DO
   * call the PPM Image display function
   */

    brushColour = RGBValue(r, g, b);

    qDebug() << "Switching brush colour to: (" << r << "," << g << "," << b
             << ")";
}

void GLWidget::initializeGL() {
    // default behaviour clears the buffer
    glClearColor(1.0, 1.0, 1.0, 1.0); // set the colour of the canvas
    glClear(GL_COLOR_BUFFER_BIT);     // clean the canvas (draw buffer)
}

void GLWidget::paintGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // set the canvas colour
    glClear(GL_COLOR_BUFFER_BIT);     // clear the buffer
    /*
   * TO DO
   * call the PPM Image display function
   */
    image.display();
    glFlush(); // flush everything from the draw buffer to be displayed
}

void GLWidget::resizeGL(int w, int h) {
    /*
   * TO DO
   * set dimensions to correct value and resize image
   */
    width = w;
    height = h;
    image.resize(w, h);

    // and sets to a standard 2D set of coordinates
    glMatrixMode(GL_PROJECTION);         // switch to proj. mat.
    glLoadIdentity();                    // set to identity
    glOrtho(0, width, 0, height, -1, 1); // with orthog proj
    glViewport(0, 0, width, height);     // set the viewport
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    // RGB colours
    case Qt::Key_R:
        this->setBrushColour(255, 0, 0);
        this->updateGL();
        break;
    case Qt::Key_G:
        this->setBrushColour(0, 255, 0);
        this->updateGL();
        break;
    case Qt::Key_B:
        this->setBrushColour(0, 0, 255);
        this->updateGL();
        break;
        // CMYK colours
    case Qt::Key_C:
        this->setBrushColour(0, 255, 255);
        this->updateGL();
        break;
    case Qt::Key_M:
        this->setBrushColour(255, 0, 255);
        this->updateGL();
        break;
    case Qt::Key_Y:
        this->setBrushColour(255, 255, 0);
        this->updateGL();
        break;
    case Qt::Key_K:
        this->setBrushColour(0, 0, 0);
        this->updateGL();
        break;
        // white colour
    case Qt::Key_W:
        this->setBrushColour(255, 255, 255);
        this->updateGL();
        break;

        // brush size
    case Qt::Key_Minus:
        brushSize--;
        if (brushSize < 1)
            brushSize = 1;
        this->updateGL();
        break;
    case Qt::Key_Plus:
        brushSize++;
        if (brushSize > 80)
            brushSize = 80;
        this->updateGL();
        break;

        // load / save PPM image
    case Qt::Key_L:
        this->loadImage();
        this->updateGL();
        break;
    case Qt::Key_S:
        this->saveImage();
        break;
    case Qt::Key_E:
        this->clearImage();
        this->updateGL();
        break;

        // quit
    case Qt::Key_Q:
        qApp->exit();
        break;
    default:
        event->ignore();
        break;
    }
}

void GLWidget::paintImageAt(int x, int y) {
    /*
   * TO DO
   * Use brush and current colour to paint on image
   * Pseudo code for square brush:
   * for width of brush {
   *   for height of brush {
   *     set image pixel;
   *   }
   * }
   *
   * Challegenge: paint image using a round shapep brush
   */

    for(int i=0; i<brushSize; i++) {
        for(int j=0; j<brushSize; j++) {
            if(i*i + j*j < brushSize * brushSize) {
                image.setPixel(x+i, y+j, brushColour);
                image.setPixel(x-i, y+j, brushColour);
                image.setPixel(x+i, y-j, brushColour);
                image.setPixel(x-i, y-j, brushColour);

            }
        }
    }

    this->updateGL(); // call a refresh
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    // convert to image coordinates
    // make sure to flip the axes for from the top left
    int image_x = height - 1 - devicePixelRatio() * event->y();
    int image_y = devicePixelRatio() * event->x();

    /*
   * TO DO
   */
    paintImageAt(image_x, image_y);


}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    // convert to image coordinates
    // make sure to flip the axes for from the top left
    int image_x = height - 1 - devicePixelRatio() * event->y();
    int image_y = devicePixelRatio() * event->x();

    /*
   * TO DO
   */

    paintImageAt(image_x, image_y);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
    // convert to image coordinates
    // make sure to flip the axes for from the top left
    int image_x = height - 1 - devicePixelRatio() * event->y();
    int image_y = devicePixelRatio() * event->x();

    /*
   * TO DO
   */
    paintImageAt(image_x, image_y);
}

// load & save routines
void GLWidget::loadImage() {
    if (mainWindow == NULL) {
        //      <widget class="QMainWindow" name="MainWindow">
        //       <widget class="QWidget" name="centralWidget">
        //        <widget class="QScrollArea" name="glScrollArea">
        //          <widget class="QWidget" name="glWidget">
        mainWindow = parentWidget()->parentWidget()->parentWidget()->parentWidget();
    }
    std::string filePath = QDir::homePath().toStdString() +
            std::string("/Desktop/comp30020-Lab3.ppm");

    /*
   * TO DO
   * Load and resize the main window to the new image width and height (+the
   * margins)
   * You will need to figure out the margins.
   * Try printing out the main window and image widths and heights
   * before and after loading the image/doing the resize
   *
   * call mainWindow->size() and this->size to get current sizes
   */

    int width = mainWindow->width() - this->width;
    int height = mainWindow->height() - this->height;

    image.readFile(filePath);
    QSize margin = QSize(width, height);

    int imgwidth = image.width() + margin.width();
    int imgheight = image.height() + margin.height();

    QSize windowSize = QSize(imgwidth, imgheight);

    mainWindow->resize(windowSize);
    this->updateGL(); // call a refresh
}

void GLWidget::saveImage() {
    QString filePath = QDir::homePath() + "/Desktop/comp30020-Lab3.ppm";
    QFile file(filePath);
    file.remove();
    /*
   * TO DO
   * Call filePath.toStdString() to convert to a std::string
   */
    image.writeFile(filePath.toStdString());
}

//  and an erase routine
void GLWidget::clearImage() {
    /*
   * TO DO
   *
   */
    image.clear();

}

GLWidget::~GLWidget() {
    // Auto-generated destructor stub
}
