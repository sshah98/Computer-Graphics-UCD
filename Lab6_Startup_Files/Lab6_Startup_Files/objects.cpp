#include "objects.h"
#include "point.h"
#include "vector.h"
#include <cmath>

const double pi = 3.1416;

void drawTetrahedron() {
    /*
   * TODO
   * Draw a tetrahedron centered at the origin using GL_TRIANGLES
   * Compute and set normal vectors for each triangle to ensure proper shading
   */

    glBegin(GL_TRIANGLES);

    //front triangle
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);

    Point p = Point(-1, -1, -1);
    Point q = Point(1, -1, 1);
    Point r = Point(-1, 1, 1);

    Vector u = q - p;
    Vector v = r - p;
    Vector n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    //right side triangle
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    p = Point(-1, -1, -1);
    q = Point(1, 1, -1);
    r = Point(-1, 1, 1);

    u = q - p;
    v = r - p;
    n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    //left side triangle
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);


    p = Point(1, 1, -1);
    q = Point(-1, -1, -1);
    r = Point(1, -1, 1);

    u = q - p;
    v = r - p;
    n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    //bottom triangle
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f,  1.0f, -1.0f);

    p = Point(1, -1, 1);
    q = Point(-1, 1, 1);
    r = Point(1, 1, -1);

    u = q - p;
    v = r - p;
    n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    glEnd();


}

void drawCube() {
    /*
   * TODO
   * Draw a cube centered at the origin using GL_QUADS
   * Compute and set normal vectors for each rectangle to ensure proper shading
   * Set texture coordinates
   */

    glBegin(GL_QUADS);

    // Top face (y = 1.0f)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);

    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    Point p = Point(1, 1, -1);
    Point q = Point(-1, 1, -1);
    Point r = Point(-1, 1, 1);

    Vector u = q - p;
    Vector v = r - p;
    Vector n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    // Front face  (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);

    p = Point(1, 1, 1);
    q = Point(-1, 1, 1);
    r = Point(-1, -1, 1);

    u = q - p;
    v = r - p;
    n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    // Back face (z = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    p = Point(1, -1, -1);
    q = Point(-1, -1, -1);
    r = Point(-1, 1, -1);

    u = q - p;
    v = r - p;
    n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    // Left face (x = -1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    p = Point(-1, 1, 1);
    q = Point(-1, 1, -1);
    r = Point(-1, -1, -1);

    u = q - p;
    v = r - p;
    n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);


    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    p = Point(1, 1, -1);
    q = Point(1, 1, 1);
    r = Point(1, -1, 1);

    u = q - p;
    v = r - p;
    n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    glEnd();

}

void drawOctahedron() {
    /*
   * TODO
   * Draw an octahedron centered at the origin using GL_TRIANGLES
   * Compute and set normal vectors for each triangle to ensure proper shading
   */

    glBegin(GL_TRIANGLES);

    //front triangle
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);

    Point p = Point(-1, -1, -1);
    Point q = Point(1, -1, 1);
    Point r = Point(-1, 1, 1);

    Vector u = q - p;
    Vector v = r - p;
    Vector n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    //right side triangle
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    p = Point(-1, -1, -1);
    q = Point(1, 1, -1);
    r = Point(-1, 1, 1);

    u = q - p;
    v = r - p;
    n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    //left side triangle
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);


    p = Point(1, 1, -1);
    q = Point(-1, -1, -1);
    r = Point(1, -1, 1);

    u = q - p;
    v = r - p;
    n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    //bottom triangle
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f,  1.0f, -1.0f);

    p = Point(1, -1, 1);
    q = Point(-1, 1, 1);
    r = Point(1, 1, -1);

    u = q - p;
    v = r - p;
    n = u.cross(v).normalised();

    glNormal3f(n.dx, n.dy, n.dz);

    glEnd();


}

void drawCylinder(float radius, float height, int nSegments) {
    /*
   * TODO
   * Draw cylinder centered at the origin using GL_TRIANGLES
   * Compute and set normal vectors for each vertex to ensure smooth shading
   */

    glBegin(GL_TRIANGLES);

    for (float i = 0; i < nSegments; i++) {

        // a loop a circumference
        float angle = (pi * i * 2) / nSegments;
        float nextAngle = pi * (i + 1) * 2 / nSegments;
        float x1 = sin(angle) * radius, y1 = cos(angle)*radius;
        float x2 = sin(nextAngle)*radius, y2 = cos(nextAngle)*radius;

        // draw top (green) triangle
        glNormal3f(x1,y1,0);
        glNormal3f(x2,y2,0);
        glNormal3f(x1,y1,0);

        glVertex3f(x1,y1,0);
        glVertex3f(x2,y2,height);
        glVertex3f(x1,y1,height);

        // draw bottom (red) triangle
        glNormal3f(x1,y1,0);
        glNormal3f(x2,y2,0);
        glNormal3f(x2,y2,0);

        glVertex3f(x1,y1,0);
        glVertex3f(x2,y2,0);
        glVertex3f(x2,y2,height);


        // right triangle
        glNormal3f(x1,y1,0);
        glNormal3f(x2,y2,height);
        glNormal3f(x2,y2,height);

        glVertex3f(x1,y1,0);
        glVertex3f(x2,y2,height);
        glVertex3f(x2,y2,height);

        // left triangle
        glNormal3f(x1,y1,0);
        glNormal3f(x2,y2,0);
        glNormal3f(x2,y2,height);

        glVertex3f(x1,y1,0);
        glVertex3f(x2,y2,0);
        glVertex3f(x2,y2,height);

        //circle
        glVertex3f(0,0,0);
        glVertex3f(x1,y1,0);
        glVertex3f(x2,y2,0);

        glVertex3f(0,0,height);
        glVertex3f(x1,y1,height);
        glVertex3f(x2,y2,height);



    }

    glEnd();



}

void drawSphere(float radius, int nSegments, int nSlices) {
    /*
   * TODO
   * Draw sphere centered at the origin using GL_QUADS
   * Compute and set normal vectors for each vertex to ensure proper shading
   * Set texture coordinates
   */

    for (float i = 0.0; i < nSlices; i += 1.0) {
        float lat0 = pi * (((i) / nSlices) - 0.5);
        float z0 = sin(lat0)*radius;
        float zr0 = cos(lat0)*radius;

        float lat1 = pi * (((i+1) / nSlices) - 0.5);
        float z1 = sin(lat1)*radius;
        float zr1 = cos(lat1)*radius;

        glBegin(GL_QUADS);

        for (float j = 0.0; j < nSegments; j += 1.0) {
            float long0 = 2 * pi * ((j) / nSegments);
            float x0 = cos(long0);
            float y0 = sin(long0);

            float long1 = 2 * pi * ((j+1) / nSegments);
            float x1 = cos(long1);
            float y1 = sin(long1);

            glVertex3f(x1 * zr0, y1 * zr0, z0);
            glNormal3f(x1 * zr0, y1 * zr0, z0);

            glVertex3f(x0 * zr0, y0 * zr0, z0);
            glNormal3f(x0 * zr0, y0 * zr0, z0);

            glVertex3f(x0 * zr1, y0 * zr1, z1);
            glNormal3f(x0 * zr1, y0 * zr1, z1);

            glVertex3f(x1 * zr1, y1 * zr1, z1);
            glNormal3f(x1 * zr1, y1 * zr1, z1);

        }

        glEnd();
    }

}
