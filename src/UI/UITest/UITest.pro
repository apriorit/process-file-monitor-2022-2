include(gtest_dependency.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt
CONFIG   += cmdline precompile_header

PRECOMPILED_HEADER = pch.h

SOURCES += \
    ../processesseeker.cpp \
    main.cpp \
    tst_processesmonitortest.cpp \
    tst_processesinfotest.cpp \
    ../processmonitor.cpp \
    tst_processesseeker.cpp

HEADERS += \
    pch.h
