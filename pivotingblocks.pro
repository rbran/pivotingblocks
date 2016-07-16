TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    buffer_circular.c \
    comunicacao.c \
    modulos/dummy.c \
    modulo.c \
    modulos/zero.c \
    modulos/null.c

HEADERS += \
    comunicacao.h \
    modulo.h \
    buffer_circular.h \
    modulos/dummy.h \
    modulos/zero.h \
    modulos/null.h
