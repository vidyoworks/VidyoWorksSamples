#-------------------------------------------------
#
# Project created by QtCreator 2016-06-08T13:26:10
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGalleryView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vsroomlink.cpp \
    VsPlugin.cpp \
    VsStatus.cpp \
    MyGlCanvas.cpp

HEADERS  += mainwindow.h \
    vsroomlink.h \
    VsPlugin.h \
    VsStatus.h \
    MyGlCanvas.h

FORMS    += mainwindow.ui \
    vsroomlink.ui \
    MyGlCanvas.ui

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
            ../QtGalleryView/VidyoClient/lib/mac/VidyoClientDll.dylib

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
        -L..\\QtGalleryView\\VidyoClient\\lib\\win32\
        VidyoClientDll.lib
}

