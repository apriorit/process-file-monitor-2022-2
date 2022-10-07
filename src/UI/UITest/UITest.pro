GOOGLETEST_DIR = ..\..\..\ext\googletest
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
    processmonitortestingutility.cpp \
    tst_bothprocesseslistequals.cpp \
    tst_loginfotest.cpp \
    tst_pipeclienttest.cpp \
    tst_pipeservertest.cpp \
    tst_processesmonitortest.cpp \
    tst_processesinfotest.cpp \
    ../processmonitor.cpp \
    ../processinfo.cpp \
    ../../Common/pipehost.cpp \
    ../pipeserver.cpp \
    ../../Common/pipeclient.cpp \
    ../../Common/loginfo.cpp \
    ../logbuffer.cpp \
    ../processesstorage.cpp \
    tst_processesseeker.cpp \
    tst_processesstorage.cpp

HEADERS += \
    pch.h \
    processmonitortestingutility.h
