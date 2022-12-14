QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG   += cmdline precompile_header

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PRECOMPILED_HEADER = pch.h

SOURCES += \
    ../Common/loginfo.cpp \
    ../Common/pipeclient.cpp \
    ../Common/pipehost.cpp \
    logbuffer.cpp \
    logmodel.cpp \
    main.cpp \
    mainwindow.cpp \
    pipeserver.cpp \
    processesmodel.cpp \
    processesseeker.cpp \
    processesstorage.cpp \
    processinfo.cpp \
    processmonitor.cpp

HEADERS += \
    ../Common/loginfo.h \
    ../Common/pipeclient.h \
    ../Common/pipehost.h \
    logbuffer.h \
    logmodel.h \
    mainwindow.h \
    pch.h \
    pipeserver.h \
    processesmodel.h \
    processesseeker.h \
    processesstorage.h \
    processinfo.h \
    processmonitor.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
