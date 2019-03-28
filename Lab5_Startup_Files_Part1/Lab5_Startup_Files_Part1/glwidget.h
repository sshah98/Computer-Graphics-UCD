#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QMainWindow>
#include <QtOpenGL>
#include <vector>

#include "PPMImage.h"
#include "RGBValue.h"
#include "light.h"
#include "point.h"
#include "sphere.h"
#include "vector.h"

class GLWidget : public QGLWidget {
  Q_OBJECT
public:
  GLWidget(QWidget *parent = 0);

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  virtual ~GLWidget();

protected:
  void keyPressEvent(QKeyEvent *event);
  bool showSpecular = true;
  bool showDiffuse = true;
  bool showAmbient = true;

private:
  QWidget *mainWindow;

  // PPM image to render raytracing
  PPMImage renderImage;
  int width, height;
  void saveImage();

private: // Object models, lights, image plane and camera
  // vectors of spheres and light sources that make up our scene
  std::vector<Sphere> objects;
  std::vector<Light> lights;
  // position of the camera, along with its forward, up and left directions
  Point camera_position;
  Vector camera_forward;
  Vector camera_up;
  Vector camera_left;
  // size of image plane and its distance from camera
  float plane_distance;
  float plane_width;
  float plane_height;
  // amount to step by in x and y direction along image plane
  Vector x_step;
  Vector y_step;
  // upper left corner image plane
  Vector upper_left;

private:
  // function that does the raytracing
  void raytrace(void);
  // helper function to setup all the information needed to generate rays
  void setupCamera(void);

  // Given a sphere, a light, a light direction, and a normal,
  // computes specular component
  RGBValue computeSpecular(Sphere &object, Vector &normal,
                           Vector &light_direction, Light &light, Vector &ray);
  // Given a sphere, a light, a light direction, and a normal,
  // computes diffuse component
  RGBValue computeDiffuse(Sphere &object, Vector &normal,
                          Vector &light_direction, Light &light);
  // computes ambient component
  RGBValue computeAmbient(Sphere &object, Light &light);

  // determines if ray intersect some object(s) in the scene
  bool hitTest(Point &camera_position, Vector &ray,
               std::vector<Sphere> &objects);
  // returns sphere index back the sphere with the point of closest intersection
  unsigned int closestIntersect(Point &camera_position, Vector &ray,
                                std::vector<Sphere> &objects);
  // computes the colour of this intersection point
  RGBValue intersectionColour(unsigned int sphereIndex, Point &intersection,
                              Vector &ray, Vector &normal,
                              std::vector<Sphere> &objects,
                              std::vector<Light> lights);
};

#endif // GLWIDGET_H
