#-------------------------------------------------
#
# Project created by QtCreator 2016-06-18T16:41:41
#
#-------------------------------------------------

QT       -= core gui

TARGET = LibRenet
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    src/librenet.cpp \
    src/netdev_controller.cpp \
    src/ipv4_address.cpp \
    src/mac_address.cpp

HEADERS += librenet.h \
    include/librenet.h \
    include/netdev_controller.h \
    include/macros.h \
    include/ipv4_address.h \
    include/mac_address.h \
    include/protocol.h \
    include/ethernetII.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
