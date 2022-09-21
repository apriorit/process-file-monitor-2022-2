include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

SOURCES += \
        main.cpp         tst_processesmonitortest.cpp \
        ../processmonitor.cpp
