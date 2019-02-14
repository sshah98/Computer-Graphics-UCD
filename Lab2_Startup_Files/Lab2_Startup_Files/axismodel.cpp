#include "axismodel.h"
#include <QPainter>
#include <QVector2D>
#include <QDebug>
#include <math.h>

// Test Point, Vector and Matrix classe
void Cartesian2D::drawMaths() {
  // defines a quadrilateral in (xy)-plane
  Point p(1, 1, 0);
  drawPoint(p, red, "P");
  Point q(2, 5, 0);
  drawPoint(q, dark_green, "Q");
  Point r(4, -3, 0);
  drawPoint(r, yellow, "R");
  Point s(6, 2, 0);
  drawPoint(s, cyan, "S");

  drawVector(p, q, grey, ""); //  Empty string for unnamed vectors
  drawVector(p, r, grey, "");
  drawVector(r, s, grey, "");
  drawVector(q, s, grey, "");

  Vector v = q - p;
  Vector w = r - p;
  Vector v_cross_w = (w.cross(v)).normalised();
  Vector w_cross_v = (v.cross(w)).normalised();

  Point a(-3, 3, 0);
  drawVector(v, a, grey, "v");
  drawVector(w, a, grey, "w");
  drawVector(v_cross_w, a, red, "u");

  Point b(-7, 2, 0);
  drawVector(v, b, grey, "v");
  drawVector(w, b, grey, "w");
  drawVector(w_cross_v, b, red, "u'");

  Point t(-6, -6, 0);
  drawPoint(t, grey, "T");
  Vector y_vec(0.0, 3.0, 0.0); // a vector parallel to y-axis
  drawVector(y_vec, t, blue, "");

  Vector z_vec(0.0, 0.0, 8.0); // a vector parallel to z-axis
  drawVector(z_vec, r, blue, "");

  /* a standard cartesian rotation matrix
   * degrees in radians, 0.5 = 45 degrees
   * matrix describes how other components should change
   * in relation to the z-axis in this case
   */
  float m_coeff[3][3] = {{float(cos(0.5)), float(-sin(0.5)), 0.0},
                         {float(sin(0.5)), float(cos(0.5)), 0.0},
                         {0.0, 0.0, 1.0}};
  Vector y_vec_rot = Matrix(m_coeff) * y_vec;
  drawVector(y_vec_rot, t, orange, ""); // CCW rotation
}

// Create 2D cartian plane (xy), (yz) or (zx)
Cartesian2D::Cartesian2D(int plane, QSize size, int scale, int nLines) {
  this->plane = plane;
  this->size = size;
  this->scale = scale;
  this->nLines = nLines;
}

