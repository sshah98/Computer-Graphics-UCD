#ifndef _OBJECTS_H
#define _OBJECTS_H

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// routines for drawing geometric primitives :  platonic solids
void drawTetrahedron();
void drawCube();
void drawOctahedron();
void drawDodecahedron();
void drawIcosahedron();

void drawSphere(float radius, int nSegments, int nSlices);
void drawCylinder(float radius, float height, int nSegments);

#endif // _OBJECTS_H
