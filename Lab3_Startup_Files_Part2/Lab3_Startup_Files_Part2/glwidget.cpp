#include "glwidget.h"
#include "vector.h"
#include <QDebug>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>     // std::distance


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {

    setFocusPolicy(Qt::StrongFocus);
    mainWindow = NULL;
    brushSize = 11;
    this->setBrushColour(0, 0, 0);

    // Add 2 triangles
    this->vertices.push_back(Point(50, 100, 0));
    this->vertices.push_back(Point(100, 300, 0));
    this->vertices.push_back(Point(200, 200, 0));

    this->vertices.push_back(Point(350, 100, 0));
    this->vertices.push_back(Point(550, 200, 0));
    this->vertices.push_back(Point(300, 250, 0));

    this->vertexColours.push_back(RGBValue(255, 0, 0));
    this->vertexColours.push_back(RGBValue(0, 255, 0));
    this->vertexColours.push_back(RGBValue(0, 0, 255));

    this->vertexColours.push_back(RGBValue(255, 255, 0));
    this->vertexColours.push_back(RGBValue(255, 0, 255));
    this->vertexColours.push_back(RGBValue(0, 255, 255));
}

void GLWidget::setBrushColour(Byte r, Byte g, Byte b) {
    brushColour[0] = r;
    brushColour[1] = g;
    brushColour[2] = b;
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

    // start by clearing the image
    this->clearImage();
    // call subroutines to do the actual drawing
    if (fillTriangles)
        this->rasterizeTriangles();
    if (showEdges)
        this->drawEdges();
    if (showVertices)
        this->drawVertices();

    // call the PPM Image display function
    image.display();

    // flush everything from the draw buffer to be displayed
    glFlush();
}