// Draw 2 plane with axis
void Cartesian2D::drawPlane() {
  // Qt setup
  QOpenGLPaintDevice device(size * scale);
  QPainter painter(&device);
  painter.setRenderHint(QPainter::Antialiasing);
  QFont font;
  QPainterPath path;
  QPen pen = QPen(QColor(0, 180, 20, 255), 1 * scale, Qt::SolidLine,
                  Qt::RoundCap, Qt::RoundJoin);

  // grid setup
  float h = size.height() * scale;
  float w = size.width() * scale;
  float delta = round(h / nLines);

  // grid
  QPoint offset(w / 2 - int(w / 2 / delta) * delta, h / 2 - int(h / 2 / delta) * delta);
  QRectF rect(0, 0, w, h);
  for (float i = offset.y(); i <= h; i += delta) {
    path.moveTo(rect.left(), rect.top() + i);
    path.lineTo(rect.right(), rect.top() + i);
  }
  for (float i = offset.x(); i <= w; i += delta) {
    path.moveTo(rect.left() + i, rect.top());
    path.lineTo(rect.left() + i, rect.bottom());
  }
  painter.strokePath(path, pen);

  // scale to grid
  QPointF origin(w / 2.0, h / 2.0);
  rect = QRect(0, 0, w / delta, h / delta);
  painter.translate(origin);
  painter.scale(delta, delta);
  font.setPixelSize(1);
  font.setItalic(true);
  painter.setFont(font);

  // origin
  path = QPainterPath();
  path.addEllipse(QPoint(0, 0), 8.0 / delta * scale, 8.0 / delta * scale);
  pen.setWidthF(2.0 / delta * scale);
  pen.setColor(Qt::black);
  painter.strokePath(path, pen);
  path = QPainterPath();
  path.addEllipse(QPoint(0, 0), 2.0 / delta * scale, 2.0 / delta * scale);
  painter.fillPath(path, Qt::black);

  // horizontal-axis
  path = QPainterPath();
  QPointF offsetPoint(rect.size().width() / 2, rect.size().height() / 2);
  path.moveTo(-offsetPoint.x() + 0.5, 0);
  path.lineTo(offsetPoint.x() - 0.5, 0);
  path.moveTo(offsetPoint.x() - 0.5, 0);
  path.lineTo(offsetPoint.x() - 1.5, 0 - 1.0 / 3.0);
  path.moveTo(offsetPoint.x() - 0.5, 0);
  path.lineTo(offsetPoint.x() - 1.5, 0 + 1.0 / 3.0);
  QRectF textRect(rect.center().x() - 1.2, -1.2, 1, 1);
  switch (plane) {
  case xy_plane:
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom, "X");
    break;
  case yz_plane:
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom, "Y");
    break;
  case zx_plane:
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom, "Z");
    break;
  }
  pen.setColor(Qt::black);
  pen.setWidthF(3.0 / delta * scale);
  painter.strokePath(path, pen);

  // vertical-axis
  path = QPainterPath();
  path.moveTo(0, -offsetPoint.y() + 0.5);
  path.lineTo(0, offsetPoint.y() - 0.5);
  path.lineTo(0, -offsetPoint.y() + 0.5);
  path.lineTo(-1.0 / 3.0, -offsetPoint.y() + 1.5);
  path.lineTo(0, -offsetPoint.y() + 0.5);
  path.lineTo(1.0 / 3.0, -offsetPoint.y() + 1.5);
  textRect = QRectF(0.2, -offsetPoint.y() + 0.3, 1, 1);
  switch (plane) {
  case xy_plane:
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom, "Y");
    break;
  case yz_plane:
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom, "Z");
    break;
  case zx_plane:
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom, "X");
    break;
  }
  pen.setColor(Qt::black);
  pen.setWidthF(3.0 / delta * scale);
  painter.strokePath(path, pen);
}

void Cartesian2D::drawPoint(Point &p, const GLfloat colour[],
                            std::string name) {
  // Qt setup
  QOpenGLPaintDevice device(size * scale);
  QPainter painter(&device);
  painter.setRenderHint(QPainter::Antialiasing);
  QFont font;
  QPainterPath path;
  QColor color(QColor(int(colour[0] * 255), int(colour[1] * 255),
                      int(colour[2] * 255), int(colour[3] * 255)));
  QPen pen =
      QPen(color, 1.5 * scale, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(pen);

  // grid setup and transform
  float h = size.height() * scale;
  float w = size.width() * scale;
  float delta = round(h / nLines);
  QPointF origin(w / 2, h / 2);
  painter.translate(origin);
  painter.scale(delta, -delta);

  // project point on cartesian 2D plane
  QPointF pointP;
  switch (plane) {
  case xy_plane:
    pointP = QPointF(p.x, p.y);
    break;
  case zx_plane:
    pointP = QPointF(p.z, p.x);
    break;
  case yz_plane:
    pointP = QPointF(p.y, p.z);
    break;
  }

  // draw point
  path.addEllipse(pointP, 4.0 / delta * scale, 4.0 / delta * scale);
  painter.fillPath(path, color);

  // draw label
  font.setPixelSize(1);
  font.setItalic(true);
  painter.setFont(font);
  painter.scale(1, -1);
  QRectF textRect = QRectF(pointP.x() + 0.5, -pointP.y() - 0.5, 1, 1);
  painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom,
                   QString(name.c_str()));
}

