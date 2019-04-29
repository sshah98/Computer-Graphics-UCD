QT       += core gui opengl

TARGET = Lab6
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    glwidget.cpp \
    objects.cpp \
    point.cpp \
    vector.cpp \
    quat.cpp \
    arcball.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    objects.h \
    point.h \
    vector.h \
    quat.h \
    arcball.h

FORMS    += mainwindow.ui

mac: LIBS += -framework GLUT

unix:!macx:!symbian: LIBS += -lGL -lglut
