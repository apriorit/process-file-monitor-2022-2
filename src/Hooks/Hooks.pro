QT -= gui

TEMPLATE = lib
DEFINES += HOOKS_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dllmain.cpp

HEADERS += \
    pch.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/../../ext/mhook/ -lmhook

INCLUDEPATH += $$PWD/../../ext/mhook
DEPENDPATH += $$PWD/../../ext/mhook

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../ext/mhook/mhook.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../ext/mhook/libmhook.a
