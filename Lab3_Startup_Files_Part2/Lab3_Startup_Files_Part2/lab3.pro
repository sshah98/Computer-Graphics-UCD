QT       += core gui opengl

TARGET = Lab3
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    glwidget.cpp \
    PPMImage.cpp \
    RGBValue.cpp \
    point.cpp \
    vector.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    PPMImage.h \
    RGBValue.h \
    point.h \
    vector.h

FORMS += \
    mainwindow.ui

mac: LIBS += -framework GLUT

unix:!macx:!symbian: LIBS += -lGL -lglut

RESOURCES += \
    resources.qrc
