# #####################################################################
# Automatically generated by qmake (2.01a) Fri Dec 25 20:37:53 2009
# #####################################################################
TEMPLATE = app
TARGET = steps
DEPENDPATH += .
INCLUDEPATH += .
QT += network core gui widgets sql
LIBS += -lGeographic

CONFIG += debug

# Input
HEADERS += mainwindow.h \
    mapview.h \
    mgmreader.h \
    geotools.h \
    tile.h \
    tilelayer.h \
    mainscene.h \
    constants.h \
    preferences.h \
    tilefetcher.h \
    memcache.h \
    task.h \
    disktask.h \
    networktask.h \
    debug.h \
    debugdialog.h \
    pathgraphicsitem.h \
    pathnode.h \
    pathedge.h \
    pathedgesegment.h \
    geocircle.h \
    worldwindow.h \
    path.h
FORMS += mainwindow.ui \
    preferences.ui \
    debugdialog.ui \
    viewwidgets.ui
SOURCES += main.cpp \
    mainwindow.cpp \
    mapview.cpp \
    mgmreader.cpp \
    geotools.cpp \
    tile.cpp \
    tilelayer.cpp \
    mainscene.cpp \
    preferences.cpp \
    tilefetcher.cpp \
    memcache.cpp \
    task.cpp \
    disktask.cpp \
    networktask.cpp \
    debug.cpp \
    debugdialog.cpp \
    pathgraphicsitem.cpp \
    pathnode.cpp \
    pathedge.cpp \
    pathedgesegment.cpp \
    geocircle.cpp \
    worldwindow.cpp \
    path.cpp
RESOURCES += steps.qrc
