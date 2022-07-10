QT       += core gui charts widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lhdf5_cpp -lhdf5

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chart.cpp \
    chartview.cpp \
    databasexrd.cpp \
    graphicsscene.cpp \
    graphicsview.cpp \
    main.cpp \
    mainwindow.cpp \
	 h5data.cpp \
    phase.cpp

HEADERS += \
    chart.h \
    chartview.h \
    databasexrd.h \
    graphicsscene.h \
    graphicsview.h \
    mainwindow.h \
	 h5data.h \
    phase.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




#to use H5 in windows
DEFINES += H5_BUILT_AS_DYNAMIC_LIB
