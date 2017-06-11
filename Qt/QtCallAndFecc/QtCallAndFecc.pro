#-------------------------------------------------
#
# Project created by QtCreator 2016-06-08T13:26:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCallAndFecc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    VsPlugin.cpp \
    VsStatus.cpp \
    VsUserAccount.cpp \
    VDCall.cpp

HEADERS  += mainwindow.h \
    VsPlugin.h \
    VsStatus.h \
    VsUserAccount.h \
    VDCall.h

FORMS    += mainwindow.ui \
    VsUserAccount.ui \
    VDCall.ui

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
            ../QtCallAndFecc/VidyoClient/lib/mac/VidyoClientDll.dylib

        } else {
        LIBS += \
        VidyoClient/lib/linux/libVidyoClientDll.so\
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
        -L..\\QtCallAndFecc\\VidyoClient\\lib\\win\
        VidyoClientDll.lib
}

