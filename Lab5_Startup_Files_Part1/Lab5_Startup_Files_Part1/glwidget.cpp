#include "glwidget.h"
#include "sphere.h"
#include "vector.h"
#include <QDebug>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    mainWindow = NULL;

    // Create Camera
    camera_position = Point(0, 0, 10);
    camera_forward = Vector(0, 0, -1);
    camera_up = Vector(0, 1, 0);
    camera_left = camera_up.cross(camera_forward);

    // Set the distance of the image plane along with its width and height
    plane_distance = 1;
    plane_width = 2;

    // Setup the camera
    this->setupCamera();

    // Setup a white light source
    Light source = Light(Point(3, 3, 9));
    source.specular = RGBValue(255, 255, 255);
    source.diffuse = RGBValue(255, 255, 255);
    source.ambient = RGBValue(64, 64, 64);
    lights.push_back(source);

    // Set properties for earth sphere
    Sphere earth = Sphere(Point(0, 0, 0), 3);
    earth.specular = RGBValue(255, 255, 255);
    earth.ambient = RGBValue(0, 0, 255);
    earth.diffuse = earth.ambient;
    earth.emissive = RGBValue(0, 0, 0);
    objects.push_back(earth);

    // Set properties for moon sphere
    Sphere moon = Sphere(Point(1, 1, 6), 0.5);
    moon.specular = RGBValue(255, 255, 255);
    moon.ambient = RGBValue(128, 128, 128);
    moon.diffuse = moon.ambient;
    moon.emissive = RGBValue(0, 0, 0);
    objects.push_back(moon);
}

void GLWidget::initializeGL() {
    // default behaviour clears the buffer
    glClearColor(1.0, 1.0, 1.0, 1.0); // set the colour of the canvas
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWidget::paintGL() {
    // set the canvas colour and clear the buffer
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // setup modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRasterPos2i(0, 0);

    // do the raytracing
    raytrace();

    // draw the image
    renderImage.display();

    // flush everything from the draw buffer
    glFlush();
}

void GLWidget::resizeGL(int w, int h) {
    // resize the PPM image to the new width and height
    width = w;
    height = h;
    renderImage.resize(width, height);

    // setup the camera
    setupCamera();

    // Set all pixels to black
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            renderImage.setPixel(y, x, 0, 0, 0, 1);
        }
    }

    // Set standard 2D set of coordinates
    glMatrixMode(GL_PROJECTION);         // switch to proj. mat.
    glLoadIdentity();                    // set to identity
    glOrtho(0, width, 0, height, -1, 1); // with orthog proj
    glViewport(0, 0, width, height);     // set the viewport
    glMatrixMode(GL_MODELVIEW);          // switch to MV mat.
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    // Phong lighting model components
    case Qt::Key_1:
        this->showSpecular = !this->showSpecular;
        this->updateGL();
        break;
    case Qt::Key_2:
        this->showDiffuse = !this->showDiffuse;
        this->updateGL();
        break;
    case Qt::Key_3:
        this->showAmbient = !this->showAmbient;
        this->updateGL();
        break;
        // save PPM image
    case Qt::Key_S:
        this->saveImage();
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

GLWidget::~GLWidget() {
    // Auto-generated destructor stub
}

// save routines
void GLWidget::saveImage() {
    QString filePath = QDir::homePath() + "/Desktop/comp30020-Lab5.ppm";
    QFile file(filePath);
    file.remove();
    renderImage.writeFile(filePath.toStdString());
}

void GLWidget::raytrace(void) {
    // generate a ray for each pixel in the image and see where it goes
    Vector ray;
    RGBValue overall_colour;
    unsigned int closest;
    Vector normal;
    Vector light_direction;
    Point intersection;
    Vector cameraVec = Vector(camera_position.x, camera_position.y, camera_position.z);


    for (int pixel_x = 0; pixel_x < width; ++pixel_x) {
        for (int pixel_y = 0; pixel_y < height; ++pixel_y) {
               /*
                * TO DO:
                * generate the ray from the camera,
                */

            Vector pixelCentre = upper_left + pixel_x * x_step + pixel_y * y_step;
            ray = (pixelCentre - cameraVec).normal();

            // check if the ray intersects any objects
            if (!hitTest(camera_position, ray, objects))
                continue;

            // as we know that at least one object intersects, figure out which one
            // is the closest to the camera
            closest = closestIntersect(camera_position, ray, objects);

            /*
       * TO DO:
       * compute colour properties
       */

            intersection = objects[closest].intersectionPoint(camera_position, ray);
            normal = objects[closest].normal(intersection);

            overall_colour = intersectionColour(closest, intersection, ray, normal, objects, lights);

            renderImage.setPixel(height - pixel_y, pixel_x, overall_colour, 255);
        }
    }
}

