TARGET = qastro_ui_test
TEMPLATE = app
QT = core gui
include (../uicomponents.pri)
INCLUDEPATH += src

HEADERS += src/graphwidget.h \
    src/piedelegateitemtest.h

SOURCES += src/main.cpp src/graphwidget.cpp \
    src/fanshapetest.cpp \
    src/pieitemtest.cpp \
    src/piedelegateitemtest.cpp

FORMS += \
    src/piedelegateitemtest.ui
