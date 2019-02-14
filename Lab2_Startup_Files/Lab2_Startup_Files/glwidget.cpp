#include "glwidget.h"
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <cmath>
#include <cstdlib>

#include "axismodel.h"
#include "test.h"
#include "vector.h"

std::string path = QDir::homePath().toStdString() + std::string("/Desktop/");

int nlines = 22;
int plane = xy_plane;

// light source
GLfloat light_position[] = {0.0f, 100.0f, 100.0f, 0.0f}; // (x, y, z, w)
GLfloat light_ambient[] = {0.25f, 0.25f, 0.25f, 1.0f};   // (r, g, b, a)
GLfloat light_diffuse[] = {0.25f, 0.25f, 0.25f, 1.0f};

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
  setFocusPolicy(Qt::StrongFocus);
}

void GLWidget::initializeGL() {
  // This is all OpenGL stuff you will learn about later in the course.
  // enable lighting for 3D shading effects
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  // OpenGL can have up to 8 light sources

  // set location of LIGHT0
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

  glShadeModel(GL_SMOOTH);
  // enable depth-buffering
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}

void GLWidget::paintGL() {
  // set the colour of the window to white
  // and clear the window
  glClearColor(light_grey[0], light_grey[1], light_grey[2], 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* OpenGL assumes the following
   * orientation of basis axes
   *
   *          y+
   *          |  z-
   *          | /
   *  x-______|/______x+
   *          /
   *         /|
   *       z+ |
   *          y-
  */

  // cartesian 2D (xy)-plane
  Cartesian2D cartesian2D(plane, size(), devicePixelRatio(), nlines);
  // draw (xy)-plane
  cartesian2D.drawPlane();
  // draw some linear alegra objects
  cartesian2D.drawMaths();

  // flush everything from draw buffer
  glFlush();
}

void GLWidget::resizeGL(int w, int h) {
  // set the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  w = static_cast<GLfloat>(this->width());
  h = static_cast<GLfloat>(this->height());
  GLfloat scale = 1.5;
  GLfloat aspectRatio = GLfloat(this->width()) / GLfloat(this->height());
  // left, right, top, bottom, near, far
  glOrtho(-scale * aspectRatio, scale * aspectRatio, -scale, scale, -scale,
          scale);
  // set the viewport
  glViewport(0, 0, this->width(), this->height());
  glMatrixMode(GL_MODELVIEW);
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_Minus:
    nlines += 2;
    break;
  case Qt::Key_Plus:
    if (nlines != 2.0) {
      nlines -= 2;
    }
    break;
  case Qt::Key_X:
    plane = yz_plane;
    break;
  case Qt::Key_Y:
    plane = zx_plane;
    break;
  case Qt::Key_Z:
    plane = xy_plane;
    break;
  case Qt::Key_T: // run the test code
  {
    std::string filePath = path + std::string("comp30020-Lab2-solution.txt");
    if (runTest(filePath))
      std::cout << std::endl << "Solution file " << filePath << std::endl;
    else
      std::cout << "Unable to write file" << filePath << std::endl;
    break;
  }
  case Qt::Key_S: {
    std::string filePath = path + std::string("comp30020-Lab2-Screenshot.ppm");
    this->screenShot(filePath);
    break; // take a screen shot
  }
  case Qt::Key_Q:
    qApp->exit();
    break;

  default:
    event->ignore();
    break;
  }
  this->updateGL();
}

GLWidget::~GLWidget() {
  // TODO Auto-generated destructor stub
}

void GLWidget::screenShot(std::string path) {
  this->paintGL();
  grabFrameBuffer();

  const char *fileName = path.c_str();
  int windowWidth = this->width() * devicePixelRatio();
  int windowHeight = this->height() * devicePixelRatio();
  int nPixelBytes = 3;
  // compute size of pixel map
  int nRowBytes = windowWidth * nPixelBytes;
  int nMapBytes = windowWidth * windowHeight * 3;
  // allocate memory for pixel map
  unsigned char *pixelMap = (unsigned char *)std::malloc(nMapBytes);
  // copy from the frame buffer
  glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE,
               pixelMap);
  char ppmHeader[100];
  // prepare the PPM header
  sprintf(ppmHeader, "P6\n%d %d\n255\n", windowWidth, windowHeight);
  FILE *outFile = fopen(fileName, "wb"); // prepare binary file for writing
  if (outFile == NULL) {
    std::cout << std::endl << "Unable to write file " << fileName << std::endl;
    return;
  }                                                 // error-check
  fwrite(ppmHeader, strlen(ppmHeader), 1, outFile); // write the PPM header
  unsigned char *pixelRow;
  for (pixelRow = pixelMap + nMapBytes - nRowBytes; pixelRow >= pixelMap;
       pixelRow -= nRowBytes)
    fwrite(pixelRow, nRowBytes, 1, outFile);
  std::cout << std::endl << "PPM Screenshot " << fileName << std::endl;
  fclose(outFile);
}
