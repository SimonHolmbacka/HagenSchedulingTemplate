TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -mssse3 -msse4.1 -mssse3 -msse3 -msse2 -msse
LIBS += -pthread
SOURCES += main.cpp \
    LinkedList.cpp \
    metadata.cpp \
    fixdata.cpp \
    schedule.cpp \
    core.cpp \
    parser.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    LinkedList.h \
    metadata.h \
    fixdata.h \
    schedule.h \
    core.h \
    parser.h \
    settings.h

