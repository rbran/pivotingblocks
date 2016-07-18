TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    comunicacao.c \
    modulos/dummy.c \
    modulo.c \
    modulos/zero.c \
    modulos/null.c \
    utils/buffer_circular.c \
    utils/linked_list.c \
    utils/linked_list_iterator.c

HEADERS += \
    comunicacao.h \
    modulo.h \
    buffer_circular.h \
    modulos/dummy.h \
    modulos/zero.h \
    modulos/null.h \
    utils/buffer_circular.h \
    utils/linked_list.h
