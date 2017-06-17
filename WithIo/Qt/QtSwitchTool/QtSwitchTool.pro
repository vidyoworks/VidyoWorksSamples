#-------------------------------------------------
#
# Project created by QtCreator 2016-06-08T13:26:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtSwitchTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vsroomlink.cpp \
    VsPlugin.cpp \
    VsStatus.cpp \
    VidyoWorksUii.cpp

HEADERS  += mainwindow.h \
    vsroomlink.h \
    VsPlugin.h \
    VsStatus.h \
    VidyoWorksUii.h

FORMS    += mainwindow.ui \
    vsroomlink.ui \
    VidyoWorksUi.ui

INCLUDEPATH +=\
                VidyoClient/include

macx {
        QMAKE_INFO_PLIST = resources/macx/info.plist

}

win32 {
       RC_FILE = resources/win32/win32.rc
}


unix {
        macx {
            LIBS += \
            ../QtSwitchTool/VidyoClient/lib/mac/VidyoClientSwitch.dylib

        } else {
        LIBS += \
        VidyoClient/lib/linux/libVidyoClientSwitch.so\
        -LVidyoClient/lib\
        -lblkid\
        -lXrandr\
        -lanl\
        -lpthread\
        -lGL -lGLU -lX11\
        -lrt
        }
}
win32 {
        LIBS += \
        -L..\\QtSwitchTool\\VidyoClient\\lib\\win\
        VidyoClientSwitch.lib
}