void Cartesian2D::drawVector(Point &p, Point &q, const GLfloat colour[4],
                             std::string name) {

  Vector v = q - p;
  drawVector(v, p, colour, name);
}

void Cartesian2D::drawVector(Vector &v, Point &p, const GLfloat colour[4],
                             std::string name) {

  // Qt setup
  QOpenGLPaintDevice device(size * scale);
  QPainter painter(&device);
  painter.setRenderHint(QPainter::Antialiasing);
  QFont font;
  QPainterPath path;
  QColor color(QColor(int(colour[0] * 255), int(colour[1] * 255),
                      int(colour[2] * 255), int(colour[3] * 255)));
  QPen pen =
      QPen(color, 0.1 * scale, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(pen);

  // grid setup
  float h = size.height() * scale;
  float w = size.width() * scale;
  float delta = round(h / nLines);
  QPointF origin(w / 2.0, h / 2.0);
  painter.translate(origin);
  painter.scale(delta, -delta);

  // project point and vector on cartesian 2D plane
  QVector2D vectorV;
  QPointF pointP;
  float dz;
  switch (plane) {
  case xy_plane:
    pointP = QPointF(p.x, p.y);
    vectorV = QVector2D(v.dx, v.dy);
    dz = v.dz;
    break;
  case zx_plane:
    pointP = QPointF(p.z, p.x);
    vectorV = QVector2D(v.dz, v.dx);
    dz = v.dy;
    break;
  case yz_plane:
    pointP = QPointF(p.y, p.z);
    vectorV = QVector2D(v.dy, v.dz);
    dz = v.dx;
    break;
  }

  if (vectorV.length() == 0) { // normal to plane
    if (dz == 0)
      return; // don't draw zero length vector
    path.addEllipse(pointP, 8.0 / delta * scale, 8.0 / delta * scale);
    pen.setWidthF(2.0 / delta * scale);
    painter.strokePath(path, pen);
    path = QPainterPath();
    if (dz > 0) {
      path.addEllipse(pointP, 2.0 / delta * scale, 2.0 / delta * scale);
      painter.fillPath(path, color);
    } else {
      float d = 8.0 / delta * scale * sqrt(2) / 2;
      path.moveTo(pointP.x() + d, pointP.y() + d);
      path.lineTo(pointP.x() - d, pointP.y() - d);
      path.moveTo(pointP.x() - d, pointP.y() + d);
      path.lineTo(pointP.x() + d, pointP.y() - d);
      painter.strokePath(path, pen);
    }
  } else {
    // draw vector
    QPointF pointQ = pointP + vectorV.toPointF();
    path.moveTo(pointP);
    path.lineTo(pointQ);

    // draw vector head
    QVector2D unitV = vectorV / vectorV.length();
    QVector2D normalV(-unitV.y(), unitV.x());
    QPointF pointT1 =
        pointQ - (normalV / 6).toPointF() - (unitV / 2).toPointF();
    QPointF pointT2 =
        pointQ + (normalV / 6).toPointF() - (unitV / 2).toPointF();
    path.moveTo(pointQ);
    path.lineTo(pointT1);
    path.moveTo(pointQ);
    path.lineTo(pointT2);
    pen.setWidthF(2.0 / delta * scale);
    painter.strokePath(path, pen);
  }

  // draw label
  if (name.length() > 0) {
    font.setPixelSize(1);
    font.setBold(true);
    painter.setFont(font);
    painter.scale(1, -1);
    QPointF middle = pointP + (vectorV / 2).toPointF();
    QRectF textRect = QRectF(middle.x() + 0.5, -middle.y() - 0.5, 1, 1);
    painter.drawText(textRect, Qt::AlignLeft | Qt::AlignBottom,
                     QString(name.c_str()));
  }
}
