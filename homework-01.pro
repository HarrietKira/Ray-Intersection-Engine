QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++1z
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    intersection.cpp \
    main.cpp \
    mainwindow.cpp \
    primitive.cpp \
    ray.cpp \
    scene.cpp \
    shape.cpp \
    sphere.cpp \
    squareplane.cpp \
    transform.cpp

HEADERS += \
    camera.h \
    globalincludes.h \
    intersection.h \
    mainwindow.h \
    primitive.h \
    ray.h \
    scene.h \
    shape.h \
    sphere.h \
    squareplane.h \
    transform.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

