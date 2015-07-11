TEMPLATE = app
CONFIG += console c11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.c \
    generator.c \
    renderer.c \
    common.c \
    seeker.c \
    stack.c

LIBS += -lGL -lOSMesa -lpng

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    generator.h \
    types.h \
    renderer.h \
    common.h \
    seeker.h \
    stack.h

