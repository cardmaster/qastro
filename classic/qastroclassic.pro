TARGET = qastroclassic
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    timeloc.cpp \
    planet.cpp \
    planetfactory.cpp \
    planetset.cpp \
    houses.cpp \
    signs.cpp \
    aspect.cpp \
    astrology.cpp \
    astrologdat.cpp \
    grapher.cpp \
    texter.cpp \
    timeloceditor.cpp \
    astromath.cpp \
    conf.cpp \
    settings.cpp \
    pathinputer.cpp
HEADERS += mainwindow.h \
    timeloc.h \
    planet.h \
    planetfactory.h \
    cswe.h \
    planetset.h \
    houses.h \
    signs.h \
    aspect.h \
    astrology.h \
    timelocfile.h \
    astrologdat.h \
    grapher.h \
    texter.h \
    timeloceditor.h \
    astromath.h \
    conf.h \
    settings.h \
    pathinputer.h
FORMS += mainwindow.ui \
    timeloceditor.ui \
    settings.ui

include(../libswe/libswe.pri)

LIBS += -lm
RESOURCES += qastro.qrc \
    ../resources/epeh.qrc
RC_FILE = qastro.rc

#Deployment config
#ephe.source = ephe
DEPLOYMENTFOLDERS = #ephe

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()
