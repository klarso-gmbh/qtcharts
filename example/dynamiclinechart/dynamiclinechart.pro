!include( ../../common.pri ) {
 error( "Couldn't find the common.pri file!" )
}

!include( ../../integrated.pri ) {
 error( "Couldn't find the integrated.pri file !")
}

TARGET = dynamicLineChart
TEMPLATE = app
QT += core gui
SOURCES += main.cpp
HEADERS += updater.h



