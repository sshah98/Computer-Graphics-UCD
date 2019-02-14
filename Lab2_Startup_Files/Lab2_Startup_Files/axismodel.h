#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "matrix.h"
#include "point.h"
#include "vector.h"
#include <QOpenGLPaintDevice>

// basic colours
static const GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
static const GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat grey[] = {0.5, 0.5, 0.5, 1.0};
static const GLfloat light_grey[] = {0.9, 0.9, 0.9, 1.0};

// primary colours
static const GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
static const GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
static const GLfloat dark_green[] = {0.0, 0.5, 0.0, 1.0};
static const GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};

// secondary colours
static const GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
static const GLfloat magenta[] = {1.0, 0.0, 1.0, 1.0};
static const GLfloat cyan[] = {0.0, 0.8, 0.8, 1.0};

// other colours
static const GLfloat orange[] = {1.0, 0.5, 0.0, 1.0};
static const GLfloat brown[] = {0.5, 0.25, 0.0, 1.0};
static const GLfloat dkgreen[] = {0.0, 0.5, 0.0, 1.0};
static const GLfloat pink[] = {1.0, 0.6, 0.6, 1.0};

static const double pi = 3.14159265358979;

enum { xy_plane = 0, yz_plane, zx_plane };

class Cartesian2D {

private:
  QSize size;
  int scale;
  int nLines;
  int plane;

public:
  // draw math
  void drawMaths();

  // constructor for cartesian plane
  Cartesian2D(int plane, QSize size, int scale, int nLines);

  // draw (xy)-plane with grid lines
  void drawPlane();

  // draw point
  void drawPoint(Point &p, const GLfloat colour[4], std::string name);

  // draw vector between two points
  void drawVector(Point &p, Point &q, const GLfloat colour[4],
                  std::string name);

  // draw vector from a source point
  void drawVector(Vector &v, Point &p, const GLfloat colour[4],
                  std::string name);
};

#endif // _OBJECTS_H
