TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    buffer_circular.c

HEADERS += \
    comunicacao.h \
    modulo.h \
    buffer_circular.h
