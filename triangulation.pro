#-------------------------------------------------
#
# Project created by QtCreator 2017-05-31T21:31:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = triangulation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    window.cpp \
    glwidget.cpp \
    logo.cpp \
    mesh.cpp \
    vertex.cpp \
    triangle.cpp \
    gltriangulationwidget.cpp \
    shape.cpp \
    offreader.cpp \
    offwriter.cpp

HEADERS  += mainwindow.h \
    window.h \
    glwidget.h \
    logo.h \
    mesh.h \
    triangle.h \
    vertex.h \
    simplemesh_global.h \
    gltriangulationwidget.h \
    shape.h \
    offreader.h \
    offwriter.h

FORMS    += mainwindow.ui
