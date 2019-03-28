#include "glwidget.h"
#include "vector.h"
#include <QDebug>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {

    setFocusPolicy(Qt::StrongFocus);
    mainWindow = NULL;

    // Add Bezier control points
    this->vertices.push_back(Point(100, 300, 0));
    this->vertices.push_back(Point(200, 100, 0));
    this->vertices.push_back(Point(400, 100, 0));
    this->vertices.push_back(Point(500, 300, 0));
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
    if (this->joinControlPoints)
        this->drawControlPolygon(); // show line segments between control points
    if (this->showVertices)
        this->drawVertices(); // show control points
    if (this->showDeCasteljau)
        this->drawDeCasteljau(
                this->deCasteljauParameter); // show deCasteljau's construction
    if (this->showBezier)
        this->drawBezierCurve(); // show Bezier curve

    // call the PPM Image display function
    image.display();

    // flush everything from the draw buffer
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
        this->showVertices = !this->showVertices;
        this->updateGL();
        break;
    case Qt::Key_2:
        this->joinControlPoints = !this->joinControlPoints;
        this->updateGL();
        break;
    case Qt::Key_3:
        this->showDeCasteljau = !this->showDeCasteljau;
        this->updateGL();
        break;
    case Qt::Key_4:
        this->showBezier = !this->showBezier;
        this->updateGL();
        break;

        // backspace/delete keys: remove vertex
    case Qt::Key_Delete:
    case Qt::Key_Backspace:
        if ((vertices.size() < 2) || (selectedVertex == -1))
            return;
        // move remaining vertices backwards in array
        for (int vertexIndex = selectedVertex;
             vertexIndex < ((int)vertices.size()) - 1; vertexIndex++)
            vertices[vertexIndex] = vertices[vertexIndex + 1];
        // delete the one at the end
        vertices.pop_back();
        selectedVertex = -1;
        this->updateGL();
        break;

        // change deCasteljau Parameter
    case Qt::Key_Minus:
        this->deCasteljauParameter -= 0.01;
        if (this->deCasteljauParameter < 0.0)
            this->deCasteljauParameter = 0.0;
        this->updateGL();
        break;
    case Qt::Key_Plus:
        this->deCasteljauParameter += 0.01;
        if (this->deCasteljauParameter > 1.0)
            this->deCasteljauParameter = 1.0;
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

void GLWidget::mousePressEvent(QMouseEvent *event) {
    Point p(event->x(), event->y(), 0);

    // right mouse click to add vertex
    if (event->button() == Qt::RightButton) {
        /*
     * TODO
     */


    }
    // left mouse click to select vertex
    else {
        // reset selection
        this->selectedVertex = -1;
        // search through all vertices
        for (int vertexIndex = 0; vertexIndex < ((int)vertices.size());
             vertexIndex++) {
            Vector vec = this->vertices[vertexIndex] - p;
            if (vec.norm() < 28) { // close enough
                this->selectedVertex = vertexIndex;
                break;
            }
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

// save routines
void GLWidget::saveImage() {
    QString filePath = QDir::homePath() + "/Desktop/comp30020-Lab4.ppm";
    QFile file(filePath);
    file.remove();
    image.writeFile(filePath.toStdString());
}

// and an erase routine
void GLWidget::clearImage() { image.clear(); }

GLWidget::~GLWidget() {
    // Auto-generated destructor stub
}

// draw a disc at vertex location
void GLWidget::drawVertex(Point p, int brushSize, RGBValue color) {
    int size = brushSize * devicePixelRatio() / 2;
    Point vertex = p * devicePixelRatio();
    vertex.y = height - 1 - vertex.y;

    for (int i = -size; i < size; i++) {
        for (int j = -size; j < size; j++) {
            // draw disc
            if (i * i + j * j <= size * size) {
                image.setPixel(vertex[1] + i, vertex[0] + j, color);
            }
        }
    }
}

//	draw all vertices
void GLWidget::drawVertices() {
    for (int vertexIndex = 0; vertexIndex < ((int)vertices.size());
         vertexIndex++) {
        Point p = vertices[vertexIndex];
        if (vertexIndex != selectedVertex) // draw disc
            this->drawVertex(p, 9, RGBValue(80, 80, 80));
        else { // selected: draw circle
            this->drawVertex(p, 17, RGBValue(0, 0, 0));
            this->drawVertex(p, 13, RGBValue(255, 255, 255));
            this->drawVertex(p, 7, RGBValue(0, 0, 0));
        }
    }
}

void GLWidget::drawEdge(Point fromPoint, Point toPoint, RGBValue color) {
    Point pointP = fromPoint;
    Point pointQ = toPoint;
    Vector vec_PQ = (pointQ - pointP);
    float norm_vec_PQ = vec_PQ.norm();    // compute vector length
    float stepDelta = 1.0f / norm_vec_PQ; //	compute parameter step

    for (float t = 0.0f; t <= 1.0f; t += stepDelta) {
        Point p = (pointP + t * vec_PQ) * devicePixelRatio();
        for (int k = 0; k < devicePixelRatio(); k++) {
            for (int l = 0; l < devicePixelRatio(); l++) {
                image.setPixel(height - 1 - p.y - k, p.x + l, color);
            }
        }
    }
}

// draws line segments between control points
void GLWidget::drawControlPolygon() {
    /*
   * TODO
   */

    for(unsigned int i=0; i<vertices.size()-1; i++) {
        drawEdge(vertices[i], vertices[i+1], RGBValue(255, 0, 0));

    }

}

// draws using deCasteljau's algorithm for parameter value t
void GLWidget::drawDeCasteljau(float t) {
    /*
   * TODO
   */

    int N_PTS = vertices.size();
    Point bezPoints[N_PTS][N_PTS];


    for(unsigned int i=0, j=N_PTS-1; i<vertices.size(); i++, j--) {

        bezPoints[i][j] = vertices[i];
    }


    for (int diag = N_PTS-2; diag >= 0; diag--) {
        for (int i = 0; i <= diag; i++) {

            int j = diag - i;

            bezPoints[i][j].x = (1.0-t)*bezPoints[i][j+1].x + t*bezPoints[i+1][j].x;
            bezPoints[i][j].y = (1.0-t)*bezPoints[i][j+1].y + t*bezPoints[i+1][j].y;


            drawEdge(bezPoints[i][j+1], bezPoints[i+1][j], RGBValue(0, 255, 0));

        }

    }

}

// draws the bezier curve
void GLWidget::drawBezierCurve() {
    /*
   * TODO
   */

    int N_PTS = vertices.size();
    Point bezPoints[N_PTS][N_PTS];


    for(int i=0, j=N_PTS-1; i<vertices.size(); i++, j--) {

        bezPoints[i][j] = vertices[i];
    }

    for(float u = 0.0; u <= 1.0; u += 0.001) {
        for (int diag = N_PTS-2; diag >= 0; diag--) {
            for (int i = 0; i <= diag; i++) {

                int j = diag - i;

                bezPoints[i][j].x = (1.0-u)*bezPoints[i][j+1].x + u*bezPoints[i+1][j].x;
                bezPoints[i][j].y = (1.0-u)*bezPoints[i][j+1].y + u*bezPoints[i+1][j].y;



            }
            image.setPixel(height-bezPoints[0][0].y, bezPoints[0][0].x, RGBValue(255, 0, 0));


        }
    }

}
