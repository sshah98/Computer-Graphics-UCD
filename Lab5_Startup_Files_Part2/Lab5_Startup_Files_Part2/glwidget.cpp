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

    // read in the textures if we cannot, just exit
    earth_texture.resize(512, 256);
    moon_texture.resize(512, 256);
    if (!earth_texture.readFile(
                (QDir::homePath() + "/Desktop/earth.ppm").toStdString()) ||
            !moon_texture.readFile(
                (QDir::homePath() + "/Desktop/moon.ppm").toStdString())) {
        exit(1);
    }

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
    earth.ambient = isTextured ? RGBValue(32, 32, 32) : RGBValue(0, 0, 255);
    earth.diffuse = isTextured ? earth.specular : earth.ambient;
    earth.emissive = RGBValue(0, 0, 0);
    if (isTextured)
        earth.texture = &earth_texture;
    objects.push_back(earth);
    // Set properties for moon sphere
    Sphere moon = Sphere(Point(1, 1, 6), 0.5);
    moon.specular = RGBValue(255, 255, 255);
    moon.ambient = isTextured ? RGBValue(64, 64, 64) : RGBValue(128, 128, 128);
    moon.diffuse = isTextured ? moon.specular : moon.ambient;
    moon.emissive = RGBValue(0, 0, 0);
    if (isTextured)
        moon.texture = &moon_texture;
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
    case Qt::Key_4:
        this->useShadow = !this->useShadow;
        this->updateGL();
        break;
        // save PPM image
    case Qt::Key_S:
        this->saveImage();
        break;
    case Qt::Key_T:
        this->isTextured = !this->isTextured;
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
    Vector cameraVec =
            Vector(camera_position.x, camera_position.y, camera_position.z);

    for (int pixel_x = 0; pixel_x < width; ++pixel_x) {
        for (int pixel_y = 0; pixel_y < height; ++pixel_y) {
            /*
       * TO DO:
       * generate the ray from the camera,
       */
            ray = upper_left + (pixel_x * x_step) + (pixel_y * y_step);
            ray = ray - cameraVec;
            ray = ray.normal();

            // check if the ray intersects any objects
            if (!hitTest(camera_position, ray, objects))
                continue;

            // as we know that at least one object intersects, figure out which one
            // is the closest to the camera
            closest = closestIntersect(camera_position, ray, objects);

            // generate the intersection point and normal
            intersection = objects[closest].intersectionPoint(camera_position, ray);
            normal = objects[closest].normal(intersection).normal();
            // figure out the contribution of each light source to this ray and set
            // the colour when done
            overall_colour = intersectionColour(closest, intersection, ray, normal,
                                                objects, lights);

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
    // Calculate the bisector
    Vector bisector = (light_direction - ray) * 0.5;

    // Caclulate the intensity
    float intensity = normal.dot(bisector) / (bisector.norm() * normal.norm());

    // if the intensity is less than zero then return black
    if (intensity < 0.f) {
        return RGBValue(0, 0, 0);
    }

    // modulate the specular components
    RGBValue colour = object.specular.modulate(light.specular);

    // raise the intensity to the power of shininess before applying it to the
    // modulated colour
    intensity = pow(intensity, (float)object.shininess);

    return colour * intensity;
}

RGBValue GLWidget::computeDiffuse(Sphere &object, Point &intersection,
                                  Vector &normal, Vector &light_direction,
                                  Light &light) {
    // computed diffuse and texture colour
    RGBValue diffuse_colour;
    RGBValue tex_colour;

    // compute the intensity of the light through the dot
    // product of the light and normal
    float intensity = normal.dot(light_direction);

    // if the intensity is less than zero set the colour to zero
    if (intensity < 0.f) {
        return RGBValue(0, 0, 0);
    }

    /*
   * TO DO
   * Add texturing
   *  - get colour of texture at point of intersection
   *  - use that colour instead of the object's solid colour
   */

    tex_colour = object.getTexColour(intersection);

    diffuse_colour = object.diffuse.modulate(light.diffuse);

    // return the computed colour
    return diffuse_colour.modulate(tex_colour) * intensity;
}

RGBValue GLWidget::computeAmbient(Sphere &object, Light &source) {
    return object.ambient.modulate(source.ambient);
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
    bool isShadowed = false;

    for (unsigned int lightIndex = 0; lightIndex < lightSources.size();
         lightIndex++) {
        // compute direction to light source
        light_direction =
                lightSources[lightIndex].directionFromPoint(intersection).normal();

        // test if point is shadowed
        isShadowed = this->isShadowed(sphereIndex, intersection, light_direction,
                                      lightSources[lightIndex], objects);

        // compute the contribution of this light
        if (!isShadowed || !useShadow) {
            if (showSpecular) {
                overall_colour +=
                        computeSpecular(objects[sphereIndex], normal, light_direction,
                                        lightSources[lightIndex], ray);
            }
            if (showDiffuse) {
                overall_colour +=
                        computeDiffuse(objects[sphereIndex], intersection, normal,
                                       light_direction, lightSources[lightIndex]);
            }
            if (showAmbient) {
                overall_colour +=
                        computeAmbient(objects[sphereIndex], lightSources[lightIndex]);
            }
        }
        if (showAmbient) {
            overall_colour +=
                    computeAmbient(objects[sphereIndex], lightSources[lightIndex]);
        }
    }
    // return the overall colour
    return overall_colour;
}

bool GLWidget::isShadowed(unsigned int sphereIndex, Point &intersection,
                          Vector &light_direction, Light &source,
                          std::vector<Sphere> &objects) {
    // is this shadowed
    bool isShadowed = false;

    /*
   * TO DO
   *
   */
    for(unsigned int i=0; i<objects.size(); i++) {
        if(i != sphereIndex && objects[i].hitTest(intersection, light_direction)) {
            isShadowed = true;
        }
    }
    return isShadowed;

}
