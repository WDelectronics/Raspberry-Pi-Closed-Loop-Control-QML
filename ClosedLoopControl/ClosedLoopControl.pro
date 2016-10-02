
QT       += core serialport
QT       += qml quick
QT       += quickcontrols2

TARGET = ClosedLoopControl
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

RESOURCES += qml.qrc

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH +=  $$PWD/../../../../usr/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SOURCES += main.cpp \
    control.cpp \
    pid.cpp \
    parser.cpp \
    settings.cpp

HEADERS += \
    control.h \
    pid.h \
    parser.h \
    settings.h

INSTALLS = target
target.files = ClosedLoopControl
target.path = /home/pi

DISTFILES +=