void GLWidget::setupCamera(void) {

    plane_height = plane_width * ((float)height / width);

    // figure out where the upper left position of the plane is
    Vector start_pos(camera_position.x, camera_position.y, camera_position.z);
    upper_left = start_pos + (plane_distance * camera_forward);
    upper_left = upper_left + ((plane_width * 0.5) * camera_left);
    upper_left = upper_left + ((plane_height * 0.5) * camera_up);

    // figure out the stepping in the x and y directions
    x_step = Vector(-camera_left.dx, -camera_left.dy, -camera_left.dz).normal();
    y_step = Vector(-camera_up.dx, -camera_up.dy, -camera_up.dz).normal();
    x_step = x_step * (plane_width / width);
    y_step = y_step * (plane_height / height);
}

RGBValue GLWidget::computeSpecular(Sphere &object, Vector &normal,
                                   Vector &light_direction, Light &light,
                                   Vector &ray) {
    /*
   * TO DO
   * See class handouts
   */
    Vector vb = (light_direction - ray) * 0.5;
    float cos_theta = (normal.dot(vb)) / (normal.norm() * vb.norm());

    if(cos_theta > 0) {
        return object.specular.modulate(light.specular) * pow(cos_theta, object.shininess);
    }

    return RGBValue(0,0,0);

}

RGBValue GLWidget::computeDiffuse(Sphere &object, Vector &normal,
                                  Vector &light_direction, Light &light) {
    /*
   * TO DO
   * See class handouts
   */
    float cos_theta = normal.dot(light_direction) / (normal.norm() * light_direction.norm());
    if(cos_theta > 0) {
        return object.diffuse.modulate(light.diffuse) * cos_theta;
    }

    return RGBValue(0,0,0);
}

RGBValue GLWidget::computeAmbient(Sphere &object, Light &light) {
    /*
   * TO DO
   * See class handouts
   */
    return object.ambient.modulate(light.ambient);
}

bool GLWidget::hitTest(Point &camera_position, Vector &ray,
                       std::vector<Sphere> &objects) {

    // if the ray intersects a single object return true, otherwise return false
    for (unsigned int count = 0; count < objects.size(); ++count) {
        if (objects[count].hitTest(camera_position, ray)) {
            return true;
        }
    }
    return false;
}

unsigned int GLWidget::closestIntersect(Point &camera_position, Vector &ray,
                                        std::vector<Sphere> &objects) {

    // the distance of the nearest intersection point
    float distance;
    // loop control variable
    unsigned int count = 0;
    // point of intersection
    Point intersection;
    // temporary vector for computing distance
    Vector temp;
    // temp point for new intersection
    Point new_intersect;
    // distance of new intersection
    float new_distance;
    // object which is closest
    unsigned int closest;

    // find the first intersection point and set its distance
    for (count = 0; count < objects.size(); ++count) {
        if (objects[count].hitTest(camera_position, ray)) {
            intersection = objects[count].intersectionPoint(camera_position, ray);
            temp = intersection - camera_position;
            distance = temp.norm();
            closest = count;
            break;
        }
    }

    // now search through all other objects for intersection
    // if there is another intersection
    // and its closer update the closest point
    for (; count < objects.size(); ++count) {
        if (objects[count].hitTest(camera_position, ray)) {
            new_intersect = objects[count].intersectionPoint(camera_position, ray);
            temp = new_intersect - camera_position;
            new_distance = temp.norm();
            if (new_distance < distance) {
                distance = new_distance;
                intersection = new_intersect;
                closest = count;
            }
        }
    }

    // return the point of intersection
    return closest;
}

RGBValue GLWidget::intersectionColour(unsigned int sphereIndex,
                                      Point &intersection, Vector &ray,
                                      Vector &normal,
                                      std::vector<Sphere> &objects,
                                      std::vector<Light> lightSources) {

    // go through each light source and calculate the
    // total contribution of that light
    RGBValue overall_colour(0, 0, 0);
    Vector light_direction;
    for (unsigned int count = 0; count < lightSources.size(); count++) {
        light_direction =
                lightSources[count].directionFromPoint(intersection).normal();
        if (showSpecular) {
            overall_colour +=
                    computeSpecular(objects[sphereIndex], normal, light_direction,
                                    lightSources[count], ray);
        }
        if (showDiffuse) {
            overall_colour += computeDiffuse(objects[sphereIndex], normal,
                                             light_direction, lightSources[count]);
        }
        if (showAmbient) {
            overall_colour +=
                    computeAmbient(objects[sphereIndex], lightSources[count]);
        }
    }

    // return the overall colour
    return overall_colour;
}
