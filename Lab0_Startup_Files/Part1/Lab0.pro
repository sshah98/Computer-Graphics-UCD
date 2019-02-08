QT       += core gui opengl

TARGET = Lab0
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui

mac: LIBS += -framework GLUT

unix:!macx:!symbian: LIBS += -lGL -lglut
