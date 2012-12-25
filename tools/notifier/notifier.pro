#-------------------------------------------------
#
# Project created by QtCreator 2012-09-07T16:16:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = notifier
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    table_model.cpp

HEADERS  += window.h \
    structs.h \
    table_model.h

FORMS    += window.ui


CONFIG += static


QMAKE_LFLAGS += -static-libgcc -static-libstdc++


RESOURCES += \
    notifier.qrc