void GLWidget::resizeGL(int w, int h) {
    width = w;
    height = h;
    image.resize(width, height);

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

        // save PPM image
    case Qt::Key_S:
        this->saveImage();
        break;
    case Qt::Key_E:
        this->clearImage();
        this->updateGL();
        break;

        // drawing modes
    case Qt::Key_1:
        /*
     * TO DO
     * toggle vertex drawing
     */
        if(showVertices == true) {
            showVertices = false;
        }
        else {
            showVertices = true;
        }
        this->updateGL();
        break;
    case Qt::Key_2:
        /*
     * TO DO
     * toggles edge drawing
     */
        if(showEdges == true) {
            showEdges = false;
        }
        else {
            showEdges = true;
        }
        this->updateGL();
        break;
    case Qt::Key_3:
        /*
     * TO DO
     * toggles triangle drawing
     */
        if(fillTriangles == true) {
            fillTriangles = false;
        }
        else {
            fillTriangles = true;
        }
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

void GLWidget::paintAt(int x, int y) {
    for (int i = 0; i <= brushSize; i++) {
        for (int j = 0; j <= brushSize; j++) {
            if ((i * i + j * j) <= (brushSize * brushSize)) {
                image.setPixel(x + i, y + j, brushColour);
            }
        }
    }
    this->updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    Point p(event->x(), event->y(), 0);

    // reset selection
    selectedVertex = -1;

    /*
   * TO DO
   *
   * Mouse-down near (within 8 pixels) of a vertex
   * should select and highlight this vertex
   *
   */

    for(unsigned int i=0; i<vertices.size(); i++) {
        if(sqrt(pow(vertices[i].x-p.x, 2) + pow(vertices[i].y-p.y, 2)) <= 8) {
            selectedVertex = i;
        }
    }

    this->updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    Point p(event->x(), event->y(), 0);

    if (selectedVertex != -1) {
        vertices[selectedVertex] = p;
        this->updateGL();
    }
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
   * Load and resize the main window to the new image width and height (+the
   * margins)
   * You will need to figure out the margins.
   * Try printing out the main window and image widths and heights
   * before and after loading the image/doing the resize
   */

    image.readFile(filePath);
    QSize margin = mainWindow->size() - this->size();
    QSize windowSize = QSize(image.width() / devicePixelRatio(),
                             image.height() / devicePixelRatio()) +
            margin;
    mainWindow->resize(windowSize);

    this->updateGL();
}

void GLWidget::saveImage() {
    QString filePath = QDir::homePath() + "/Desktop/comp30020-Lab3.ppm";
    QFile file(filePath);
    file.remove();
    image.writeFile(filePath.toStdString());
}

// and an erase routine
void GLWidget::clearImage() { image.clear(); }

GLWidget::~GLWidget() {
    // Auto-generated destructor stub
}

// draw a disc at vertex locatopm
void GLWidget::drawVertex(int vertexIndex, int brushSize, bool invertColor) {
    int size = brushSize * devicePixelRatio() / 2;
    Point vertex = vertices[vertexIndex] * devicePixelRatio();
    vertex.y = height - 1 - vertex.y;

    for (int i = -size; i < size; i++) {
        for (int j = -size; j < size; j++) {
            // draw disc
            if (i * i + j * j <= size * size) {
                if (vertexIndex == selectedVertex && invertColor) {
                    image.setPixel(vertex[1] + i, vertex[0] + j, RGBValue(255, 255, 255));
                } else {
                    image.setPixel(vertex[1] + i, vertex[0] + j,
                            vertexColours[vertexIndex]);
                }
            }
        }
    }
}

//	draw all vertices
void GLWidget::drawVertices() {
    for (int vertexIndex = 0; vertexIndex < ((int)vertices.size());
         vertexIndex++) {
        if (vertexIndex != selectedVertex) // draw disc
            this->drawVertex(vertexIndex, 9, false);
        else { // selected: draw circle
            this->drawVertex(vertexIndex, 17, false);
            this->drawVertex(vertexIndex, 13, true);
            this->drawVertex(vertexIndex, 7, false);
        }
    }
}

void GLWidget::drawEdge(int fromVertexIndex, int toVertexIndex) {
    /*
   * TO DO
   * draw an edge of a triangle using the parametric method.
   * Edges are vectors. You can figure these out from the vertices
   * of the triangles which are points.
   *
   * 1. Draw the edges in black.
   * 2. Interpolate the colour between vertices linearly.
   */
    Point p = vertices[fromVertexIndex];
    Point q = vertices[toVertexIndex];

    RGBValue colour_p = vertexColours[fromVertexIndex];
    RGBValue colour_q = vertexColours[toVertexIndex];

    for (float t = 0.0; t <= 1.0; t += 0.001) {
        Point r = p + (q - p) * t;
        brushColour = colour_p + (colour_q - colour_p) * t;

        image.setPixel(this->height - round(r.y), round(r.x), brushColour);

    }

}

//	draw all triangle edges
void GLWidget::drawEdges() {
    this->drawEdge(0, 1);
    this->drawEdge(1, 2);
    this->drawEdge(2, 0);

    this->drawEdge(3, 4);
    this->drawEdge(4, 5);
    this->drawEdge(5, 3);
}

// Barycentric coordinate
float GLWidget::barycentricCoordinate(Point p, int vertexAIndex,
                                      int vertexBIndex, int vertexCIndex) {
    Vector vec_BA = vertices[vertexAIndex] * devicePixelRatio() -
            vertices[vertexBIndex] * devicePixelRatio();
    Vector normal_vec_BA = Vector(-vec_BA.dy, vec_BA.dx, 0);
    Vector vec_AC = vertices[vertexCIndex] * devicePixelRatio() -
            vertices[vertexAIndex] * devicePixelRatio();
    Vector vec_AP = p - vertices[vertexAIndex] * devicePixelRatio();
    return vec_AP.dot(normal_vec_BA) / vec_AC.dot(normal_vec_BA);
}

// fill triangles
void GLWidget::rasterizeTriangles() {
    /*
   * TO DO
   * Draw a filled triangle using the algorithms
   * discussed in lectures (i.e. Barycentric coordinates method).
   *
   * 1. Draw the triangle in black.
   * 2. Interpolate the colour between vertices using
   * barycentric interpolation.
   *
   */

    // add two variables to get the minimum of triangle and max of triangle - the rightmost and bottommost of a square to get the points

    for(unsigned x=0; x<vertices.size(); x++) {
        for(unsigned y=0; y<vertices.size(); y++) {

            Point p = vertices[x];

            float alpha = barycentricCoordinate(p, 0, 1, 2);
            float beta = barycentricCoordinate(p, 1, 2, 0);
            float gamma = barycentricCoordinate(p, 2, 0, 1);

            if ((alpha < 0.0) || (beta < 0.0) || (gamma < 0.0)) {
                continue;
            }
            brushColour = alpha * vertexColours[0] + beta * vertexColours[1] + gamma * vertexColours[2];
            image.setPixel(x, y, brushColour);

        }

    }

}
