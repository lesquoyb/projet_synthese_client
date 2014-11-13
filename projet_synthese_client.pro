#-------------------------------------------------
#
# Project created by QtCreator 2014-10-18T19:09:45
#
#-------------------------------------------------

QT       += core gui\
            testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet_synthese_client
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += src/formegeom.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    tests/testcouleurs.cpp \
    src/point.cpp \
    src/vecteur.cpp \
    src/Couleur.cpp \
    src/groupe.cpp \
    tests/testgroupe.cpp \
    src/segment.cpp \
    tests/testsegment.cpp \
    src/cercle.cpp \
    src/triangle.cpp \
    tests/testtriangle.cpp \
    src/polygone.cpp \
    src/dessinManager.cpp \
    src/erreur.cpp \
    src/tools.cpp

HEADERS  += src/Couleur.h \
    src/formegeom.h \
    src/mainwindow.h \
    tests/testcouleurs.h \
    src/angle.h \
    src/point.h \
    src/vecteur.h \
    exceptions/exceptioncouleurinexistante.h \
    src/groupe.h \
    tests/testgroupe.h \
    src/segment.h \
    tests/testsegment.h \
    src/cercle.h \
    src/Tools.h \
    src/triangle.h \
    tests/testtriangle.h \
    src/polygone.h \
    src/dessinManager.h \
    src/erreur.h \
    src/dessinable.h

FORMS    += src/mainwindow.ui

OTHER_FILES += \
    contraintes.ods \
    technos.txt
