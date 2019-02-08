#include "glwidget.h"
#include <cmath>
#include <cstdlib>

/* Some parameters for manipulating objects */
GLfloat scale = 1.0f;
GLfloat x_pos = 0.0f, y_pos = 0.0f;
GLfloat x_rot = 0.0f, y_rot = 0.0f, z_rot = 30.0f;

/* Some colours defined in rgb alpha space */
GLfloat ambiant[] = {0.1745f * 1.5f, 0.01175f * 1.5f, 0.01175f * 1.5f, 1.0f};
GLfloat diffuse[] = {0.61424f, 0.04136f, 0.04136f, 1.0f};
GLfloat specular[] = {0.727811f, 0.626959f, 0.626959f, 1.0f};
GLfloat shininess = 0.6f * 128.0f;

/* light source */
GLfloat light_position[] = {10.0f, 10.0f, 10.0f, 0.0f}; // (x, y, z, w)
GLfloat light_ambient[] = {0.8f, 0.8f, 0.8f, 1.0f};     // (r, g, b, a)
GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
  setFocusPolicy(Qt::StrongFocus);
}

void GLWidget::resetObject() {
  scale = 1.0f;
  x_pos = 0.0f, y_pos = 0.0f;
  x_rot = 0.0f, y_rot = 0.0f, z_rot = 30.0f;
}

void GLWidget::initializeGL() {
  /*
      OpenGL stuff
      you will learn about later the course.
  */

  /* enable lighting for 3D shading effects*/
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); // OpenGL can have up to 8 light sources

  /* set the position of lIGHT0 */
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

  glShadeModel(GL_SMOOTH);
  /* enable depth-buffering */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}

void GLWidget::paintGL() {
  /* set background colour and clear the window */
  glClearColor(0.8, 0.8, 0.8, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  /* apply user input to any objects drawn, to do this we
need to know some mathematics for moving objects around a space.
OpenGL assumes the following orientation of basis axes
                         y+
                         |    z-
                         |   /
                         |  /
                         | /
              x-_________|/_________x+
                         /
                        /|
                       / |
                      /  |
                     z+  |
                         y-

             you will learn more about all these concepts later in the
             course.
         */
  // move object around the screen in a plane
  glTranslatef(x_pos, y_pos, 0.0);
  // rotate the object
  glRotatef(x_rot, 0.0f, 0.0f, 1.0f);
  glRotatef(y_rot, 0.0f, 1.0f, 0.0f);
  glRotatef(z_rot, 1.0f, 0.0f, 0.0f);

  // change the size of the object
  glScalef(scale, scale, scale); // scale the object

  // give the object a colour
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambiant);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

  // the standard OpenGL test object, it is a teapot
  glutSolidTeapot(1.0f);

  glPopMatrix();

  glFlush(); // flush everything from the draw buffer to be displayed
}

void GLWidget::resizeGL(int w, int h) {
  // init3D(); //initialise 3D lighting and shading

  /* set the projection matrix */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /* set a very simple orthographic projection 3D
     objects are drawn in a cube. Each parameter gives
     the position of the 6 planes the make up the cube.
             left  right  top  bottom   near  far     */

  GLfloat aspectRatio = GLfloat(this->width()) / GLfloat(this->height());
  glOrtho(-2.0 * aspectRatio, 2.0 * aspectRatio, -2.0, 2.0, -1.5, 1.5);
  glViewport(0, 0, this->width(), this->height()); // set the viewport
  glMatrixMode(GL_MODELVIEW);
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_Minus:
    scale /= 1.01f;
    this->updateGL();
    break;
  case Qt::Key_Plus:
    scale *= 1.01f;
    this->updateGL();
    break;
  case Qt::Key_R:
    resetObject();
    this->updateGL();
    break;
  case Qt::Key_Q:
    qApp->exit();
    break;

  case Qt::Key_X:
    if (x_rot < 360.0f)
      x_rot += 10.0f;
    else
      x_rot = 0.0f;
    this->updateGL();
    break;
  case Qt::Key_Y:
    if (y_rot < 360.0f)
      y_rot += 10.0f;
    else
      y_rot = 0.0f;
    this->updateGL();
    break;
  case Qt::Key_Z:
    if (z_rot < 360.0f)
      z_rot += 10.0f;
    else
      z_rot = 0.0f;
    this->updateGL();
    break;

  default:
    event->ignore();
    break;
  }
}

GLWidget::~GLWidget() {
  // TODO Auto-generated destructor stub
}
