QT       += core gui opengl

TARGET = Lab3
TEMPLATE = app

SOURCES += main.cpp\
    mainwindow.cpp \
    glwidget.cpp \
    PPMImage.cpp \
    RGBValue.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    PPMImage.h \
    RGBValue.h

FORMS += \
    mainwindow.ui

mac: LIBS += -framework GLUT

unix:!macx:!symbian: LIBS += -lGL -lglut

RESOURCES += \
    resources.qrc
