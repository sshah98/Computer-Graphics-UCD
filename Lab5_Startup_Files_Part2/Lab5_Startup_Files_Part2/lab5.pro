QT       += core gui opengl

TARGET = Lab5
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    glwidget.cpp \
    PPMImage.cpp \
    RGBValue.cpp \
    point.cpp \
    vector.cpp \
    light.cpp \
    sphere.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    PPMImage.h \
    RGBValue.h \
    point.h \
    vector.h \
    light.h \
    sphere.h

FORMS += \
    mainwindow.ui

mac: LIBS += -framework GLUT

unix:!macx:!symbian: LIBS += -lGL -lglut

RESOURCES += \
    resources.qrc