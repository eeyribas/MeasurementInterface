QT += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeasurementInterface
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    languagedialog.cpp \
    linechartthread.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mousemovefunction.cpp \
    processthread.cpp \
    yesnodialog.cpp

HEADERS += \
    languagedialog.h \
    linechartparameters.h \
    linechartthread.h \
    logindialog.h \
    mainwindow.h \
    mousemovefunction.h \
    processthread.h \
    staticparameters.h \
    yesnodialog.h

FORMS += \
    languagedialog.ui \
    logindialog.ui \
    mainwindow.ui \
    yesnodialog.ui

RESOURCES += \
    resources.qrc
