TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11 -mfpu=neon
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

