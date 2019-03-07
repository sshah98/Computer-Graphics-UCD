#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QMainWindow>
#include <QtOpenGL>
#include <vector>

#include "PPMImage.h"
#include "RGBValue.h"
#include "point.h"

class GLWidget : public QGLWidget {
  Q_OBJECT
public:
  GLWidget(QWidget *parent = 0);

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  // load & save routines
  void loadImage();
  void saveImage();

  // clear routine
  void clearImage();

  // paint in image with brush
  void paintAt(int x, int y);

  // utility routine
  void setBrushColour(Byte r, Byte g, Byte b);

  virtual ~GLWidget();

protected:
  void keyPressEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

private:
  QWidget *mainWindow;
  RGBValue brushColour; // current brush colour
  PPMImage image;       // image being drawn
  int brushSize;        // brush size
  int width, height;

private:
  // draws vertices
  void drawVertices();
  void drawVertex(int vertexIndex, int brushSize, bool invertColor);
  // draws edges
  void drawEdges();
  void drawEdge(int fromVertexIndex, int toVertexIndex);
  // fill triangles
  void rasterizeTriangles();
  // barycentric parameter
  float barycentricCoordinate(Point p, int vertexAIndex, int vertexBIndex,
                              int vertexCIndex);

  std::vector<Point> vertices;         // vector of vertices
  std::vector<RGBValue> vertexColours; // vector of vertex colours
  int selectedVertex = 2;              // no vertex selected
  bool showVertices = true;            // draw point at vertices
  bool showEdges = false;              // show edges (wireframe)
  bool fillTriangles = false;          // fill triangles
};

#endif // GLWIDGET_H
