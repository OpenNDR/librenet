#-------------------------------------------------
#
# Project created by QtCreator 2016-06-18T16:41:41
#
#-------------------------------------------------

QT       -= core gui

TARGET = LibRenet
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14

SOURCES += \
    src/librenet.cpp \
    src/netdev_controller.cpp \
    src/ipv4_address.cpp

HEADERS += librenet.h \
    include/librenet.h \
    include/netdev_controller.h \
    include/macros.h \
    include/ipv4_address.h \
    include/protocol.h \
    include/ethernetII.h \
    include/hw_address.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
