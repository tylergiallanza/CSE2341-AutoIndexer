TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    AutoIndexer.cpp \
    DSstring.cpp \
    main.cpp

HEADERS += \
    AutoIndexer.h \
    DSlinkedList.h \
    DSRBtree.h \
    DSsortedLinkedList.h \
    DSstring.h \
    DSvector.h
    tests.hpp
